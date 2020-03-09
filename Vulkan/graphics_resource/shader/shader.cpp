#include "../vulkan/graphics_resource/shader/shader.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include "../vulkan/core/vulkan_graphics_backend.h"
#include "shader_stage.h"

namespace vengine
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="graphics_backend"></param>
    /// <param name="vertex_shader_path"></param>
    /// <param name="fragment_shader_path"></param>
    Shader::Shader
    (
        std::shared_ptr<VulkanGraphicsBackend> const graphics_backend,
        std::shared_ptr<VertexShaderModule> vertex,
        std::shared_ptr<FragmentShaderModule> fragment,
        std::shared_ptr<IShaderParameter> parameter
    )
    : graphics_backend_(graphics_backend),
      vertex_(vertex),
      fragment_(fragment),
      parameter_(parameter) {
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    Shader::~Shader() {
        auto device = graphics_backend_->getLogicalDevice();
        vkDestroyShaderModule(device, vertex_->module_, graphics_backend_->getAllocator());
        vkDestroyShaderModule(device, fragment_->module_, graphics_backend_->getAllocator());
    }


} // vengine