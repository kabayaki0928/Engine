#ifndef MEMORY_UTILSH
#define MEMORY_UTILSH

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>

namespace vengine
{
    namespace memory_utils
    {
        static uint32_t findMemoryType
        (
            const VkPhysicalDevice& physicalDevice,
            uint32_t typeFilter,
            VkMemoryPropertyFlags properties
        ) {
            VkPhysicalDeviceMemoryProperties memProperties;
            vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memProperties);

            for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
                if ((typeFilter & (1 << i))
                    && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
                    return i;
                }
            }

            throw std::runtime_error("failed to find suitable memory type!");
        }
    };
} // vengine
#endif