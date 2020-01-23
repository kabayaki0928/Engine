#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace vengine
{
    class Camera;
    using PCamera = const Camera* const;

    class VulkanGraphicsBackend;

    /// <summary>
    /// GraphicsRenderPipeline作成時に必要なカメラに依存するものの構築を担当するクラス
    /// </summary>
    class CameraPipelineBuilder final
    {
    private:
        std::shared_ptr<VulkanGraphicsBackend> graphics_backend_;
    public:
        CameraPipelineBuilder(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend);
        ~CameraPipelineBuilder();
        
        void buildViewport(PCamera camera, VkViewport& out_viewport);
        void buildScissor(PCamera camera, VkRect2D& out_scissor);
        void buildViewportState(PCamera camera, const VkViewport& viewport, const VkRect2D& scissor, VkPipelineViewportStateCreateInfo& out_create_info);
        void buildRasterizer(PCamera camera, VkPipelineRasterizationStateCreateInfo& out_create_info);
        void buildMultisample(PCamera camera, VkPipelineMultisampleStateCreateInfo& out_create_info);

        void buildDepthStencilState(PCamera camera, VkPipelineDepthStencilStateCreateInfo& out_create_info);
        void buildColorBlendAttachment(PCamera camera, VkPipelineColorBlendAttachmentState& out_create_info);
        void buildColorBlendState(PCamera camera, const VkPipelineColorBlendAttachmentState& attachment, VkPipelineColorBlendStateCreateInfo& out_create_info);

        void buildFrameBuffer(PCamera camera, VkFramebuffer& out_frame_buffer);
    };
} // vengine