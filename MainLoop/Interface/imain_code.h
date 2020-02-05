#pragma once

namespace rengine
{
    /// <summary>
    /// MainLoop上で実行される機能を持つインターフェース
    /// </summary>
    class IMainCode
    {
    public:
        ~IMainCode() {}

        virtual void initialize() = 0;
        virtual void update() = 0;
        // TODO lateUpdate？
        // TODO fixedUpdate？
        virtual void prepareDraw() = 0;
        virtual void lateDraw() = 0;
    };
} // rengine