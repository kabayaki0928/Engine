#pragma once

namespace vengine
{
    class Shader;
    using SpShader = std::shared_ptr<Shader> const;

    /// <summary>
    /// �V�F�[�_�[��RenderingPipeline��ɔz�u / �������Ă������߂̃N���X
    /// </summary>
    class ShaderPipelineBuilder
    {
    public:
        ShaderPipelineBuilder();
        ~ShaderPipelineBuilder();

        void buildVertexShaderStage(SpShader shader, VkPipelineShaderStageCreateInfo& out_create_info);
        void buildFragmentShaderStage(SpShader shader, VkPipelineShaderStageCreateInfo& out_create_info);
        void buildVertexInputInfo(SpShader shader, VkPipelineVertexInputStateCreateInfo& out_create_info);
        void buildInputAssemblyInfo(SpShader shader, VkPipelineInputAssemblyStateCreateInfo& out_create_info);
    };
} // vengine

