#ifndef SWAPCHAIN_IMAGEVIEWH
#define SWAPCHAIN_IMAGEVIEWH

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "image_view.h"

namespace vengine
{
    class VulkanGraphicsBackend;

    /// <summary>
    /// SwapChainで使用するImageViewを管理するクラス
    /// </summary>
    class SwapchainImageViews
    {
    private:
        std::shared_ptr<VulkanGraphicsBackend> graphics_backend_;
        std::vector<ImageView*> image_views_;
        std::vector<VkFramebuffer> swapchain_framebuffers_;
    public:
        SwapchainImageViews(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend);
        ~SwapchainImageViews();

        void create();
        static void createImageView(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend, const VkDevice& device, const VkSwapchainKHR& swapChain, std::vector<ImageView*>& out_image_views);
        static void createFrameBuffers();
    };
} // vengine

#endif