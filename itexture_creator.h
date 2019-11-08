#pragma once

#include "itexture.h"

namespace rengine
{
    class Texture;

    /// <summary>
    /// �e�N�X�`���̐�������@�\�����邱�Ƃ������C���^�[�t�F�[�X
    /// </summary>
    class ITextureCreator
    {
    public:
        ~ITextureCreator() {}
        virtual  ITexture create(Texture& out_texture) = 0;

    };
} // cengine