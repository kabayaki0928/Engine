//#include "stdafx.h"
//#include "shader_stage.h"
//
//namespace vengine
//{
//    /// <summary>
//    /// コンストラクタ
//    /// </summary>
//    /// <param name="name"></param>
//    /// <param name="shader_module"></param>
//    /// <param name="stage_type"></param>
//    ShaderStage::ShaderStage(const char* name, const VkShaderModule& shader_module, ShaderStageType stage_type)
//    : name_(name) {
//        shader_module_ = shader_module;
//        stage_type_ = stage_type;
//    }
//
//    /// <summary>
//    /// デストラクタ
//    /// </summary>
//    ShaderStage::~ShaderStage() {
//    }
//
//    /// <summary>
//    /// VkPipelineShaderStageCreateInfo作成処理
//    /// </summary>
//    void ShaderStage::create() {
//        create(name_, shader_module_, stage_type_, create_info_);
//    }
//
//    /// <summary>
//    /// VkPipelineShaderStageCreateInfo作成処理(static)
//    /// </summary>
//    /// <param name="shader_module"></param>
//    /// <param name="stage_type"></param>
//    /// <param name="out_create_info"></param>
//    void ShaderStage::create
//    (
//        const char* name,
//        const VkShaderModule& shader_module,
//        const ShaderStageType stage_type,
//        VkPipelineShaderStageCreateInfo out_create_info
//    ) {
//
//        VkPipelineShaderStageCreateInfo shader_stage_info = {};
//        shader_stage_info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
//        shader_stage_info.stage = toShaderStageFlagBits(stage_type);
//        shader_stage_info.module = shader_module;
//        shader_stage_info.pName = name;
//
//        out_create_info = shader_stage_info;
//    }
//
//    /// <summary>
//    /// ShaderStageType -> VkShaderStageFlagBitsの変換処理
//    /// </summary>
//    /// <param name="stage_type"></param>
//    VkShaderStageFlagBits ShaderStage::toShaderStageFlagBits(const ShaderStageType stage_type) {
//        switch (stage_type) {
//        case ShaderStageType::Vertex:   return VK_SHADER_STAGE_VERTEX_BIT;
//        case ShaderStageType::Fragment: return VK_SHADER_STAGE_FRAGMENT_BIT;
//        }
//        assert(false, "failed to shader stage type");
//    }
//
//} // vengine
