#include "pipeline_builder.h"

#include "vulkan_graphics_backend.h"

#include "camera_pipeline_builder.h"
#include "shader_pipeline_builder.h"
#include "render_pass_pipeline_builder.h"
#include "descriptor_pipeline_builder.h"

namespace vengine
{
    PipelineBuilder::PipelineBuilder(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend)
    : camera_builder_(std::make_shared<CameraPipelineBuilder>()),
      shader_builder_(std::make_shared<ShaderPipelineBuilder>()),
      render_pass_builder_(std::make_shared<RenderPassPipelineBuilder>(graphics_backend)),
      descriptor_builder_(std::make_shared<DescriptorPipelineBuilder>(graphics_backend)){
    }
    PipelineBuilder::~PipelineBuilder() {
        camera_builder_ = nullptr;
        shader_builder_ = nullptr;
        render_pass_builder_ = nullptr;
        descriptor_builder_ = nullptr;
    }
    void PipelineBuilder::buildDepthStencilState(VkPipelineDepthStencilStateCreateInfo& out_create_info) {
        out_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        out_create_info.depthTestEnable = VK_TRUE;
        out_create_info.depthWriteEnable = VK_TRUE;
        out_create_info.depthCompareOp = VK_COMPARE_OP_LESS;
        out_create_info.depthBoundsTestEnable = VK_FALSE;
        out_create_info.stencilTestEnable = VK_FALSE;
    }
    void PipelineBuilder::buildColorBlendAttachmentState(VkPipelineColorBlendAttachmentState& out_create_info) {
        out_create_info.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        out_create_info.blendEnable = VK_FALSE;
    }
    void PipelineBuilder::buildColorBlendState(const VkPipelineColorBlendAttachmentState& color_blend_attachment, VkPipelineColorBlendStateCreateInfo& out_create_info) {
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
    void PipelineBuilder::buildPipelineLayout(const VkDescriptorSetLayout& layout, VkPipelineLayoutCreateInfo& out_create_info) {
        out_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        out_create_info.setLayoutCount = 1;
        out_create_info.pSetLayouts = &layout;
    }
    void PipelineBuilder::buildGraphicsPipeline(
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
        out_create_info.subpass = 0; // TODO subpassä÷òAÇÕÇ†Ç∆Ç≈çlÇ¶ÇÈ
        out_create_info.basePipelineHandle = VK_NULL_HANDLE;
    }
} // vengine