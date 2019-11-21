#pragma once

#define GLFW_INCLUDE_VULKAN
#include <glm/glm.hpp>

#include "ishader_parameter.h"

namespace vengine
{
    class VulkanGraphicsBackend;

    typedef struct ShaderModule {
        VkShaderModule module_;
        VkPipelineShaderStageCreateInfo create_info_;
        char* name_;
    } ShaderModule;

    using VertexShaderModule = ShaderModule;
    using FragmentShaderModule = ShaderModule;

    /*
    typedef enum VkShaderStageFlagBits {
        VK_SHADER_STAGE_VERTEX_BIT = 0x00000001,
        VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT = 0x00000002,
        VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT = 0x00000004,
        VK_SHADER_STAGE_GEOMETRY_BIT = 0x00000008,
        VK_SHADER_STAGE_FRAGMENT_BIT = 0x00000010,
        VK_SHADER_STAGE_COMPUTE_BIT = 0x00000020,
        VK_SHADER_STAGE_ALL_GRAPHICS = 0x0000001F,
        VK_SHADER_STAGE_ALL = 0x7FFFFFFF,
        VK_SHADER_STAGE_RAYGEN_BIT_NV = 0x00000100,
        VK_SHADER_STAGE_ANY_HIT_BIT_NV = 0x00000200,
        VK_SHADER_STAGE_CLOSEST_HIT_BIT_NV = 0x00000400,
        VK_SHADER_STAGE_MISS_BIT_NV = 0x00000800,
        VK_SHADER_STAGE_INTERSECTION_BIT_NV = 0x00001000,
        VK_SHADER_STAGE_CALLABLE_BIT_NV = 0x00002000,
        VK_SHADER_STAGE_TASK_BIT_NV = 0x00000040,
        VK_SHADER_STAGE_MESH_BIT_NV = 0x00000080,
        VK_SHADER_STAGE_FLAG_BITS_MAX_ENUM = 0x7FFFFFFF
    } VkShaderStageFlagBits;
    ↑増える可能性あり
    */
    enum ShaderStageType
    {
        VertexShader,     // 頂点シェーダー
        FragmentShader,   // フラグメントシェーダー
    };

    class Shader final
    {
    private:
        std::shared_ptr<VulkanGraphicsBackend> graphics_backend_;
        std::shared_ptr<VertexShaderModule> vertex_;
        std::shared_ptr<FragmentShaderModule> fragment_;
        std::shared_ptr<IShaderParameter> parameter_;
    public: 
        Shader
        (
            std::shared_ptr<VulkanGraphicsBackend> const graphics_backend,
            std::shared_ptr<VertexShaderModule> vertex,
            std::shared_ptr<FragmentShaderModule> fragment,
            std::shared_ptr<IShaderParameter> parameter
        );
        ~Shader();

        inline const VkShaderModule& getVertexShaderModule() const noexcept {
            return vertex_->module_;
        }

        inline const VkShaderModule& getFragmentShaderModule() const noexcept { return fragment_->module_; }
        inline const std::shared_ptr<IShaderParameter> getParameter() const noexcept { return parameter_; }
    };
} // vengine