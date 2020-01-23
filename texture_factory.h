#pragma once

namespace rengine
{
    /// <summary>
    /// テクスチャクラスを生成するためのクラス
    /// </summary>
    class TextureFactory
    {
    public:
        TextureFactory(std::shared_ptr<ITextureBuilder> const texture_builder);
        ~TextureFactory();
    };
} // rengine

