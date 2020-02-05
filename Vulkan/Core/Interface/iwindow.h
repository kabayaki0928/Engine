#pragma once

namespace rengine
{
    /// <summary>
    /// �E�B���h�E�ɕK�v�ȋ@�\�������C���^�[�t�F�[�X
    /// </summary>
    class IWindow
    {
    public:
        virtual void create() = 0;
        virtual bool isShouldClose() const = 0;
        virtual bool isFrameBufferResized() const noexcept = 0;
    };
} // EEngine