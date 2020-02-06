#pragma once

#include "iloader.h"

namespace vengine
{
    class ModelLoader;
    class ShaderLoader;
    class TextureLoader;
    class VulkanGraphicsBackend;

    /// <summary>
    /// �Œ���̋@�\���������ǂݍ��݊Ǘ��p�N���X
    /// </summary>
    class SimpleLoader final : public rengine::ILoader
    {
    private:
        std::unique_ptr<ModelLoader> model_loader_;
        std::unique_ptr<ShaderLoader> shader_loader_;
        std::unique_ptr<TextureLoader> texture_loader_;
    public:
        SimpleLoader(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend);
        ~SimpleLoader();
        template<typename T>
        void load(const char* file_name, std::function<void(T)> callback) override;
    };
} // rengine
