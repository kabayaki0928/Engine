#pragma once

namespace vengine
{
    /// <summary>
    /// 
    /// </summary>
    class RenderPipelineBuilder final
    {
    public:
        RenderPipelineBuilder();
        ~RenderPipelineBuilder();

        static void createRasterizationState(VkPipelineRasterizationStateCreateInfo& out_create_info);
        static void createMultisampleState(const VkSampleCountFlagBits& msaa_samples, VkPipelineMultisampleStateCreateInfo& out_create_info);
        static void createDepthStencilState(VkPipelineDepthStencilStateCreateInfo& out_create_info);
        static void createColorBlendAttachmentState(VkPipelineColorBlendAttachmentState& out_create_info);
        static void createColorBlendState(const VkPipelineColorBlendAttachmentState& color_blend_attachment, VkPipelineColorBlendStateCreateInfo& out_create_info);
        static void createPipelineLayout(const VkDescriptorSetLayout& layout, VkPipelineLayoutCreateInfo& out_create_info);
        static void createGraphicsPipeline(
            const VkPipelineShaderStageCreateInfo*          stages,
            const VkPipelineVertexInputStateCreateInfo*     vertex_input_state,
            const VkPipelineInputAssemblyStateCreateInfo*   input_assembly_state,
            const VkPipelineViewportStateCreateInfo*        viewport_state,
            const VkPipelineRasterizationStateCreateInfo*   rasterization_state,
            const VkPipelineMultisampleStateCreateInfo*     Multisample_state,
            const VkPipelineDepthStencilStateCreateInfo*    depth_stencil_state,
            const VkPipelineColorBlendStateCreateInfo*      color_blend_state,
            const VkPipelineLayout&                         layout,
            const VkRenderPass&                             render_pass,
            VkGraphicsPipelineCreateInfo&                   out_create_info
        );

    };
} // vengine