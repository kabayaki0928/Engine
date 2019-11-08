#include "drawable_buffer.h"

#include "buffer.h"
#include "Vertex.h"
#include "vulkan_graphics_backend.h"
#include "vulkan_utils.h"

namespace vengine
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="graphics_backend"></param>
    /// <param name="vertices"></param>
    /// <param name="indices"></param>
    DrawableBuffer::DrawableBuffer(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend, std::vector<Vertex> vertices, std::vector<uint32_t> indices)
    : graphics_backend_(graphics_backend),
      vertices_(vertices),
      indices_(indices) {
        create();
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    DrawableBuffer::~DrawableBuffer() {

    }

    /// <summary>
    /// 頂点バッファ、インデックスバッファをCommandBufferで使用する形式で生成
    /// </summary>
    void DrawableBuffer::create() {
        DrawableBuffer::createVertexBuffer(graphics_backend_, vertices_, vertex_data_);
        DrawableBuffer::createIndexBuffer(graphics_backend_, indices_, index_data_);
    }

    /// /// <summary>
    /// 頂点バッファ
    /// </summary>
    /// <param name="graphics_backend"></param>
    /// <param name="vertices"></param>
    /// <param name="out_data"></param>
    void DrawableBuffer::createVertexBuffer
    (
        std::shared_ptr<VulkanGraphicsBackend> graphics_backend,
        const std::vector<Vertex>& vertices,
        Data out_data
    ) {
        VkDeviceSize buffer_size = sizeof(vertices_[0]) * vertices.size();
        static VkBufferUsageFlags src_buffer_usage_flags = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
        static VkBufferUsageFlags dst_buffer_usage_flags = VK_BUFFER_USAGE_TRANSFER_DST_BIT
                                                         | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
        static VkMemoryPropertyFlags src_memory_property_usage_flags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
                                                                     | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
        static VkMemoryPropertyFlags dst_memory_property_usage_flags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

        DrawableBuffer::createBuffer
        (
            graphics_backend,
            buffer_size,
            src_buffer_usage_flags,
            dst_buffer_usage_flags,
            src_memory_property_usage_flags,
            dst_memory_property_usage_flags,
            vertices.data(),
            out_data
        );
    }

    void DrawableBuffer::createIndexBuffer
    (
        std::shared_ptr<VulkanGraphicsBackend> graphics_backend,
        const std::vector<uint32_t>& indices,
        Data out_data
    ) {
        VkDeviceSize buffer_size = sizeof(indices_[0]) * indices.size();

        static VkBufferUsageFlags src_buffer_usage_flags = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
        static VkBufferUsageFlags dst_buffer_usage_flags = VK_BUFFER_USAGE_TRANSFER_DST_BIT
                                                         | VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
        static VkMemoryPropertyFlags src_memory_property_usage_flags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
                                                                     | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
        static VkMemoryPropertyFlags dst_memory_property_usage_flags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

        DrawableBuffer::createBuffer
        (
            graphics_backend,
            buffer_size,
            src_buffer_usage_flags,
            dst_buffer_usage_flags,
            src_memory_property_usage_flags,
            dst_memory_property_usage_flags,
            indices.data(),
            out_data
        );
    }

    /// <summary>
    /// 頂点バッファ
    /// </summary>
    /// <param name="graphics_backend"></param>
    /// <param name="vertices"></param>
    /// <param name="out_data"></param>
    void DrawableBuffer::createBuffer
    (
        std::shared_ptr<VulkanGraphicsBackend> graphics_backend,
        VkDeviceSize buffer_size,
        VkBufferUsageFlags src_buffer_usage_flags,
        VkBufferUsageFlags dst_buffer_usage_flags,
        VkMemoryPropertyFlags src_memory_property_usage_flags,
        VkMemoryPropertyFlags dst_memory_property_usage_flags,
        void const* mem_cpy_data,
        Data out_data
    ) {
        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;

        Buffer::createBuffer(graphics_backend, buffer_size, src_buffer_usage_flags, src_memory_property_usage_flags, stagingBuffer, stagingBufferMemory);

        auto device = graphics_backend->getLogicalDevice();
        void* data;
        vkMapMemory(device, stagingBufferMemory, 0, buffer_size, 0, &data);
        memcpy(data, mem_cpy_data, (size_t)buffer_size);
        vkUnmapMemory(device, stagingBufferMemory);

        Buffer::createBuffer(graphics_backend, buffer_size, dst_buffer_usage_flags, dst_memory_property_usage_flags, out_data.buffer_, out_data.buffer_memory_);
        //Buffer::copyBuffer(container, commandPool, stagingBuffer, vertexBuffer, bufferSize, graphicsQueue);

        vkDestroyBuffer(device, stagingBuffer, nullptr);
        vkFreeMemory(device, stagingBufferMemory, nullptr);
    }


} // vengine
