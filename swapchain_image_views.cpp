#include "swapchain_image_views.h"
#include "swapchain.h"
#include "vulkan_graphics_backend.h"
#include "image_view.h"

namespace vengine
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="graphics_backend"></param>
    SwapchainImageViews::SwapchainImageViews(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend)
        : image_views_({}) {
        graphics_backend_ = graphics_backend_;
        create();
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    SwapchainImageViews::~SwapchainImageViews() {
        //for (const auto image_view : image_views_) {
        //    image_view.reset();
        //}
        //image_views_.clear();

        for (auto framebuffer : swapchain_framebuffers_) {
            vkDestroyFramebuffer(graphics_backend_->getLogicalDevice(), framebuffer, graphics_backend_->getAllocator());
        }
    }

    /// <summary>
    /// 生成処理
    /// </summary>
    void SwapchainImageViews::create() {
        auto device = graphics_backend_->getLogicalDevice();
        auto swapchain = graphics_backend_->getVulkanSwapchain();
        auto image_view = image_views_;
        SwapchainImageViews::create(graphics_backend_, device, swapchain, image_views_);
    }

    /// <summary>
    /// VkImage / VkImageViewを内包したImageViewクラスの生成
    /// </summary>
    /// <param name="graphics_backend"></param>
    /// <param name="device"></param>
    /// <param name="swapchain"></param>
    /// <param name="out_image_views"></param>
    void SwapchainImageViews::createImageView
    (
        std::shared_ptr<VulkanGraphicsBackend> const graphics_backend,
        const VkDevice& device,
        const VkSwapchainKHR& swapchain,
        std::vector<ImageView*>& out_image_views
    ) {
        std::vector<VkImage> temp;
        uint32_t image_count = 0;
        vkGetSwapchainImagesKHR(device, swapchain, &image_count, nullptr);
        out_image_views.resize(image_count);
        temp.resize(image_count);
        vkGetSwapchainImagesKHR(device, swapchain, &image_count, temp.data());

        for (const auto& image : temp) {
            auto imageView = new ImageView(graphics_backend);
            imageView->create(image);
            out_image_views.push_back(imageView);
        }

        // TODO 実装
        //image_views_.resize(swapchain_images_.size());
        //
        //for (size_t i = 0; i < swapchain_images_.size(); ++i)
        //{
        //    swapChainImageViews[i] = createImageView(swapChainImages[i], VK_FORMAT_B8G8R8A8_UNORM, VK_IMAGE_ASPECT_COLOR_BIT, 1);
        //}
    }

} // vengine