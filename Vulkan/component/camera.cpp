#include "camera.h"

#include "../vulkan/core/vulkan_graphics_backend.h"

namespace vengine
{
    Camera::Camera(std::shared_ptr<VulkanGraphicsBackend> const graphcis_backend)
    : graphics_backend_(graphics_backend_) {
    }

    Camera::~Camera() {
        auto device = graphics_backend_->getLogicalDevice();
        auto allocator = nullptr;

        // depth系バッファの破棄
        vkDestroyImageView(device, depth_buffer_.image_view_, allocator);
        vkDestroyImage(device, depth_buffer_.image_, allocator);
        vkFreeMemory(device, depth_buffer_.image_memory_, allocator);

        // color系バッファの破棄
        vkDestroyImageView(device, color_buffer_.image_view_, allocator);
        vkDestroyImage(device, color_buffer_.image_, allocator);
        vkFreeMemory(device, color_buffer_.image_memory_, allocator);
    }
} // vengine
