#include "shader.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>
#include "vulkan_graphics_backend.h"
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
        std::shared_ptr<FragmentShaderModule> fragment
    )
    : graphics_backend_(graphics_backend),
      vertex_(vertex),
      fragment_(fragment) {
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    Shader::~Shader() {
        auto device = graphics_backend_->getLogicalDevice();
        vkDestroyShaderModule(device, vertex_->module_, nullptr);
        vkDestroyShaderModule(device, fragment_->module_, nullptr);
    }


} // vengine