#pragma once

#include "iwindow.h"
#include "igraphics_instance.h"
#include "igraphics_device.h"
#include "isurface.h"
#include "iswapchain.h"

namespace rengine
{
    /// <summary>
    /// 各GraphicsAPIへアクセスするためのBackEndインターフェース
    /// </summary>
    class IGraphicsBackend
    {
    public:
        ~IGraphicsBackend() {};
        inline virtual const IWindow* getWindow() const noexcept = 0;
        inline virtual const IGraphicsInstance* getInstance() const noexcept = 0;
        inline virtual const IGraphicsDevice* getDevice() const noexcept = 0;
        inline virtual const ISurface* getSurface() const noexcept = 0;
        inline virtual const ISwapchain* getSwapchain() const noexcept = 0;

        virtual void initialize() = 0;
        virtual void recreateSwapchain() = 0;

        //virtual void init() = 0;
        //virtual void recreateSwapchain() = 0;
        //virtual void cleanupSwapchain() = 0;
        //virtual void cleanup() = 0;
        //virtual void drawFrame() = 0;
    };
} // rengine
