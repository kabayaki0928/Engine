#pragma once

namespace vengine
{
    class Shader;
    using PShader = const Shader* const;

    /// <summary>
    /// シェーダーをRenderingPipeline上に配置 / 生成していくためのクラス
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

