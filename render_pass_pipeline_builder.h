#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace vengine
{
    class VulkanGraphicsBackend;

    /// <summary>
    /// GraphicsRenderPipeline作成時に必要なRenderPassを構築する部分を担当するクラス
    /// </summary>
    class RenderPassPipelineBuilder final
    {
    private:
        std::shared_ptr<VulkanGraphicsBackend> graphics_backend_;
    public:
        RenderPassPipelineBuilder(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend);
        ~RenderPassPipelineBuilder();

        void buildColorAttachemntDescription(VkAttachmentDescription& out_description);
        void buildDepthAttachmentDescription(VkAttachmentDescription& out_description);
        void buildColorAttachmentResolve(VkAttachmentDescription& out_description);
        void buildSubpassDescription(VkSubpassDescription& out_description);
        void buildSubpassDependency(VkSubpassDependency& out_dependency);
        template<int N>
        void buildRenderPass
        (
            std::array<VkAttachmentDescription, N> attachments,
            const VkSubpassDescription& subpass,
            const VkSubpassDependency& dependency,
            VkRenderPass& out_render_pass
        );

        void buildSimpleRenderPass(VkRenderPass& out_render_pass);

    };
} // vengine

