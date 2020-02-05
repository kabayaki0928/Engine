#include "shader_pipeline_builder.h"

#include "shader.h"

namespace vengine
{
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    ShaderPipelineBuilder::ShaderPipelineBuilder() {
    }

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ShaderPipelineBuilder::~ShaderPipelineBuilder() {
    }

    /// <summary>
    /// shader stage�쐬(���_��)
    /// </summary>
    void ShaderPipelineBuilder::buildVertexShaderStage(SpShader shader, VkPipelineShaderStageCreateInfo& out_create_info) {
        // https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPipelineShaderStageCreateInfo.html
        out_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        out_create_info.stage = VK_SHADER_STAGE_VERTEX_BIT;
        out_create_info.module = shader->getVertexShaderModule();
        out_create_info.pName = "main";
    }
    /// <summary>
    /// shader stage�쐬(�t���O�����g��)
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
    /// ���f������̓��͒l�ŉ����󂯎�邩�ݒ�
    /// </summary>
    /// <param name="shader"></param>
    /// <param name="out_create_info"></param>
    void ShaderPipelineBuilder::buildVertexInputInfo(SpShader shader, VkPipelineVertexInputStateCreateInfo& out_create_info) {
        auto parameter = shader->getParameter();
        auto binding = parameter->getBindingDescription();
        auto attribute = parameter->getAttributeDescription();
        // https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPipelineVertexInputStateCreateInfo.html
        out_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

        // �V�F�[�_�[�K�p���ɗ������ރp�����[�^�̑S�̐ݒ芴
        out_create_info.vertexBindingDescriptionCount = 1;
        out_create_info.pVertexBindingDescriptions = &binding;

        // �V�F�[�_�[�K�p���ɗ������ރp�����[�^�̏ڍאݒ�
        // �V�F�[�_�[�t�@�C���́ulayout(location = 0) in vec3 fragColor;�v���Ă��
        out_create_info.vertexAttributeDescriptionCount = attribute.length_;
        out_create_info.pVertexAttributeDescriptions = attribute.attribute_;
    }
    /// <summary>
    /// ���̓A�Z���u���ݒ�
    /// </summary>
    /// <param name="shader"></param>
    /// <param name="out_create_info"></param>
    void ShaderPipelineBuilder::buildInputAssemblyInfo(SpShader shader, VkPipelineInputAssemblyStateCreateInfo& out_create_info) {
        // https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPipelineInputAssemblyStateCreateInfo.html
        // TODO shader�ǂݍ��ݎ��ɕύX�ł���悤�ɂ���K�v������
        out_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
        out_create_info.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
        out_create_info.primitiveRestartEnable = VK_FALSE;
    }

} // vengine
