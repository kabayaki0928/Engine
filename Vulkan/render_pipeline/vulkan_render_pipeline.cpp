#include "vulkan_render_pipeline.h"

#include "../vulkan/utils/vulkan_utils.h"
#include "vertex.h"
#include "../vulkan/graphics_resource/shader/shader.h"
#include "uniform_buffer.h"
#include "queue_family.h"

#include "texture.h"
#include "ishader_parameter.h"
#include "../vulkan/graphics_resource/shader/shader.h""
#include "../vulkan/graphics_resource/material/material.h"
#include "../vulkan/graphics_resource/model/model.h"
#include "model_renderer.h"

#include "camera.h"

#include "pipeline_builder.h"
#include "camera_pipeline_builder.h"
#include "shader_pipeline_builder.h"
#include "render_pass_pipeline_builder.h"
#include "descriptor_pipeline_builder.h"

#include "../vulkan/core/vulkan_graphics_backend.h"

namespace vengine
{
    VulkanRenderPipeline::VulkanRenderPipeline(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend)
    : pipeline_builder_(std::make_unique<PipelineBuilder>(graphics_backend)),
      graphics_backend_(graphics_backend) {
    }

    VulkanRenderPipeline::~VulkanRenderPipeline() {
        graphics_backend_ = nullptr;
    }

    void VulkanRenderPipeline::initialize() {
        createGraphicsPipeline();
    }

    void VulkanRenderPipeline::createGraphicsPipeline() {


        // TODO 描画可能なモデル / メッシュ / プリミティブ型の取得
        auto model_renderers = std::vector<rengine::ModelRenderer>();
        auto cameras = std::vector<vengine::Camera*>(); // todo rengine側に持っていきたい

        // TODO 最後のしか反映されないので後で修正
        VkPipelineShaderStageCreateInfo vertex_shader_stage = {};
        VkPipelineShaderStageCreateInfo fragment_shader_stage = {};
        VkPipelineVertexInputStateCreateInfo vertex_input_info = {};
        VkPipelineInputAssemblyStateCreateInfo input_assembly_info = {};
        for (const rengine::ModelRenderer& model_renderer : model_renderers) {
            bool isEnable = model_renderer.isEnable();
            if (!isEnable) {
                continue;
            }

            std::shared_ptr<rengine::Material> material = model_renderer.getSharedMaterial();
            std::shared_ptr<Shader> shader = material->getShader();
            auto texture = material->getTextures();

            pipeline_builder_->shader()->buildVertexShaderStage(shader, vertex_shader_stage);
            pipeline_builder_->shader()->buildFragmentShaderStage(shader, fragment_shader_stage);
            pipeline_builder_->shader()->buildVertexInputInfo(shader, vertex_input_info);
            pipeline_builder_->shader()->buildInputAssemblyInfo(shader, input_assembly_info);
        }

        VkImageView texture_image_views;
        VkSampler texture_image_samplers;

        VkDescriptorSetLayout set_layout;
        pipeline_builder_->descriptor()->buildSimpleDescriptor
        (
            graphics_backend_->getVulkanSwapchain().getSwapchainCount(),
            uniform_buffers_,
            sizeof(UniformBufferObject),
            texture_image_views,
            texture_image_samplers,
            set_layout
        );

        VkViewport viewport = {};
        VkRect2D scissor = {};
        VkPipelineViewportStateCreateInfo viewport_state = {};
        VkPipelineRasterizationStateCreateInfo rasterization = {};
        VkPipelineMultisampleStateCreateInfo multisample = {};

        VkPipelineDepthStencilStateCreateInfo depth_stencil;
        VkPipelineColorBlendAttachmentState color_blend_attachment;
        VkPipelineColorBlendStateCreateInfo color_blend;
        for (auto camera : cameras) {

            pipeline_builder_->camera()->buildViewport(camera, viewport);
            pipeline_builder_->camera()->buildScissor(camera, scissor);
            pipeline_builder_->camera()->buildViewportState(camera, viewport, scissor, viewport_state);
            pipeline_builder_->camera()->buildRasterizer(camera, rasterization);
            pipeline_builder_->camera()->buildMultisample(camera, multisample);

            pipeline_builder_->camera()->buildDepthStencilState(camera, depth_stencil);
            pipeline_builder_->camera()->buildColorBlendAttachment(camera, color_blend_attachment);
            pipeline_builder_->camera()->buildColorBlendState(camera, color_blend_attachment, color_blend);
        }

        // RenderPass作成
        // simple hogeシリーズは関数群をまとめたやつ。
        // 展開する必要があるやも
        pipeline_builder_->render_pass()->buildSimpleRenderPass(render_pass_);


        VkPipelineLayoutCreateInfo pipeline_layout_info = {};
        pipeline_builder_->buildPipelineLayoutInfo(set_layout, pipeline_layout_info);
        pipeline_builder_->buildPipelineLayout(pipeline_layout_info, pipeline_layout_);
        
        VkPipelineShaderStageCreateInfo shaders[] = {
            fragment_shader_stage,
            vertex_shader_stage
        };

        // TODO poolしていないので必要がありそう
        VkGraphicsPipelineCreateInfo graphics_pipeline_create_info;
        pipeline_builder_->buildGraphicsPipelineInfo
        (
            shaders,
            &vertex_input_info,
            &input_assembly_info,
            &viewport_state,
            &rasterization,
            &multisample,
            nullptr, // depth stencil
            nullptr, // color blend state
            pipeline_layout_,
            render_pass_,
            graphics_pipeline_create_info
        );
        pipeline_builder_->buildGraphicsPipeline(graphics_pipeline_create_info, graphics_pipeline_);
    }

