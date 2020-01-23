#include "model.h"

#include "vulkan_graphics_backend.h"

#include "drawable_buffer.h"
#include "shader.h"

namespace rengine
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Model::Model
    (
        std::shared_ptr<DrawableBuffer> const drawable_buffer,
        std::shared_ptr<Material> const material
    ) : drawable_buffer_(drawable_buffer),
        material_(material) {
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    /// <returns></returns>
    Model::~Model() {
        drawable_buffer_ = nullptr;
        material_ = nullptr;
    }

} // vengine