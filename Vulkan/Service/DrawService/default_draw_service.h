#pragma once

#include "idraw_service.h"

namespace rengine
{
    /// <summary>
    /// 描画ルーチンへのアクセスを提供するための一般的なクラス
    /// リストに追加して削除して取得ができるだけの機能を持つ
    /// </summary>
    class DefaultDrawService final : public IDrawService
    {
    private:
        SpModelRendererList buffer_list_;
    public:
        DefaultDrawService();
        ~DefaultDrawService();

        void add(SpModelRenderer const renderer) noexcept override;
        void remove(SpModelRenderer const renderer) noexcept override;
        SpModelRendererList get() const noexcept override;
    };
} // rengine

