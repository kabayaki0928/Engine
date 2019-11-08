#pragma once

namespace vengine
{
    class VulkanGraphicsBackend;

    namespace texture {
        typedef struct PixelData {
            stbi_uc* pixels_;
            int width_;
            int height_;
            int channels_;

        } CreateInfo;
    } // texture

    class Texture final
    {
    private:
        std::shared_ptr<VulkanGraphicsBackend> graphics_backend_;
        VkImage image_;
        VkDeviceMemory memory_;
        VkImageView image_view_;
        int mip_levels_;
    public:
        Texture(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend, const texture::PixelData& pixel_data);
        ~Texture();

        void create(const texture::PixelData& pixel_data);
        void createTextureSampler();
    };
} // vengine