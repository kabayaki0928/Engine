#pragma once

namespace rengine
{
    /// <summary>
    /// MainLoop��Ŏ��s�����@�\�����C���^�[�t�F�[�X
    /// </summary>
    class IMainCode
    {
    public:
        ~IMainCode() {}

        virtual void initialize() = 0;
        virtual void update() = 0;
        // TODO lateUpdate�H
        // TODO fixedUpdate�H
        virtual void prepareDraw() = 0;
        virtual void lateDraw() = 0;
    };
} // rengine