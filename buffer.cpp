#include "buffer.h"

#include "command_buffer.h"
#include "memory_utils.h"
#include "vulkan_graphics_backend.h"
#include "vulkan_utils.h"

namespace vengine
{
    void Buffer::createBuffer
    (
        std::shared_ptr<VulkanGraphicsBackend> const graphics_backend,
        VkDeviceSize size,
        VkBufferUsageFlags usage,
        VkMemoryPropertyFlags properties,
        VkBuffer& buffer,
        VkDeviceMemory& buffer_memory
    ) {
        VkBufferCreateInfo buffer_info = {};

        buffer_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
        buffer_info.size = size;
        buffer_info.usage = usage;
        buffer_info.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        auto device = graphics_backend->getLogicalDevice();
        auto physical_device = graphics_backend->getPhysicalDevice();

        VkResult result = vkCreateBuffer(device, &buffer_info, nullptr, &buffer);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to create vertex buffer");
        }

        VkMemoryRequirements memory_requirements;
        vkGetBufferMemoryRequirements(device, buffer, &memory_requirements);

        VkPhysicalDeviceMemoryProperties memory_properties;
        vkGetPhysicalDeviceMemoryProperties(physical_device, &memory_properties);

        VkMemoryAllocateInfo alloc_info = {};
        alloc_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        alloc_info.allocationSize = memory_requirements.size;
        alloc_info.memoryTypeIndex = memory_utils::findMemoryType(physical_device, memory_requirements.memoryTypeBits, properties);

        result = vkAllocateMemory(device, &alloc_info, nullptr, &buffer_memory);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate vertex buffer memory!");
        }

        vkBindBufferMemory(device, buffer, buffer_memory, 0);
    }
    
    void Buffer::copyBuffer
    (
        std::shared_ptr<VulkanGraphicsBackend> graphics_backend,
        const VkCommandPool& command_pool,
        const VkBuffer& src_buffer,
        const VkBuffer& dst_buffer,
        const VkDeviceSize& size,
        const VkQueue& queue
    ) {
        VkCommandBufferAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = command_pool;
        allocInfo.commandBufferCount = 1;

        VkCommandBuffer command_buffer = {};
        ExecutableCommandBufferData data = { graphics_backend, command_pool, command_buffer, queue };

        command_buffer = CommandBuffer::beginSingleTimeCommands(data);
        {
            VkBufferCopy copyRegion = {};
            copyRegion.size = size;
            vkCmdCopyBuffer(command_buffer, src_buffer, dst_buffer, 1, &copyRegion);
        }
        CommandBuffer::endSingleTimeCommands(data);
    }
} // vengine