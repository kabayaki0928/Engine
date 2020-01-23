#include "default_draw_service.h"

#include "model_renderer.h"
#include "idraw_service.h"

namespace rengine
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    DefaultDrawService::DefaultDrawService()
    : buffer_list_(100) {
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    DefaultDrawService::~DefaultDrawService() {
        SpModelRendererList().swap(buffer_list_);
    }

    /// <summary>
    /// 追加
    /// </summary>
    /// <param name="drawable_buffer"></param>
    void DefaultDrawService::add(SpModelRenderer const renderer) {
        buffer_list_.emplace_back(renderer);
    }

    /// <summary>
    /// 削除
    /// </summary>
    /// <param name="renderer"></param>
    void DefaultDrawService::remove(SpModelRenderer const renderer) {
        // TODO 即時破棄しているもののこのタイミングではnullptrだけ入れておいて
        // 開票できるタイミングで開放するという方法でもいいかもしれない
        // あくまでdefaultなので拡張が必要そうならそっちで対応する
        for (auto itr = buffer_list_.begin(); itr != buffer_list_.end(); itr++) {
            if (*(itr) == renderer) {
                buffer_list_.erase(itr);
                break;
            }
        }
        // でもいいものの重複する要素は入らない想定なので一旦上記のままで
        // buffer_list_.erase(std::remove(buffer_list_.begin(), buffer_list_.end(), renderer));
    }

    /// <summary>
    /// 取得
    /// </summary>
    /// <returns></returns>
    SpModelRendererList DefaultDrawService::get() const noexcept {
        return buffer_list_;
    }
    
} // rengine