    void VulkanRenderPipeline::draw() {

        glfwPollEvents();

        const LogicalDevice& logical_device = graphics_backend_->getLogicalDevice();
        const Swapchain& swapchain = graphics_backend_->getVulkanSwapchain();

        vkWaitForFences(logical_device, 1, &in_flight_fences_[current_frame_], VK_TRUE, UINT64_MAX);

        uint32_t image_index;
        VkResult result = vkAcquireNextImageKHR(logical_device, swapchain, UINT64_MAX, image_available_semaphores_[current_frame_], VK_NULL_HANDLE, &image_index);

        if (result == VK_ERROR_OUT_OF_DATE_KHR) {
            // graphics_backend経由じゃなくてもいいかも
            // 類似の機能が増えたら再考
            graphics_backend_->recreateSwapchain();
            return;
        }
        else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
            throw std::runtime_error("failed to acquire swap chain image!");
        }

        updateUniformBuffer(image_index);

        VkSubmitInfo submitInfo = {};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

        VkSemaphore waitSemaphores[] = { image_available_semaphores_[current_frame_] };
        VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
        submitInfo.waitSemaphoreCount = 1;
        submitInfo.pWaitSemaphores = waitSemaphores;
        submitInfo.pWaitDstStageMask = waitStages;

        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &command_buffers_[image_index];

        VkSemaphore signalSemaphores[] = { render_finished_semaphores_[current_frame_] };
        submitInfo.signalSemaphoreCount = 1;
        submitInfo.pSignalSemaphores = signalSemaphores;

        vkResetFences(logical_device, 1, &in_flight_fences_[current_frame_]);

        if (vkQueueSubmit(graphics_queue_, 1, &submitInfo, in_flight_fences_[current_frame_]) != VK_SUCCESS) {
            throw std::runtime_error("failed to submit draw command buffer!");
        }

        VkPresentInfoKHR presentInfo = {};
        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

        presentInfo.waitSemaphoreCount = 1;
        presentInfo.pWaitSemaphores = signalSemaphores;

        VkSwapchainKHR swapChains[] = { graphics_backend_->getVulkanSwapchain() };
        presentInfo.swapchainCount = 1;
        presentInfo.pSwapchains = swapChains;

        presentInfo.pImageIndices = &image_index;

