#include "surface.h"
#include "../vulkan/core/vulkan_graphics_backend.h"

namespace vengine
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="graphics_backend"></param>
    Surface::Surface(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend) {

    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    Surface::~Surface() {
        vkDestroySurfaceKHR(graphics_backend_->getVulkanInstance(), surface_, graphics_backend_->getAllocator());
    }

    /// <summary>
    /// 作成処理
    /// </summary>
    void Surface::create() {
        Surface::create(graphics_backend_->getVulkanInstance(), graphics_backend_->getGLFWWindow(), surface_);
    }

    /// <summary>
    /// 作成処理
    /// </summary>
    /// <param name="instance"></param>
    /// <param name="window"></param>
    /// <param name="out_surface"></param>
    void Surface::create(const VkInstance& instance, GLFWwindow* window, VkSurfaceKHR& out_surface) {
        VkResult result = glfwCreateWindowSurface(instance, window, nullptr, &out_surface);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to create window surface!");
        }
    }

} // vengine