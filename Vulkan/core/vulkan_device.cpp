#include "vulkan_device.h"

#include "../vulkan/core/vulkan_graphics_backend.h"
#include "physical_device_owner.h"
#include "physical_device.h"
#include "logical_device.h"

namespace vengine
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="physical_device_owner"></param>
    /// <param name="physical_device"></param>
    /// <param name="logical_device"></param>
    VulkanDevice::VulkanDevice(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend)
      : physical_device_owner_(std::make_unique<PhysicalDeviceOwner>(graphics_backend)),
        physical_device_(physical_device_owner_->getCurrentDevice()),
        logical_device_(std::make_unique<LogicalDevice>(graphics_backend, physical_device_))
    {
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    VulkanDevice::~VulkanDevice() {
        physical_device_owner_.reset();
        physical_device_.reset();
        logical_device_.reset();
    }
} // vengine