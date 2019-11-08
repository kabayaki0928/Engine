#include "vulkan_render_pipeline.h"

#include "descriptor.h"
#include "vulkan_graphics_backend.h"
#include "vulkan_utils.h"
#include "vertex.h"
#include "viewport.h"
#include "shader.h"
#include "uniform_buffer.h"
#include "queue_family.h"

namespace vengine
{
    VulkanRenderPipeline::VulkanRenderPipeline(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend) {
        graphics_backend_ = graphics_backend;
    }

    VulkanRenderPipeline::~VulkanRenderPipeline() {
    }

    void VulkanRenderPipeline::initialize() {
        createGraphicsPipeline();
    }

    void VulkanRenderPipeline::createGraphicsPipeline() {
        // リソースに対してヒモづいたほうがよさそう
        auto shader = std::make_unique<Shader>(graphics_backend_, "shaders/vert.spv", "shaders/frag.spv");
        auto descriptor = std::make_unique<Descriptor>(graphics_backend_);
        auto viewport = std::make_unique<Viewport>();

        //auto vertShaderCode = readFile("shaders/vert.spv");
        //auto fragShaderCode = readFile("shaders/frag.spv");
        //
        //VkShaderModule vertShaderModule = createShaderModule(vertShaderCode);
        //VkShaderModule fragShaderModule = createShaderModule(fragShaderCode);

        //VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
        //vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        //vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
        //vertShaderStageInfo.module = vertShaderModule;
        //vertShaderStageInfo.pName = "main";
        //
        //VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
        //fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        //fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        //fragShaderStageInfo.module = fragShaderModule;
        //fragShaderStageInfo.pName = "main";

        VkPipelineShaderStageCreateInfo shaderStages[] = {
            shader->getVertexShaderModule().create_info_,
            shader->getFragmentShaderModule().create_info_, 
        };

        VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
        vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

        auto bindingDescription = Vertex::getBindingDescription();
        auto attributeDescriptions = Vertex::getAttributeDescriptions();

        vertexInputInfo.vertexBindingDescriptionCount = 1;
        vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
        vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
        vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

        VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
        inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        inputAssembly.primitiveRestartEnable = VK_FALSE;

        /*VkViewport viewport = {};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = graphics_backend_->getVulkanSwapchain().getWidth();
        viewport.height = graphics_backend_->getVulkanSwapchain().getHeight();
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        VkRect2D scissor = {};
        scissor.offset = { 0, 0 };
        scissor.extent = graphics_backend_->getVulkanSwapchain().getExtent();

        VkPipelineViewportStateCreateInfo viewportState = {};
        viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewportState.viewportCount = 1;
        viewportState.pViewports = &viewport;
        viewportState.scissorCount = 1;
        viewportState.pScissors = &scissor;*/

        //VkPipelineRasterizationStateCreateInfo rasterizer = {};
        //rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        //rasterizer.depthClampEnable = VK_FALSE;
        //rasterizer.rasterizerDiscardEnable = VK_FALSE;
        //rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
        //rasterizer.lineWidth = 1.0f;
        //rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
        //rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
        //rasterizer.depthBiasEnable = VK_FALSE;

        //VkPipelineMultisampleStateCreateInfo multisampling = {};
        //multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        //multisampling.sampleShadingEnable = VK_FALSE;
        //multisampling.rasterizationSamples = msaaSamples;

        //VkPipelineDepthStencilStateCreateInfo depthStencil = {};
        //depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        //depthStencil.depthTestEnable = VK_TRUE;
        //depthStencil.depthWriteEnable = VK_TRUE;
        //depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
        //depthStencil.depthBoundsTestEnable = VK_FALSE;
        //depthStencil.stencilTestEnable = VK_FALSE;

        //VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
        //colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        //colorBlendAttachment.blendEnable = VK_FALSE;

        //VkPipelineColorBlendStateCreateInfo colorBlending = {};
        //colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        //colorBlending.logicOpEnable = VK_FALSE;
        //colorBlending.logicOp = VK_LOGIC_OP_COPY;
        //colorBlending.attachmentCount = 1;
        //colorBlending.pAttachments = &colorBlendAttachment;
        //colorBlending.blendConstants[0] = 0.0f;
        //colorBlending.blendConstants[1] = 0.0f;
        //colorBlending.blendConstants[2] = 0.0f;
        //colorBlending.blendConstants[3] = 0.0f;

        //VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
        //pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        //pipelineLayoutInfo.setLayoutCount = 1;
        //pipelineLayoutInfo.pSetLayouts = ;

        VkResult result = vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayout);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to create pipeline layout!");
        }

        VkGraphicsPipelineCreateInfo pipelineInfo = {};
        pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        pipelineInfo.stageCount = 2;
        pipelineInfo.pStages = shaderStages;
        pipelineInfo.pVertexInputState = &vertexInputInfo;
        pipelineInfo.pInputAssemblyState = &inputAssembly;
        pipelineInfo.pViewportState = &viewportState;
        pipelineInfo.pRasterizationState = &rasterizer;
        pipelineInfo.pMultisampleState = &multisampling;
        pipelineInfo.pDepthStencilState = &depthStencil;
        pipelineInfo.pColorBlendState = &colorBlending;
        pipelineInfo.layout = pipelineLayout;
        pipelineInfo.renderPass = renderPass;
        pipelineInfo.subpass = 0;
        pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

        if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS) {
            throw std::runtime_error("failed to create graphics pipeline!");
        }

        vkDestroyShaderModule(device, fragShaderModule, nullptr);
        vkDestroyShaderModule(device, vertShaderModule, nullptr);
    }

    void VulkanRenderPipeline::draw() {

        glfwPollEvents();

        auto logical_device = graphics_backend_->getLogicalDevice();
        auto swapchain = graphics_backend_->getVulkanSwapchain();

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
        auto swapchain = graphics_backend_->getVulkanSwapchain();
        auto extent = swapchain.getExtent();
        auto device = graphics_backend_->getLogicalDevice();


        swapChainFramebuffers.resize(swapChainImageViews.size());

        for (size_t i = 0; i < swapChainImageViews.size(); i++) {
            std::array<VkImageView, 3> attachments = {
                colorImageView,
                depthImageView,
                swapChainImageViews[i]
            };

            VkFramebufferCreateInfo framebufferInfo = {};
            framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            framebufferInfo.renderPass = renderPass;
            framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
            framebufferInfo.pAttachments = attachments.data();
            framebufferInfo.width = extent.width;
            framebufferInfo.height = extent.height;
            framebufferInfo.layers = 1;

            if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create framebuffer!");
            }
        }
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
        VkFormat colorFormat = swapChainImageFormat;

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
            if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
                vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS ||
                vkCreateFence(device, &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) {
                throw std::runtime_error("failed to create synchronization objects for a frame!");
            }
        }
    }
} // rengine
