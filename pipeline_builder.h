#pragma once

namespace vengine
{
    class CameraPipelineBuilder;
    class ShaderPipelineBuilder;
    class RenderPassPipelineBuilder;
    class DescriptorPipelineBuilder;
    class VulkanGraphicsBackend;

    /// <summary>
    /// GraphicsPipeline構築時に必要な処理をまとめてあるクラス
    /// </summary>
    class PipelineBuilder final
    {
    private:
        std::shared_ptr<CameraPipelineBuilder> camera_builder_;
        std::shared_ptr<ShaderPipelineBuilder> shader_builder_;
        std::shared_ptr<RenderPassPipelineBuilder> render_pass_builder_;
        std::shared_ptr<DescriptorPipelineBuilder> descriptor_builder_;
    public:
        PipelineBuilder(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend);
        ~PipelineBuilder();

        inline std::shared_ptr<CameraPipelineBuilder> camera() const noexcept { return camera_builder_; }
        inline std::shared_ptr<ShaderPipelineBuilder> shader() const noexcept { return shader_builder_; }
        inline std::shared_ptr<RenderPassPipelineBuilder> render_pass() const noexcept { return render_pass_builder_; }
        inline std::shared_ptr<DescriptorPipelineBuilder> descriptor() const noexcept { return descriptor_builder_; }

        void buildDepthStencilState(VkPipelineDepthStencilStateCreateInfo& out_create_info);
        void buildColorBlendAttachmentState(VkPipelineColorBlendAttachmentState& out_create_info);
        void buildColorBlendState(const VkPipelineColorBlendAttachmentState& color_blend_attachment, VkPipelineColorBlendStateCreateInfo& out_create_info);
        void buildPipelineLayout(const VkDescriptorSetLayout& layout, VkPipelineLayoutCreateInfo& out_create_info);
        void buildGraphicsPipeline(
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