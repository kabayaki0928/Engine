#pragma once

#include "igraphics_instance.h"
#include "igraphics_handle.h"

namespace rengine
{
    /// <summary>
    /// �eGraphicsAPI���̃C���X�^���X
    /// </summary>
    //class GraphicsInstance final : public IGraphicsHandle
    //{
    //private:
    //    std::unique_ptr<IGraphicsInstance> graphics_instance_;
    //public:
    //    /// <summary>
    //    /// �R���X�g���N�^
    //    /// </summary>
    //    /// <param name="graphicsInstance">�eGraphicsAPI��Instance</param>
    //    GraphicsInstance(const IGraphicsInstance* graphicsInstance) {
    //        graphics_instance_ = std::make_unique<IGraphicsInstance>(graphicsInstance);
    //    }
    //    /// <summary>
    //    /// �f�X�g���N�^
    //    /// </summary>
    //    ~GraphicsInstance() {
    //        graphics_instance_.reset();
    //    }
    //    const IGraphicsInstance* operator -> () const noexcept {
    //        return graphics_instance_.get();
    //    }
    //};
}