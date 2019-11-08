#include "swapchain.h"

#include "queue_family.h"
#include "vulkan_graphics_backend.h"
#include "swapchain_image_views.h"
#include "user_define.h"
#include "vulkan_utils.h"


namespace vengine
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="graphics_backend"></param>
    Swapchain::Swapchain(std::shared_ptr<VulkanGraphicsBackend> graphics_backend, const int width, const int height) {
        graphics_backend_ = graphics_backend;
        create(width, height);
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    Swapchain::~Swapchain() {
        swapchain_image_views_.reset();
        vkDestroySwapchainKHR(graphics_backend_->getLogicalDevice(), swapchain_, nullptr);
        graphics_backend_.reset();
    }

    /// <summary>
    /// 作成処理
    /// </summary>
    /// <param name="width"></param>
    /// <param name="height"></param>
    void Swapchain::create(const int& width, const int& height) {
        Swapchain::create
        (
            graphics_backend_->getGLFWWindow(),
            graphics_backend_->getPhysicalDevice(),
            graphics_backend_->getLogicalDevice(),
            graphics_backend_->getVulkanSurface(),
            width,
            height,
            swapchain_,
            image_format_,
            extent_
        );

        swapchain_image_views_ = std::make_unique<SwapchainImageViews>(graphics_backend_);
    }

    void Swapchain::create
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
    )
    {
        SwapChainSupportDetails swapchain_support = QueueFamily::querySwapChainSupport(physicalDevice, surface);

        VkSurfaceFormatKHR surface_format = VulkanUtils::chooseSwapSurfaceFormat(swapchain_support.formats);
        VkPresentModeKHR present_mode = VulkanUtils::chooseSwapPresentMode(swapchain_support.presentModes);
        VkExtent2D extent = VulkanUtils::chooseSwapExtent(window, swapchain_support.capabilities, width, height);

        uint32_t imageCount = swapchain_support.capabilities.minImageCount + 1;
        if (swapchain_support.capabilities.maxImageCount > 0
         && swapchain_support.capabilities.maxImageCount < imageCount) {
            imageCount = swapchain_support.capabilities.maxImageCount;
        }

        VkSwapchainCreateInfoKHR create_info = {};
        create_info.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        create_info.surface = surface;

        create_info.minImageCount = imageCount;
        create_info.imageFormat = surface_format.format;
        create_info.imageColorSpace = surface_format.colorSpace;
        create_info.imageExtent = extent;
        create_info.imageArrayLayers = 1;
        create_info.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

        auto indices = QueueFamily::findQueueFamilies(physicalDevice, surface);
        uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };

        if (indices.graphicsFamily != indices.presentFamily) {
            create_info.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            create_info.queueFamilyIndexCount = 2;
            create_info.pQueueFamilyIndices = queueFamilyIndices;
        }
        else {
            create_info.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        }

        create_info.preTransform = swapchain_support.capabilities.currentTransform;
        create_info.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        create_info.presentMode = present_mode;
        create_info.clipped = VK_TRUE;

        create_info.oldSwapchain = VK_NULL_HANDLE;

        if (vkCreateSwapchainKHR(device, &create_info, nullptr, &out_swapchain) != VK_SUCCESS) {
            throw std::runtime_error("failed to create swap chain!");
        }

        out_format = surface_format.format;
        out_extent = extent;
    }

    /// <summary>
    /// 作成処理
    /// </summary>
    void Swapchain::recreate() {
        assert(extent_.width > 0);
        assert(extent_.height > 0);

        create(extent_.width, extent_.height);
    }

    void Swapchain::cleanup() {
        //vkDestroyImageView(device, depthImageView, nullptr);
        //vkDestroyImage(device, depthImage, nullptr);
        //vkFreeMemory(device, depthImageMemory, nullptr);

        //vkDestroyImageView(device, colorImageView, nullptr);
        //vkDestroyImage(device, colorImage, nullptr);
        //vkFreeMemory(device, colorImageMemory, nullptr);

        //for (auto framebuffer : swapChainFramebuffers) {
        //    vkDestroyFramebuffer(device, framebuffer, nullptr);
        //}

        //vkFreeCommandBuffers(device, commandPool, static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());

        //vkDestroyPipeline(device, graphicsPipeline, nullptr);
        //vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
        //vkDestroyRenderPass(device, renderPass, nullptr);

        //for (auto imageView : swapChainImageViews) {
        //    vkDestroyImageView(device, imageView, nullptr);
        //}

        //vkDestroySwapchainKHR(device, swapChain, nullptr);

        //for (size_t i = 0; i < swapChainImages.size(); i++) {
        //    vkDestroyBuffer(device, uniformBuffers[i], nullptr);
        //    vkFreeMemory(device, uniformBuffersMemory[i], nullptr);
        //}

        //vkDestroyDescriptorPool(device, descriptorPool, nullptr);


        vkDestroySwapchainKHR(graphics_backend_->getLogicalDevice(), swapchain_, nullptr);
    }
} // vengine