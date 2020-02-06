#pragma once

namespace rengine
{
    /// <summary>
    /// �`����s���@�\�����邱�Ƃ������C���^�[�t�F�[�X
    /// </summary>
    class IRenderPipeline
    {
    public:
		~IRenderPipeline() { }
        virtual void initialize() = 0;
        virtual void draw() = 0;
    };
} // rengine