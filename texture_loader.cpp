#include "texture_loader.h"

#include <stb_image.h>

#include "texture.h"

namespace vengine
{
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    TextureLoader::TextureLoader() {
    }

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    TextureLoader::~TextureLoader() {
    }

    /// <summary>
    /// ���`�����l���t���e�N�X�`���ǂݍ���
    /// </summary>
    /// <param name="file_name"></param>
    /// <param name="callback"></param>
    void TextureLoader::loadWithAlpha(const char* file_name, std::function<void(texture::PixelData)> callback) {
        texture::PixelData create_info = {};
        create_info.pixels_ = stbi_load
        (
            file_name,
            &create_info.width_,
            &create_info.height_,
            &create_info.channels_,
            STBI_rgb_alpha
        );

        callback(create_info);
    }
} // vengine
