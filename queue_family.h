#pragma once

namespace vengine
{
    struct SwapChainSupportDetails;
    struct QueueFamilyIndices;

    class QueueFamily final
    {
    public:
        static bool isDeviceSuitable(const VkInstance& instance, const VkPhysicalDevice& physical_device, const VkSurfaceKHR& surface);
        static SwapChainSupportDetails querySwapChainSupport(const VkPhysicalDevice& physical_device, const VkSurfaceKHR& surface);
        static bool checkDeviceExtensionSupport(const VkPhysicalDevice& physical_device);
        static QueueFamilyIndices findQueueFamilies(const VkPhysicalDevice& physical_device, const VkSurfaceKHR& surface);
    };
} // vengine