#include "render_pipeline_builder.h"

namespace vengine
{
    RenderPipelineBuilder::RenderPipelineBuilder() {
    }
    RenderPipelineBuilder::~RenderPipelineBuilder() {
    }
    void RenderPipelineBuilder::createRasterizationState(VkPipelineRasterizationStateCreateInfo& out_create_info) {
        out_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        out_create_info.depthClampEnable = VK_FALSE;
        out_create_info.rasterizerDiscardEnable = VK_FALSE;
        out_create_info.polygonMode = VK_POLYGON_MODE_FILL;
        out_create_info.lineWidth = 1.0f;
        out_create_info.cullMode = VK_CULL_MODE_BACK_BIT;
        out_create_info.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
        out_create_info.depthBiasEnable = VK_FALSE;
    }
    void RenderPipelineBuilder::createMultisampleState(const VkSampleCountFlagBits& msaa_samples, VkPipelineMultisampleStateCreateInfo& out_create_info) {
        out_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        out_create_info.sampleShadingEnable = VK_FALSE;
        out_create_info.rasterizationSamples = msaa_samples;
    }
    void RenderPipelineBuilder::createDepthStencilState(VkPipelineDepthStencilStateCreateInfo& out_create_info) {
        out_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        out_create_info.depthTestEnable = VK_TRUE;
        out_create_info.depthWriteEnable = VK_TRUE;
        out_create_info.depthCompareOp = VK_COMPARE_OP_LESS;
        out_create_info.depthBoundsTestEnable = VK_FALSE;
        out_create_info.stencilTestEnable = VK_FALSE;
    }
    void RenderPipelineBuilder::createColorBlendAttachmentState(VkPipelineColorBlendAttachmentState& out_create_info) {
        out_create_info.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        out_create_info.blendEnable = VK_FALSE;
    }
    void RenderPipelineBuilder::createColorBlendState(const VkPipelineColorBlendAttachmentState& color_blend_attachment, VkPipelineColorBlendStateCreateInfo& out_create_info) {
        out_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        out_create_info.logicOpEnable = VK_FALSE;
        out_create_info.logicOp = VK_LOGIC_OP_COPY;
        out_create_info.attachmentCount = 1;
        out_create_info.pAttachments = &color_blend_attachment;
        out_create_info.blendConstants[0] = 0.0f;
        out_create_info.blendConstants[1] = 0.0f;
        out_create_info.blendConstants[2] = 0.0f;
        out_create_info.blendConstants[3] = 0.0f;
    }
    void RenderPipelineBuilder::createPipelineLayout(const VkDescriptorSetLayout& layout, VkPipelineLayoutCreateInfo& out_create_info) {
        out_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        out_create_info.setLayoutCount = 1;
        out_create_info.pSetLayouts = &layout;
    }
    void RenderPipelineBuilder::createGraphicsPipeline(
        const VkPipelineShaderStageCreateInfo*          stages,
        const VkPipelineVertexInputStateCreateInfo*     vertex_input_state,
        const VkPipelineInputAssemblyStateCreateInfo*   input_assembly_state,
        const VkPipelineViewportStateCreateInfo*        viewport_state,
        const VkPipelineRasterizationStateCreateInfo*   rasterization_state,
        const VkPipelineMultisampleStateCreateInfo*     ultisample_state,
        const VkPipelineDepthStencilStateCreateInfo*    depth_stencil_state,
        const VkPipelineColorBlendStateCreateInfo*      color_blend_state,
        const VkPipelineLayout&                         layout,
        const VkRenderPass&                             render_pass,
        VkGraphicsPipelineCreateInfo&                   out_create_info
    ) {
        out_create_info.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
        out_create_info.stageCount = 2;
        out_create_info.pStages = stages;
        out_create_info.pVertexInputState = vertex_input_state;
        out_create_info.pInputAssemblyState = input_assembly_state;
        out_create_info.pViewportState = viewport_state;
        out_create_info.pRasterizationState = rasterization_state;
        out_create_info.pMultisampleState = ultisample_state;
        out_create_info.pDepthStencilState = depth_stencil_state;
        out_create_info.pColorBlendState = color_blend_state;
        out_create_info.layout = layout;
        out_create_info.renderPass = render_pass;
        out_create_info.subpass = 0; // TODO subpass関連はあとで考える
        out_create_info.basePipelineHandle = VK_NULL_HANDLE;
    }
} // vengine