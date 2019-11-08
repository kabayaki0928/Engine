#ifndef IMAGE_VIEWH
#define IMAGE_VIEWH

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace vengine
{
    class VulkanGraphicsBackend;

    /// <summary>
    /// 
    /// </summary>
    class ImageView
    {
    private:
        std::shared_ptr<VulkanGraphicsBackend> graphics_backend_;
        VkImage image_;
        VkImageView image_view_;

    public:
        ImageView(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend);
        ~ImageView();

        //static void create();

        /// <summary>
        /// Imageの作成処理
        /// </summary>
        /// <param name="image"></param>
        void create(const VkImage& image) {
            // TODO 実装
        }

        /// <summary>
        /// VkImageの作成
        /// </summary>
        /// <param name="width">横幅</param>
        /// <param name="height">縦幅</param>
        /// <param name="mipLevels">mipmapをどの段階のもので生成するか</param>
        /// <param name="numSamples"></param>
        /// <param name="format"></param>
        /// <param name="tiling"></param>
        /// <param name="usage"></param>
        /// <param name="properties"></param>
        /// <param name="image"></param>
        /// <param name="imageMemory"></param>
        static void createImage
        (
            std::shared_ptr<VulkanGraphicsBackend> const graphics_backend,
            uint32_t width,
            uint32_t height,
            uint32_t mipLevels,
            VkSampleCountFlagBits numSamples,
            VkFormat format,
            VkImageTiling tiling,
            VkImageUsageFlags usage,
            VkMemoryPropertyFlags properties,
            VkImage& image,
            VkDeviceMemory& imageMemory
        );

        /// <summary>
        /// VkImageの作成処理
        /// </summary>
        /// <param name="device"></param>
        /// <param name="image"></param>
        /// <param name="format"></param>
        /// <param name="aspectFlags"></param>
        /// <param name="mipLevels"></param>
        /// <param name="outViewImage"></param>
        static void createImageView
        (
            std::shared_ptr<VulkanGraphicsBackend> const graphics_backend,
            const VkImage& image,
            const VkFormat& format,
            const VkImageAspectFlags& aspectFlags,
            const uint32_t& mipLevels,
            VkImageView& outViewImage
        );
    };

} // vengine

#endif