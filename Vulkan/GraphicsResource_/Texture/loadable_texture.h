#pragma once

#include "iresource_loader.h"
#include "texture.h"


namespace vengine
{
    class TextureLoader final
    {
    public:
        TextureLoader();
        ~TextureLoader();

        void load(const char* file_name, std::function<Texture> callback) override;
    };
} // vengine