#pragma once

namespace rengine
{
    class ModelRenderer;
    using SpModelRenderer = std::shared_ptr<ModelRenderer>;
    using SpModelRendererList = std::vector<SpModelRenderer>;

    /// <summary>
    /// 描画ルーチンへのアクセスをするためのインターフェース
    /// </summary>
    class IDrawService
    {
    public:
        ~IDrawService() { }

        virtual void add(SpModelRenderer const renderer) noexcept = 0;
        virtual void remove(SpModelRenderer const renderer) noexcept = 0;
        virtual SpModelRendererList get() const noexcept = 0;
    };
} // rengine