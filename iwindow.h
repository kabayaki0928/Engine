#pragma once

namespace rengine
{
    /// <summary>
    /// ウィンドウに必要な機能を示すインターフェース
    /// </summary>
    class IWindow
    {
    public:
        virtual void create() = 0;
        virtual bool isShouldClose() const = 0;
        virtual bool isFrameBufferResized() const noexcept = 0;
    };
} // EEngine