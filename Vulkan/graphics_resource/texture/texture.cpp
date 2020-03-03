#include "texture.h"

#include <stb_image.h>

#include "buffer.h"
#include "command_buffer.h"
#include "image_view.h"
#include "../vulkan/core/vulkan_graphics_backend.h"
#include "../vulkan/utils/vulkan_utils.h"

namespace vengine
{
    Texture::Texture
    (
        std::shared_ptr<VulkanGraphicsBackend> const graphics_backend,
        const texture::PixelData& pixel_data
    ) : graphics_backend_(graphics_backend),
        create(pixel_data) {
    }

    Texture::~Texture() {
    }

    void Texture::create(const texture::PixelData& pixel_data) {
        if (!pixel_data.pixels_) {
            throw std::runtime_error("failed to load texture image!");
        }

        auto device = graphics_backend_->getLogicalDevice();

        VkDeviceSize image_size = pixel_data.width_ * pixel_data.height_ * 4;
        mip_levels_ = static_cast<uint32_t>(std::floor(std::log2(std::max(pixel_data.width_, pixel_data.height_)))) + 1;

        VkBuffer stagingBuffer;
        VkDeviceMemory stagingBufferMemory;
        Buffer::createBuffer
        (
            graphics_backend_,
            image_size,
            VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
            | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            stagingBuffer,
            stagingBufferMemory
        );

        void* data;
        vkMapMemory(device, stagingBufferMemory, 0, image_size, 0, &data);
        memcpy(data, pixel_data.pixels_, static_cast<size_t>(image_size));
        vkUnmapMemory(device, stagingBufferMemory);
        stbi_image_free(pixel_data.pixels_);

        ImageView::createImage
        (
            graphics_backend_,
            pixel_data.width_,
            pixel_data.height_,
            mip_levels_,
            VK_SAMPLE_COUNT_1_BIT,
            VK_FORMAT_R8G8B8A8_UNORM,
            VK_IMAGE_TILING_OPTIMAL,
            VK_IMAGE_USAGE_TRANSFER_SRC_BIT
            | VK_IMAGE_USAGE_TRANSFER_DST_BIT
            | VK_IMAGE_USAGE_SAMPLED_BIT,
            VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
            image_,
            memory_
        );

        ExecutableCommandBufferData command_buffer_data = {};
        CommandBuffer::transitionImageLayout
        (
            image_,
            VK_FORMAT_R8G8B8A8_UNORM,
            VK_IMAGE_LAYOUT_UNDEFINED,
            VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
            mip_levels_
        );

        CommandBuffer::copyBufferToImage
        (
            stagingBuffer,
            image_,
            static_cast<uint32_t>(pixel_data.width_),
            static_cast<uint32_t>(pixel_data.height_)
        );
        //transitioned to VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL while generating mipmaps

        vkDestroyBuffer(device, stagingBuffer, nullptr);
        vkFreeMemory(device, stagingBufferMemory, nullptr);

        CommandBuffer::generateMipmaps
        (
            graphics_backend_,
            image_,
            VK_FORMAT_R8G8B8A8_UNORM,
            pixel_data.width_,
            pixel_data.height_,
            mip_levels_
        );

        ImageView::createImageView
        (
            graphics_backend_,
            image_,
            VK_FORMAT_R8G8B8A8_UNORM,
            VK_IMAGE_ASPECT_COLOR_BIT,
            mip_levels_,
            image_view_
        );
    }

    void Texture::createTextureSampler() {
        VkSamplerCreateInfo samplerInfo = {};
        //samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
        samplerInfo.magFilter = VK_FILTER_LINEAR;
        samplerInfo.minFilter = VK_FILTER_LINEAR;
        samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
        samplerInfo.anisotropyEnable = VK_TRUE;
        samplerInfo.maxAnisotropy = 16;
        samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
        samplerInfo.unnormalizedCoordinates = VK_FALSE;
        samplerInfo.compareEnable = VK_FALSE;
        samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
        samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
        samplerInfo.minLod = 0;
        samplerInfo.maxLod = static_cast<float>(mipLevels);
        samplerInfo.mipLodBias = 0;

        if (vkCreateSampler(device, &samplerInfo, nullptr, &textureSampler) != VK_SUCCESS) {
            throw std::runtime_error("failed to create texture sampler!");
        }
    }
} // vengine