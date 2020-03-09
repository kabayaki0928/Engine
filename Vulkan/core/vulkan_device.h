#pragma once

#include "interface/igraphics_device.h"

namespace vengine
{
    /*
        　　┏━━━━━━━┓
       　　 ┃PhysicalDevice┃
        　　┗━━━┳━━━┛
    ┏━━━━━━━╋━━━━━━━┓
    ┃LogicalDevice1┃LogicalDevice2┃
    ┗━━━━━━━┻━━━━━━━┛
    */

    class VulkanGraphicsBackend;
    class PhysicalDeviceOwner;
    class PhysicalDevice;
    class LogicalDevice;

    /// <summary>
    /// Vulkanのデバイス関連を管理するクラス
    /// </summary>
    class VulkanDevice final : public rengine::IGraphicsDevice
    {
    private:
        std::unique_ptr<PhysicalDeviceOwner> physical_device_owner_;
        std::shared_ptr<PhysicalDevice> physical_device_;
        std::unique_ptr<LogicalDevice> logical_device_;
    public:
        VulkanDevice(std::shared_ptr<VulkanGraphicsBackend> graphics_backend);
        ~VulkanDevice();
        inline const std::shared_ptr<PhysicalDevice>* getPhysicalDevice() const noexcept {
            return &physical_device_;
        }
        inline const std::unique_ptr<LogicalDevice>* getLogicalDevice() const noexcept {
            return &logical_device_;
        }
    };
} // vengine