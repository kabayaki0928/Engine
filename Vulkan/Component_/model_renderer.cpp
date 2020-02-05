#include "model_renderer.h"

#include "model.h"
#include "material.h"

namespace rengine
{
    /// <summary>
    /// モデル
    /// </summary>
    /// <param name="model"></param>
    /// <param name="material"></param>
    ModelRenderer::ModelRenderer(SpModel const model, SpMaterial const material)
    : model_(model),
      material_(material) {
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    ModelRenderer::~ModelRenderer() {
    }
} // rengine