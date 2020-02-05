#ifndef BUFFERH
#define BUFFERH

#define GLFW_INCLUDE_VULKAN

#include <glm/glm.hpp>

namespace vengine
{
    class VulkanGraphicsBackend;

    class Buffer
    {
    public:
        static void createBuffer
        (
            std::shared_ptr<VulkanGraphicsBackend> const graphics_backend,
            VkDeviceSize size,
            VkBufferUsageFlags usage,
            VkMemoryPropertyFlags properties,
            VkBuffer& buffer,
            VkDeviceMemory& buffer_memory
        );
        static void copyBuffer
        (
            std::shared_ptr<VulkanGraphicsBackend> const graphics_backend,
            const VkCommandPool& commandPool,
            const VkBuffer& src_buffer,
            const VkBuffer& dst_buffer,
            const VkDeviceSize& size,
            const VkQueue& queue
        );
    };
} // vengine

#endif