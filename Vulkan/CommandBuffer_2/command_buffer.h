#ifndef COMMAND_BUFFERH
#define COMMAND_BUFFERH

#define GLFW_INCLUDE_VULKAN

#include <glm/glm.hpp>

namespace vengine
{
    class VulkanGraphicsBackend;

    typedef struct ExecutableCommandBufferData {
        std::shared_ptr<VulkanGraphicsBackend> graphics_backend_;
        const VkCommandPool& command_pool_;
        const VkQueue& queue_;
    } ExecutableCommandBufferData;

    /// <summary>
    /// VkCommandBuffer�֘A�̏������܂Ƃ߂Ă���N���X
    /// TODO �g�����肪�����̂Ń��t�@�N�^�z��
    /// �����A�ŏI�I�Ȍ`�������Ă��ĂȂ��̂ň�U�G�ɂ܂Ƃ߂�
    /// </summary>
    class CommandBuffer final
    {
    private:
        VkCommandBuffer commandBuffer;
    public:
        static VkCommandBuffer beginSingleTimeCommands
        (
            const ExecutableCommandBufferData& data
        );
        static void endSingleTimeCommands
        (
            const ExecutableCommandBufferData& data,
            VkCommandBuffer& const command_buffer
        );
        static void generateMipmaps
        (
            const ExecutableCommandBufferData& data,
            VkCommandBuffer& const command_buffer,
            VkImage image,
            VkFormat image_format,
            int32_t width,
            int32_t height,
            uint32_t mip_levels
        );
        static void transitionImageLayout
        (
            const ExecutableCommandBufferData& data,
            VkCommandBuffer& const command_buffer,
            VkImage image,
            VkFormat format,
            VkImageLayout oldLayout,
            VkImageLayout newLayout,
            uint32_t mipLevels
        );
        static void copyBufferToImage
        (
            const ExecutableCommandBufferData& data,
            VkCommandBuffer& const command_buffer,
            VkBuffer buffer,
            VkImage image,
            uint32_t width,
            uint32_t height
        );
    };
} // vengine


#endif