
#include "queue_family.h"
#include "vulkan_utils.h"
#include "user_define.h"

namespace vengine
{
    /// <summary>
    /// 
    /// </summary>
    /// <param name="instance"></param>
    /// <param name="physical_device"></param>
    /// <param name="surface"></param>
    /// <returns></returns>
    bool QueueFamily::isDeviceSuitable(const VkInstance& instance, const VkPhysicalDevice& physical_device, const VkSurfaceKHR& surface) {
        QueueFamilyIndices indices = findQueueFamilies(physical_device, surface);

        bool extensionsSupported = checkDeviceExtensionSupport(physical_device);

        bool swapChainAdequate = false;
        if (extensionsSupported) {
            SwapChainSupportDetails swapChainSupport = querySwapChainSupport(physical_device, surface);
            swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
        }

        VkPhysicalDeviceFeatures supportedFeatures;
        vkGetPhysicalDeviceFeatures(physical_device, &supportedFeatures);

        return indices.isComplete() && extensionsSupported && swapChainAdequate && supportedFeatures.samplerAnisotropy;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="physicalDevice"></param>
    /// <param name="surface"></param>
    /// <returns></returns>
    SwapChainSupportDetails QueueFamily::querySwapChainSupport(const VkPhysicalDevice& physicalDevice, const VkSurfaceKHR& surface) {
        SwapChainSupportDetails details;

        vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &details.capabilities);

        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, nullptr);

        if (formatCount != 0) {
            details.formats.resize(formatCount);
            vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &formatCount, details.formats.data());
        }

        uint32_t presentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, nullptr);

        if (presentModeCount != 0) {
            details.presentModes.resize(presentModeCount);
            vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, details.presentModes.data());
        }

        return details;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="physical_device"></param>
    /// <returns></returns>
    bool QueueFamily::checkDeviceExtensionSupport(const VkPhysicalDevice& physical_device) {
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(physical_device, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(physical_device, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> requiredExtensions(user_define::deviceExtensions.begin(), user_define::deviceExtensions.end());

        for (const auto& extension : availableExtensions) {
            requiredExtensions.erase(extension.extensionName);
        }

        return requiredExtensions.empty();
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="physical_device"></param>
    /// <param name="surface"></param>
    /// <returns></returns>
    QueueFamilyIndices QueueFamily::findQueueFamilies(const VkPhysicalDevice& physical_device, const VkSurfaceKHR& surface) {
        QueueFamilyIndices indices;

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(physical_device, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        for (const auto& queueFamily : queueFamilies) {
            if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices.graphicsFamily = i;
            }

            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(physical_device, i, surface, &presentSupport);

            if (queueFamily.queueCount > 0 && presentSupport) {
                indices.presentFamily = i;
            }

            if (indices.isComplete()) {
                break;
            }

            i++;
        }

        return indices;
    }
} // vengine