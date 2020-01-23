#pragma once

#include "component.h"

namespace rengine
{
    class Model;
    using SpModel = std::shared_ptr<Model>;
    class Material;
    using SpMaterial = std::shared_ptr<Material>;

    /// <summary>
    /// �A�T�C�����ꂽMesh�N���X��RenderPipeline�ɏ悹�ĕ`�悷��R���|�[�l���g
    /// </summary>
    class ModelRenderer final : public cengine::Component
    {
    private:
        SpModel model_;
        SpMaterial material_;
    public:
        ModelRenderer(SpModel const mesh, SpMaterial const material);
        ~ModelRenderer();

        SpModel getSharedMesh() const noexcept { return model_; }
        SpMaterial getSharedMaterial() const noexcept { return material_; }
    };
} // rengine