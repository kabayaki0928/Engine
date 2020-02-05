#include "texture_loader.h"

#include "texture.h"

namespace vengine
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    TextureLoader::TextureLoader() {
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    TextureLoader::~TextureLoader() {
    }

    /// <summary>
    /// αチャンネル付きテクスチャ読み込み
    /// </summary>
    /// <param name="file_name"></param>
    /// <param name="callback"></param>
    void TextureLoader::loadWithAlpha(const char* file_name, std::function<void(texture::PixelData)> callback) {
        vengine::texture::PixelData create_info = {};
        int width = 0;
        int height = 0;
        int channels = 0;
        create_info.pixels_ = stbi_load
        (
            file_name,
            &width,
            &height,
            &channels,
            STBI_rgb_alpha
        );
        create_info.width_ = width;
        create_info.height_ = height;
        create_info.channels_ = channels;

        callback(create_info);
    }
} // vengine
