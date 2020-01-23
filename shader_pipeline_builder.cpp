#include "shader_pipeline_builder.h"

#include "shader.h"

namespace vengine
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    ShaderPipelineBuilder::ShaderPipelineBuilder() {
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    ShaderPipelineBuilder::~ShaderPipelineBuilder() {
    }

    /// <summary>
    /// shader stage作成(頂点編)
    /// </summary>
    void ShaderPipelineBuilder::buildVertexShaderStage(SpShader shader, VkPipelineShaderStageCreateInfo& out_create_info) {
        // https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPipelineShaderStageCreateInfo.html
        out_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        out_create_info.stage = VK_SHADER_STAGE_VERTEX_BIT;
        out_create_info.module = shader->getVertexShaderModule();
        out_create_info.pName = "main";
    }
    /// <summary>
    /// shader stage作成(フラグメント編)
    /// </summary>
    /// <param name="shader"></param>
    /// <param name="out_create_info"></param>
    void ShaderPipelineBuilder::buildFragmentShaderStage(SpShader shader, VkPipelineShaderStageCreateInfo& out_create_info) {
        // https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPipelineShaderStageCreateInfo.html
        out_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        out_create_info.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
        out_create_info.module = shader->getFragmentShaderModule();
        out_create_info.pName = "main";
    }
    /// <summary>
    /// モデルからの入力値で何を受け取るか設定
    /// </summary>
    /// <param name="shader"></param>
    /// <param name="out_create_info"></param>
    void ShaderPipelineBuilder::buildVertexInputInfo(SpShader shader, VkPipelineVertexInputStateCreateInfo& out_create_info) {
        auto parameter = shader->getParameter();
        auto binding = parameter->getBindingDescription();
        auto attribute = parameter->getAttributeDescription();
        // https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPipelineVertexInputStateCreateInfo.html
        out_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

        // シェーダー適用時に流し込むパラメータの全体設定感
        out_create_info.vertexBindingDescriptionCount = 1;
        out_create_info.pVertexBindingDescriptions = &binding;

        // シェーダー適用時に流し込むパラメータの詳細設定
        // シェーダーファイルの「layout(location = 0) in vec3 fragColor;」ってやつ
        out_create_info.vertexAttributeDescriptionCount = attribute.length_;
        out_create_info.pVertexAttributeDescriptions = attribute.attribute_;
    }
    /// <summary>
    /// 入力アセンブリ設定
    /// </summary>
    /// <param name="shader"></param>
    /// <param name="out_create_info"></param>
    void ShaderPipelineBuilder::buildInputAssemblyInfo(SpShader shader, VkPipelineInputAssemblyStateCreateInfo& out_create_info) {
        // https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPipelineInputAssemblyStateCreateInfo.html
        // TODO shader読み込み時に変更できるようにする必要がある
        out_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        out_create_info.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        out_create_info.primitiveRestartEnable = VK_FALSE;
    }

} // vengine
