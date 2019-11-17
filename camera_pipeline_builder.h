#pragma once

namespace vengine
{
    using PCamera = const Camera* const;
    class CameraPipelineBuilder
    {
    public:
        CameraPipelineBuilder();
        ~CameraPipelineBuilder();
        
        void buildViewport(PCamera camera, VkViewport& out_viewport);
        void buildScissor(PCamera camera, VkRect2D& out_scissor);
        void buildViewportState(PCamera camera, const VkViewport& viewport, const VkRect2D& scissor, VkPipelineViewportStateCreateInfo& out_create_info);
        void buildRasterizer(PCamera camera, VkPipelineRasterizationStateCreateInfo& out_create_info);
        void buildMultisample(PCamera camera, VkPipelineMultisampleStateCreateInfo& out_create_info);

        buildDepthStencilState();
        buildColorBlendAttachment();
        buildColorBlendState();
    };
} // vengine