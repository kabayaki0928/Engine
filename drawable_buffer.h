#ifndef DRAWABLE_BUFFERH
#define DRAWABLE_BUFFERH

#define GLFW_INCLUDE_VULKAN

#include <glm/glm.hpp>

namespace vengine
{
    namespace {
        typedef struct Data {
            VkBuffer buffer_;
            VkDeviceMemory buffer_memory_;
        } Data;
    }

    class VulkanGraphicsBackend;
    class Vertex;

    /// <summary>
    /// 描画コマンドを実行するために必要なバッファ関連を管理するクラス
    /// とりあえず頂点バッファとインデックスバッファを持っている
    /// 若干抽象度を上げておきたい気もする(気がしているだけかもしれない)
    /// ゆくゆくはrengine側に移動させたい
    /// </summary>
    class DrawableBuffer final
    {
    private:
        std::shared_ptr<VulkanGraphicsBackend> graphics_backend_;
        std::vector<Vertex> vertices_;
        std::vector<uint32_t> indices_;
        Data vertex_data_;
        Data index_data_;

    public:
        DrawableBuffer
        (
            std::shared_ptr<VulkanGraphicsBackend> const graphics_backend,
            std::vector<Vertex> vertices,
            std::vector<uint32_t> indices
        ) {
            this->vertices_ = vertices;
            this->indices_ = indices;
        }
        ~DrawableBuffer() {
            vertices_.clear();
            indices_.clear();
        }

        void create();
        static void createVertexBuffer
        (
            std::shared_ptr<VulkanGraphicsBackend> graphics_backend,
            const std::vector<Vertex>& vertices,
            Data out_data
        );
        static void createIndexBuffer
        (
            std::shared_ptr<VulkanGraphicsBackend> graphics_backend,
            const std::vector<uint32_t>& indices,
            Data out_data
        );
        static void createUniformBuffer
        (

        ) {
            //VkDeviceSize bufferSize = sizeof(UniformBufferObject);

            //uniformBuffers.resize(swapChainImages.size());
            //uniformBuffersMemory.resize(swapChainImages.size());

            //for (size_t i = 0; i < swapChainImages.size(); i++) {
            //    createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffers[i], uniformBuffersMemory[i]);
            //}
        }
        static void createBuffer
        (
            std::shared_ptr<VulkanGraphicsBackend> graphics_backend,
            VkDeviceSize buffer_size,
            VkBufferUsageFlags src_buffer_usage_flags,
            VkBufferUsageFlags dst_buffer_usage_flags,
            VkMemoryPropertyFlags src_memory_property_usage_flags,
            VkMemoryPropertyFlags dst_memory_property_usage_flags,
            void const* mem_cpy_data,
            Data out_data
        );
    }
} // vengine

#endif