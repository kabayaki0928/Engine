#pragma once

namespace rengine
{
    /// <summary>
    /// ���C�����[�v�̋@�\���������C���^�[�t�F�[�X
    /// </summary>
    class IMainLoop
    {
    public:
        virtual void initialize() = 0;
        virtual void run() = 0;
    };

} // rengine