#pragma once

namespace vengine
{
    class Shader;
    using PShader = const Shader* const;

    /// <summary>
    /// �V�F�[�_�[��RenderingPipeline��ɔz�u / �������Ă������߂̃N���X
    /// </summary>
    class ShaderPipelineBuilder
    {
    public:
        ShaderPipelineBuilder();
        ~ShaderPipelineBuilder();

        void buildVertexShaderStage(PShader shader, VkPipelineShaderStageCreateInfo& out_create_info);
        void buildFragmentShaderStage(PShader shader, VkPipelineShaderStageCreateInfo& out_create_info);
        void buildVertexInputInfo(PShader shader, VkPipelineVertexInputStateCreateInfo& out_create_info);
        void buildInputAssemblyInfo(PShader shader, VkPipelineInputAssemblyStateCreateInfo& out_create_info);
    };
} // vengine

