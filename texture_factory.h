#pragma once

namespace rengine
{
    /// <summary>
    /// �e�N�X�`���N���X�𐶐����邽�߂̃N���X
    /// </summary>
    class TextureFactory
    {
    public:
        TextureFactory(std::shared_ptr<ITextureBuilder> const texture_builder);
        ~TextureFactory();
    };
} // rengine

