#pragma once

namespace rengine
{
    /// <summary>
    /// Swapchain�֘A�̋@�\�����邱�Ƃ������C���^�[�t�F�[�X
    /// </summary>
    class ISwapchain
    {
    public:
        ~ISwapchain() {};
        virtual const VkExtent2D& getExtent() const noexcept = 0;
        virtual float getWidth() const noexcept = 0;
        virtual float getHeight() const noexcept = 0;
    };
} // rengine