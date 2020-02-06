#pragma once

namespace rengine
{
    class IDrawService;
    class ModelRenderer;
    using SpModelRenderer = std::shared_ptr<ModelRenderer>;
    using SpModelRendererList = std::vector<SpModelRenderer>;

    /// <summary>
    /// 描画機能を提供するクラス
    /// </summary>
    class DrawService
    {
    private:
        std::shared_ptr<IDrawService> service_;
    public:
        DrawService(const IDrawService* service);
        ~DrawService();

        void add(SpModelRenderer const renderer) noexcept;
        void remove(SpModelRenderer const renderer) noexcept;
        SpModelRendererList get() noexcept;
    };
} // rengine

