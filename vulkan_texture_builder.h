#pragma once

#include "itexture_builder.h"

namespace vengine
{
    class VulkanGraphicsBackend;

    /// <summary>
    /// Vulkan使用時にテクスチャ毎必要な処理をまとめたクラス
    /// </summary>
    class VulkanTextureBuilder : ITextureBuilder
    {
    public:
        VulkanTextureBuilder(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend);
        ~VulkanTextureBuilder();
    };
} // vengine

