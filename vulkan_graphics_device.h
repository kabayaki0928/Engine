#pragma once
#include "igraphics_handle.h"
#include "physical_device_owner.h"
#include "physical_device.h"
#include "logical_device.h"

namespace vengine
{
    using namespace rengine;

    /// <summary>
    /// Vulkanのデバイス関連を管理するクラス
    /// </summary>
    class VulkanGraphicsDevice final : public IGraphicsHandle
    {
    private:
        std::shared_ptr<VulkanGraphicsBackend> graphics_backend_;
        std::unique_ptr<PhysicalDeviceOwner> physical_device_owner_;
        std::shared_ptr<PhysicalDevice> physical_device_;
        std::unique_ptr<LogicalDevice> logical_device_;
    public:
        VulkanGraphicsDevice(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend);
        ~VulkanGraphicsDevice();
    };
} // vengine

