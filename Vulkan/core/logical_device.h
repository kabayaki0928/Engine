#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace vengine
{
    class VulkanGraphicsBackend;
    class PhysicalDevice;
    class Surface;

    /// <summary>
    /// 論理デバイス
    /// <para>物理デバイスと関連している</para>
    /// </summary>
    class LogicalDevice final
    {
    private:
        std::shared_ptr<VulkanGraphicsBackend> graphics_backend_;
        std::shared_ptr<PhysicalDevice> physical_device_;
        VkDevice device_;

    public:
        LogicalDevice
        (
            std::shared_ptr<VulkanGraphicsBackend> const graphics_backend,
            std::shared_ptr<PhysicalDevice> const physical_device
        );
        ~LogicalDevice();

        void create();
        static void create(VkDevice* device, const PhysicalDevice& physical_device, const Surface& surface);

        //----------------------------------------------------
        // operator群
        operator VkDevice&() noexcept {
            return device_;
        }
        operator const VkDevice&() const noexcept {
            return device_;
        }
    };
} // vengine