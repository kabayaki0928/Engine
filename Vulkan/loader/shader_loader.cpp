#include "shader_loader.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include "../vulkan/core/vulkan_graphics_backend.h"
#include "../vulkan/graphics_resource/shader/shader.h"

namespace vengine
{
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="graphics_backend"></param>
    ShaderLoader::ShaderLoader(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend)
    : graphics_backend_(graphics_backend) {
    }

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ShaderLoader::~ShaderLoader() {
        graphics_backend_ = nullptr;
    }

    /// <summary>
    /// �ǂݍ��ݏ���
    /// </summary>
    /// <param name="file_name"></param>
    /// <param name="callback"></param>
    void ShaderLoader::loadVertexShader(const char* file_name, std::function<void(std::shared_ptr<VertexShaderModule>)> callback) {
        // TODO �L���b�V���I�ȉ���
        // �t�@�C���̒��g�����̂܂ܕԂ��ĊO���Ńp�����[�^�ݒ肷��悤�ɂ����ق������������H
        // �O������p�����[�^��n������ɂ͂Ȃ��Ă��Ȃ��̂ŕK�v���o���璼���X�^�C����

        auto buffer = ShaderLoader::loadFile(file_name);

        VkShaderModule module;
        ShaderModule shader_module = {};
        ShaderLoader::createShaderModule(graphics_backend_, buffer, shader_module);
        ShaderLoader::createShaderStage(file_name, ShaderStageType::VertexShader, shader_module);

        auto out_shader_module = std::make_shared<VertexShaderModule>(shader_module);

        callback(out_shader_module);
    }

    /// <summary>
    /// �t���O�����g�V�F�[�_�[�̓ǂݍ��ݏ���
    /// </summary>
    /// <param name="file_name"></param>
    /// <param name="callback"></param>
    void ShaderLoader::loadFragmentShader(const char* file_name, std::function<void(std::shared_ptr<FragmentShaderModule>)> callback) {
        
        auto buffer = ShaderLoader::loadFile(file_name);

        VkShaderModule module = {};
        ShaderModule shader_module = {};
        ShaderLoader::createShaderModule(graphics_backend_, buffer, shader_module);
        ShaderLoader::createShaderStage(file_name, ShaderStageType::FragmentShader, shader_module);

        auto out_shader_module = std::make_shared<FragmentShaderModule>(shader_module);

        callback(out_shader_module);
    }

    /// <summary>
    /// �t�@�C���̓ǂݍ��ݏ���
    /// </summary>-
    /// <param name="file_name"></param>
    /// <returns></returns>
    std::vector<char> ShaderLoader::loadFile(const char* file_name) {

        std::ifstream file(file_name, std::ios::ate | std::ios::binary);

        if (!file.is_open()) {
            throw std::runtime_error("failed to open file!");
        }

        size_t fileSize = (size_t)file.tellg();
        std::vector<char> buffer(fileSize);

        file.seekg(0);
        file.read(buffer.data(), fileSize);

        file.close();

        //return buffer;
    }

    /// <summary>
    /// VkShaderModule�̍쐬����
    /// </summary>
    /// <param name="graphics_backend"></param>
    /// <param name="code"></param>
    /// <param name="out_shader_module"></param>
    void ShaderLoader::createShaderModule
    (
        std::shared_ptr<VulkanGraphicsBackend> const graphics_backend,
        const std::vector<char>& code,
        ShaderModule& out_shader_module
    ) {
        VkShaderModuleCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
        createInfo.codeSize = code.size();
        createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

        VkResult result = vkCreateShaderModule(graphics_backend->getLogicalDevice(), &createInfo, nullptr, &out_shader_module.module_);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to create shader module!");
        }
    }

    /// <summary>
    /// VkPipelineShaderStageCreateInfo�̏���(VkGraphicsPipelineCreateInfo�ŕK�v)
    /// </summary>
    /// <param name="name"></param>
    /// <param name="stage_type"></param>
    /// <param name="out_shader_module"></param>
    void ShaderLoader::createShaderStage
    (
        const char* name,
        const ShaderStageType stage_type,
        ShaderModule& out_shader_module
    ) {
        VkPipelineShaderStageCreateInfo info = {};
        info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        info.stage = toShaderStageFlagBits(stage_type);
        info.module = out_shader_module.module_;
        info.pName = name;

        out_shader_module.create_info_ = info;
    }
    
    /// <summary>
    /// ShaderStageType -> VkShaderStageFlagBits�̕ϊ�����
    /// </summary>
    /// <param name="stage_type"></param>
    VkShaderStageFlagBits ShaderLoader::toShaderStageFlagBits(const ShaderStageType stage_type) {
        switch (stage_type) {
        case ShaderStageType::VertexShader:   return VK_SHADER_STAGE_VERTEX_BIT;
        case ShaderStageType::FragmentShader: return VK_SHADER_STAGE_FRAGMENT_BIT;
        }
        assert(false, "failed to shader stage type");
    }

} // vengine
