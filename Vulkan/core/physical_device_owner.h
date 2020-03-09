#pragma once

#include "../vulkan/core/vulkan_graphics_backend.h"
#include "physical_device.h"

namespace vengine
{
    class VulkanGraphicsBackend;
    class PhysicalDevice;
    
    /// <summary>
    /// 物理デバイス管理用クラス
    /// </summary>
    class PhysicalDeviceOwner final
    {
    private:
        std::shared_ptr<VulkanGraphicsBackend> graphics_backend_;
        std::vector<std::shared_ptr<PhysicalDevice>> physical_devices_;
        std::shared_ptr<PhysicalDevice> current_physical_device_;
        int usedIndex = -1;

    private:
        void enumeratePhysicalDevice();
    public:
        PhysicalDeviceOwner(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend);
        ~PhysicalDeviceOwner();
        void initialize();
        std::shared_ptr<PhysicalDevice> getUnUsedDevice();
        std::shared_ptr<PhysicalDevice> getCurrentDevice();
    };
}; // vengine