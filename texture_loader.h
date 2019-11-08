#pragma once

namespace vengine
{
    struct texture::PixelData;

    /// <summary>
    /// �e�N�X�`���̓ǂݍ��݊֘A���Ǘ�����N���X
    /// </summary>
    class TextureLoader final
    {
    public:
        TextureLoader();
        ~TextureLoader();

        void loadWithAlpha(const char* file_name, std::function<void(texture::PixelData)> callback);
    };
} // vengine

