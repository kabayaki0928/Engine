#pragma once

namespace rengine
{
    class Texture;
    using SpTexture = std::shared_ptr<Texture>;
    using SpTextures = std::vector<SpTexture>;
    class vengine::Shader; // TODO rengineがvengineに依存しているのはおかしい
    using SpShader = std::shared_ptr<vengine::Shader>;

    class Material
    {
    private:
        SpTextures textures_;
        SpShader shader_;
    public:
        Material(SpShader const shader, SpTextures const textures);
        ~Material();
        
        inline SpTextures getTextures() const noexcept { return textures_; }
        inline SpShader getShader() const noexcept { return shader_; }
    };
} // rengine

