#pragma once

namespace vengine
{
    struct texture::PixelData;

    /// <summary>
    /// テクスチャの読み込み関連を管理するクラス
    /// </summary>
    class TextureLoader final
    {
    public:
        TextureLoader();
        ~TextureLoader();

        void loadWithAlpha(const char* file_name, std::function<void(texture::PixelData)> callback);
    };
} // vengine

