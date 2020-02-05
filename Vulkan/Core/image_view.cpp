#include "image_view.h"

#include "vulkan_graphics_backend.h"
#include "memory_utils.h"

namespace vengine
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="graphics_backend"></param>
    ImageView::ImageView(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend) {
        graphics_backend_ = graphics_backend;


    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    ImageView::~ImageView() {
        // 数が多い場合は内部(VulkanGraphicsBackend側)においてもいいやも
        vkDestroyImage(graphics_backend_->getLogicalDevice(), image_, graphics_backend_->getAllocator());
        vkDestroyImageView(graphics_backend_->getLogicalDevice(), image_view_, graphics_backend_->getAllocator());
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="graphics_backend"></param>
    /// <param name="width"></param>
    /// <param name="height"></param>
    /// <param name="mipLevels"></param>
    /// <param name="numSamples"></param>
    /// <param name="format"></param>
    /// <param name="tiling"></param>
    /// <param name="usage"></param>
    /// <param name="properties"></param>
    /// <param name="image"></param>
    /// <param name="imageMemory"></param>
    void ImageView::createImage
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
    ) {
        VkImageCreateInfo imageInfo = {};
        imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
        imageInfo.imageType = VK_IMAGE_TYPE_2D;
        imageInfo.extent.width = width;
        imageInfo.extent.height = height;
        imageInfo.extent.depth = 1;
        imageInfo.mipLevels = mipLevels;
        imageInfo.arrayLayers = 1;
        imageInfo.format = format;
        imageInfo.tiling = tiling;
        imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
        imageInfo.usage = usage;
        imageInfo.samples = numSamples;
        imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

        auto device = graphics_backend->getLogicalDevice();
        auto physical_device = graphics_backend->getPhysicalDevice();
        if (vkCreateImage(device, &imageInfo, nullptr, &image) != VK_SUCCESS) {
            throw std::runtime_error("failed to create image!");
        }

        VkMemoryRequirements memRequirements;
        vkGetImageMemoryRequirements(device, image, &memRequirements);

        VkMemoryAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
        allocInfo.allocationSize = memRequirements.size;
        allocInfo.memoryTypeIndex = memory_utils::findMemoryType(physical_device, memRequirements.memoryTypeBits, properties);

        if (vkAllocateMemory(device, &allocInfo, nullptr, &imageMemory) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate image memory!");
        }

        vkBindImageMemory(device, image, imageMemory, 0);
    }

    /// <summary>
    /// 
    /// </summary>
    /// <param name="graphics_backend"></param>
    /// <param name="image"></param>
    /// <param name="format"></param>
    /// <param name="aspectFlags"></param>
    /// <param name="mipLevels"></param>
    /// <param name="outViewImage"></param>
    void ImageView::createImageView
    (
        std::shared_ptr<VulkanGraphicsBackend> const graphics_backend,
        const VkImage& image,
        const VkFormat& format,
        const VkImageAspectFlags& aspectFlags,
        const uint32_t& mipLevels,
        VkImageView& outViewImage
    ) {
        VkImageViewCreateInfo viewInfo = {};
        viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        viewInfo.image = image;
        viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        viewInfo.format = format;
        viewInfo.subresourceRange.aspectMask = aspectFlags;
        viewInfo.subresourceRange.baseMipLevel = 0;
        viewInfo.subresourceRange.levelCount = mipLevels;
        viewInfo.subresourceRange.baseArrayLayer = 0;
        viewInfo.subresourceRange.layerCount = 1;

        VkImageView imageView;
        VkResult result = vkCreateImageView(graphics_backend->getLogicalDevice(), &viewInfo, nullptr, &imageView);
        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create image views!");
        }
        outViewImage = imageView;
    }

} // vengine