        result = vkQueuePresentKHR(present_queue_, &presentInfo);

        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || graphics_backend_->getWindow()->isFrameBufferResized()) {
            graphics_backend_->recreateSwapchain();
        }
        else if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to present swap chain image!");
        }

        current_frame_ = (current_frame_ + 1) % MAX_FRAMES_IN_FLIGHT;
    }


    void VulkanRenderPipeline::updateUniformBuffer(uint32_t current_image_index) {
        static auto startTime = std::chrono::high_resolution_clock::now();

        auto device = graphics_backend_->getLogicalDevice();
        auto extent = graphics_backend_->getSwapchain()->getExtent();
        auto currentTime = std::chrono::high_resolution_clock::now();
        float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();


        UniformBufferObject ubo = {};
        ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        ubo.projection = glm::perspective(glm::radians(45.0f), extent.width / (float)extent.height, 0.1f, 10.0f);
        ubo.projection[1][1] *= -1;

        void* data;
        vkMapMemory(device, uniform_buffers_memory_[current_image_index], 0, sizeof(ubo), 0, &data);
        memcpy(data, &ubo, sizeof(ubo));
        vkUnmapMemory(device, uniform_buffers_memory_[current_image_index]);
    }

    void VulkanRenderPipeline::createFrameBuffers() {
        auto cameras = std::vector<vengine::Camera*>(); // todo 取得方法を正しく
        for (const auto& camera : cameras) {
            VkFramebuffer frame_buffer;
            pipeline_builder_->camera()->buildFrameBuffer(camera, frame_buffer);

        }
        //const Swapchain& swapchain = graphics_backend_->getVulkanSwapchain();
        //auto extent = swapchain.getExtent();
        //auto device = graphics_backend_->getLogicalDevice();
        //auto count = swapchain.getSwapchainCount();
        //
        //frame_buffers_.resize(count);
        //
        //// TODO カメラごとに作る必要がある
        //for (size_t i = 0; i < count; i++) {
        //    std::array<VkImageView, 3> attachments = {
        //        colorImageView,
        //        depthImageView,
        //        swapChainImageViews[i]
        //    };
        //
        //    VkFramebufferCreateInfo framebufferInfo = {};
        //    framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        //    framebufferInfo.renderPass = renderPass;
        //    framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
        //    framebufferInfo.pAttachments = attachments.data();
        //    framebufferInfo.width = extent.width;
        //    framebufferInfo.height = extent.height;
        //    framebufferInfo.layers = 1;
        //
        //    if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {
        //        throw std::runtime_error("failed to create framebuffer!");
        //    }
        //}
    }

    void VulkanRenderPipeline::createCommandPool() {
        auto device = graphics_backend_->getLogicalDevice();
        auto physical_device = graphics_backend_->getPhysicalDevice();
        auto surface = graphics_backend_->getVulkanSurface();
        auto queueFamilyIndices = QueueFamily::findQueueFamilies(physical_device, surface);

        VkCommandPoolCreateInfo poolInfo = {};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

        if (vkCreateCommandPool(device, &poolInfo, nullptr, &command_pool_) != VK_SUCCESS) {
            throw std::runtime_error("failed to create graphics command pool!");
        }
    }

    void VulkanRenderPipeline::createColorResources() {
        const Swapchain& swapchain = graphics_backend_->getVulkanSwapchain();
        VkFormat colorFormat = swapchain.getSwapchainImageFormat();

        createImage(swapChainExtent.width, swapChainExtent.height, 1, msaaSamples, colorFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, colorImage, colorImageMemory);
        colorImageView = createImageView(colorImage, colorFormat, VK_IMAGE_ASPECT_COLOR_BIT, 1);

        transitionImageLayout(colorImage, colorFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, 1);
    }

    void VulkanRenderPipeline::createDepthResources() {
        VkFormat depthFormat = findDepthFormat();

        createImage(swapChainExtent.width, swapChainExtent.height, 1, msaaSamples, depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, depthImage, depthImageMemory);
        depthImageView = createImageView(depthImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT, 1);

        transitionImageLayout(depthImage, depthFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, 1);
    }

    void VulkanRenderPipeline::createSyncObject() {
        imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
        inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);

        VkSemaphoreCreateInfo semaphoreInfo = {};
        semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

        VkFenceCreateInfo fenceInfo = {};
        fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

        for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
            if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i])!= VK_SUCCESS
             || vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS
             || vkCreateFence(device, &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create synchronization objects for a frame!");
            }
        }
    }
} // rengine
