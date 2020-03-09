#include "vulkan_graphics_device.h"
#include "../vulkan/core/vulkan_graphics_backend.h"

namespace vengine
{
    VulkanGraphicsDevice::VulkanGraphicsDevice(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend) {
        graphics_backend_ = graphics_backend;
        physical_device_owner_ = std::make_unique<PhysicalDeviceOwner>(graphics_backend);
        physical_device_ = physical_device_owner_->getCurrentDevice();
    }


    VulkanGraphicsDevice::~VulkanGraphicsDevice()
    {
    }

} // vengine