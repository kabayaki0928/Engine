#pragma once

namespace rengine
{
    /// <summary>
    /// 描画を行う機能があることを示すインターフェース
    /// </summary>
    class IRenderPipeline
    {
    public:
        virtual void initialize() = 0;
        virtual void draw() = 0;
    };
} // rengine