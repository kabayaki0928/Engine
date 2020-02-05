#pragma once

namespace vengine
{
    /// <summary>
    /// �����f�o�C�X
    /// </summary>
    class PhysicalDevice final
    {
    private:
        VkPhysicalDevice physical_device_;
    public:
        PhysicalDevice(const VkPhysicalDevice& physical_device) {
            physical_device_ = physical_device;
        }
        ~PhysicalDevice() {
            physical_device_ = {};
        }
        inline operator const VkPhysicalDevice&() const noexcept {
            return physical_device_;
        }
    };
} // vengine