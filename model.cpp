#include "model.h"

#include "vulkan_graphics_backend.h"

#include "drawable_buffer.h"
#include "shader.h"


namespace rengine
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <returns></returns>
    Model::Model
    (
        std::shared_ptr<DrawableBuffer> const drawable_buffer,
        std::vector<std::shared_ptr<Texture>> textures,
        std::shared_ptr<Shader> shader
    ) : drawable_buffer_(drawable_buffer),
        textures_(textures),
        shader_(shader) {

    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    /// <returns></returns>
    Model::~Model() {
        drawable_buffer_.reset();
        for (auto& texture : textures_) {
            texture.reset();
        }
        textures_.clear();
        shader_.reset();
    }

} // vengine