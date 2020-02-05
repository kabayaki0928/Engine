#pragma once

#include "itexture.h"

namespace rengine
{
    class Texture;

    /// <summary>
    /// テクスチャの生成する機能があることを示すインターフェース
    /// </summary>
    class ITextureCreator
    {
    public:
        ~ITextureCreator() {}
        virtual  ITexture create(Texture& out_texture) = 0;

    };
} // cengine