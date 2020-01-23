#pragma once

#include "itexture_builder.h"

namespace vengine
{
    class VulkanGraphicsBackend;

    /// <summary>
    /// Vulkan�g�p���Ƀe�N�X�`�����K�v�ȏ������܂Ƃ߂��N���X
    /// </summary>
    class VulkanTextureBuilder : ITextureBuilder
    {
    public:
        VulkanTextureBuilder(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend);
        ~VulkanTextureBuilder();
    };
} // vengine

