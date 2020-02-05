#include "model.h"

#include "vulkan_graphics_backend.h"

#include "drawable_buffer.h"
#include "shader.h"

namespace rengine
{
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Model::Model
    (
        std::shared_ptr<DrawableBuffer> const drawable_buffer,
        std::shared_ptr<Material> const material
    ) : drawable_buffer_(drawable_buffer),
        material_(material) {
    }

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    /// <returns></returns>
    Model::~Model() {
        drawable_buffer_ = nullptr;
        material_ = nullptr;
    }

} // vengine