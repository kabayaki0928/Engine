#include "model_renderer.h"

#include "../vulkan/graphics_resource/model/model.h"
#include "../vulkan/graphics_resource/material/material.h"

namespace rengine
{
    /// <summary>
    /// ���f��
    /// </summary>
    /// <param name="model"></param>
    /// <param name="material"></param>
    ModelRenderer::ModelRenderer(SpModel const model, SpMaterial const material)
    : model_(model),
      material_(material) {
    }

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ModelRenderer::~ModelRenderer() {
    }
} // rengine