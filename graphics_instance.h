#pragma once

#include "igraphics_instance.h"
#include "igraphics_handle.h"

namespace rengine
{
    /// <summary>
    /// 各GraphicsAPI毎のインスタンス
    /// </summary>
    //class GraphicsInstance final : public IGraphicsHandle
    //{
    //private:
    //    std::unique_ptr<IGraphicsInstance> graphics_instance_;
    //public:
    //    /// <summary>
    //    /// コンストラクタ
    //    /// </summary>
    //    /// <param name="graphicsInstance">各GraphicsAPIのInstance</param>
    //    GraphicsInstance(const IGraphicsInstance* graphicsInstance) {
    //        graphics_instance_ = std::make_unique<IGraphicsInstance>(graphicsInstance);
    //    }
    //    /// <summary>
    //    /// デストラクタ
    //    /// </summary>
    //    ~GraphicsInstance() {
    //        graphics_instance_.reset();
    //    }
    //    const IGraphicsInstance* operator -> () const noexcept {
    //        return graphics_instance_.get();
    //    }
    //};
}