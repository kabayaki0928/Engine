#include "render_pass_pipeline_builder.h"

#include "../vulkan/core/vulkan_graphics_backend.h"
#include "../vulkan/utils/vulkan_utils.h"

namespace vengine
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="graphics_backend"></param>
    /// <returns></returns>
    RenderPassPipelineBuilder::RenderPassPipelineBuilder(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend)
    : graphics_backend_(graphics_backend) {

    }


    RenderPassPipelineBuilder::~RenderPassPipelineBuilder() {
        graphics_backend_ = nullptr;
    }
    /// <summary>
    /// 
    /// https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkAttachmentDescription.html
    /// </summary>
    /// <param name="out_description"></param>
    void RenderPassPipelineBuilder::buildColorAttachemntDescription(const VkFormat& format, const VkSampleCountFlagBits& msaa_samples, VkAttachmentDescription& out_description) {
        // render targetの画像フォーマット
        out_description.format = format;
        out_description.samples = msaa_samples;
        // https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkAttachmentLoadOp.html
        // loadOp = 読み込み時に関すること
        // storeOp = 終わった後に関すること
        // RenderPass実行時に削除する設定
        out_description.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        // RenderPass実行時に書き込まれる指定
        out_description.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        // サブパスが開始した際にステンシルをどのように扱うか
        // VK_ATTACHMENT_LOAD_OP_DONT_CARE = コンテンツを保持する必要がない設定
        out_description.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        out_description.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        // RenderPass実行時のリソースの配置設定
        out_description.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        // フレームバッファ(カラー)として扱う
        // ※このフラグはVK_IMAGE_USAGE_COLOR_ATTACHMENT_BITで生成されている必要がある
        out_description.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
    }
    void RenderPassPipelineBuilder::buildDepthAttachmentDescription(const VkFormat& format, const VkSampleCountFlagBits& msaa_samples, VkAttachmentDescription& out_description) {
        out_description.format = VulkanUtils::findDepthFormat(graphics_backend_);
        out_description.samples = msaa_samples;
        out_description.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
        out_description.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        out_description.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        out_description.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        out_description.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        out_description.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
    }
    void RenderPassPipelineBuilder::buildColorAttachmentResolve(const VkFormat& format, VkAttachmentDescription& out_description) {
        out_description.format = format;
        out_description.samples = VK_SAMPLE_COUNT_1_BIT;
        out_description.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        out_description.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
        out_description.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
        out_description.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
        out_description.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        out_description.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
    }
    void RenderPassPipelineBuilder::buildSubpassDescription(VkSubpassDescription& out_description) {
        // TODO defferd時にGBufferの増減に対応できてないので関数として切り出したほうがよさそう
        VkAttachmentReference colorAttachmentRef = {};
        colorAttachmentRef.attachment = 0;
        colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        VkAttachmentReference depthAttachmentRef = {};
        depthAttachmentRef.attachment = 1;
        depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

        VkAttachmentReference colorAttachmentResolveRef = {};
        colorAttachmentResolveRef.attachment = 2;
        colorAttachmentResolveRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

        out_description.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
        out_description.colorAttachmentCount = 1;
        out_description.pColorAttachments = &colorAttachmentRef;
        out_description.pDepthStencilAttachment = &depthAttachmentRef;
        out_description.pResolveAttachments = &colorAttachmentResolveRef;
    }
    void RenderPassPipelineBuilder::buildSubpassDependency(VkSubpassDependency& out_dependency) {
        // https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkSubpassDependency.html
        out_dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
        out_dependency.dstSubpass = 0;
        // https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPipelineStageFlagBits.html
        out_dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        out_dependency.srcAccessMask = 0;
        out_dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        out_dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT
                                     | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    }
    template<int N>
    void RenderPassPipelineBuilder::buildRenderPass
    (
        std::array<VkAttachmentDescription, N> attachments,
        const VkSubpassDescription& subpass,
        const VkSubpassDependency& dependency,
        VkRenderPass& out_render_pass
    ) {
        out_render_pass.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
        out_render_pass.attachmentCount = static_cast<uint32_t>(attachments.size());
        out_render_pass.pAttachments = attachments.data();
        out_render_pass.subpassCount = 1;
        out_render_pass.pSubpasses = &subpass;
        out_render_pass.dependencyCount = 1;
        out_render_pass.pDependencies = &dependency;

        VkResult result = vkCreateRenderPass(graphics_backend_->getLogicalDevice(), &render_pass_info, nullptr, &renderPass);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to create render pass!");
        }
    }

    void RenderPassPipelineBuilder::buildSimpleRenderPass(VkRenderPass& out_render_pass) {
        VkAttachmentDescription color_attachment_description = {};
        VkAttachmentDescription depth_attachment_description = {};
        VkAttachmentDescription color_attachment_resolve = {};
        VkSubpassDescription subpass_description = {};
        VkSubpassDependency subpass_dependency = {};

        VkFormat format = graphics_backend_->getVulkanSwapchain().getSwapchainImageFormat();
        VkSampleCountFlagBits msaa_samples = VK_SAMPLE_COUNT_1_BIT; // TODO フレームバッファ関連をまとめたら移動する

        buildColorAttachemntDescription(format, msaa_samples, color_attachment_description);
        buildDepthAttachmentDescription(format, msaa_samples, depth_attachment_description);
        buildColorAttachmentResolve(format, color_attachment_resolve);
        buildSubpassDescription(subpass_description);
        buildSubpassDependency(subpass_dependency);
        buildRenderPass<3>
        (
            {color_attachment_description, depth_attachment_description, color_attachment_resolve},
            subpass_description,
            subpass_dependency,
            out_render_pass
        ); VK_SAMPLE_COUNT_1_BIT
    }
} // vengine
