#pragma once

namespace rengine
{
    /// <summary>
    /// メインループの機能を示したインターフェース
    /// </summary>
    class IMainLoop
    {
    public:
        virtual void initialize() = 0;
        virtual void run() = 0;
    };

} // rengine