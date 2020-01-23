#include "draw_service.h"

#include "idraw_service.h"

namespace rengine
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    DrawService::DrawService(const IDrawService* service)
    : service_(std::make_shared<IDrawService>(service)) {

    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    DrawService::~DrawService() {
        service_ = nullptr;
    }

    /// <summary>
    /// 描画対象として登録
    /// </summary>
    /// <param name="renderer"></param>
    /// <returns></returns>
    void DrawService::add(SpModelRenderer const renderer) noexcept {
        service_->add(renderer);
    }

    /// <summary>
    /// 描画対象から削除
    /// </summary>
    /// <param name="renderer"></param>
    /// <returns></returns>
    void DrawService::remove(SpModelRenderer const renderer) noexcept {
        service_->remove(renderer);
    }

    /// <summary>
    /// 描画対象を取得
    /// </summary>
    /// <returns></returns>
    SpModelRendererList DrawService::get() noexcept {
        return service_->get();
    }

} // rengine
