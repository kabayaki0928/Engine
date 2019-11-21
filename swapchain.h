#ifndef SWAPCHAINH
#define SWAPCHAINH

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "iswapchain.h"

namespace vengine
{
    class VulkanGraphicsBackend;
    class SwapchainImageViews;

    /// <summary>
    /// スワップチェーン関連を管理するクラス
    /// https://vulkan-tutorial.com/Drawing_a_triangle/Presentation/Swap_chain
    /// </summary>
    class Swapchain final : public rengine::ISwapchain
    {
    private:
        std::shared_ptr<VulkanGraphicsBackend> graphics_backend_;
        VkSwapchainKHR swapchain_;
        VkFormat image_format_;
        VkExtent2D extent_;
        std::unique_ptr<SwapchainImageViews> swapchain_image_views_;

    public:
        Swapchain(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend, const int width, const int height);
        ~Swapchain();
        
        void create(const int& width, const int& height);
        static void create
        (
            const GLFWwindow* window,
            const VkPhysicalDevice& physicalDevice,
            const VkDevice& device,
            const VkSurfaceKHR& surface,
            const int& width,
            const int& height,
            VkSwapchainKHR& out_swapchain,
            VkFormat& out_format,
            VkExtent2D& out_extent
        );
        void recreate();
        void cleanup();

        const VkFormat& getSwapchainImageFormat() const noexcept { return image_format_; }
        uint32_t getSwapchainCount() const noexcept;

        //--------------------
        // override群
        inline const VkExtent2D& getExtent() const noexcept override {
            return extent_;
        }
        inline float getWidth() const noexcept override {
            return extent_.width;
        }
        inline float getHeight() const noexcept override {
            return extent_.height;
        }

        //--------------------
        // operator群
        operator VkSwapchainKHR&() noexcept {
            return swapchain_;
        }
        operator const VkSwapchainKHR&() const noexcept {
            return swapchain_;
        }
    };
} // vengine
#endif