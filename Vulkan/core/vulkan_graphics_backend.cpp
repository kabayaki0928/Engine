#include "../vulkan/core/vulkan_graphics_backend.h"

namespace vengine
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="name"></param>
    /// <param name="engineName"></param>
    /// <param name="width"></param>
    /// <param name="height"></param>
    VulkanGraphicsBackend::VulkanGraphicsBackend
    (
        const char* name,
        const char* engine_name,
        const int& width,
        const int& height
    )
        : self_(shared_from_this()),
          window_(std::make_unique<GLFWWindow>(self_, name, width, height)),
          instance_(std::make_unique<VulkanInstance>(self_, name, engine_name)),
          device_(std::make_unique<VulkanDevice>(self_)),
          surface_(std::make_unique<Surface>(self_)),
          swapchain_(std::make_unique<Swapchain>(self_, width, height)),
          allocator_(std::make_unique<CustomAllocator>())
    {
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    VulkanGraphicsBackend::~VulkanGraphicsBackend() {
        self_.reset();
        window_.reset();
        instance_.reset();
        device_.reset();
        surface_.reset();
        swapchain_.reset();
        allocator_.reset();
    }

    /// <summary>
    /// 初期化処理
    /// </summary>
    void VulkanGraphicsBackend::initialize() {
    }

    /// <summary>
    /// Swapchainにまつわるもろもろの再作成処理
    /// GraphicsBackendになくてもいいかもしれない。要再考
    /// </summary>
    void VulkanGraphicsBackend::recreateSwapchain() {
        swapchain_->cleanup();
        swapchain_->recreate();

        //cleanupSwapChain();
        //
        //createSwapChain();
        //createImageViews();
        //createRenderPass();
        //createGraphicsPipeline();
        //createColorResources();
        //createDepthResources();
        //createFramebuffers();
        //createUniformBuffers();
        //createDescriptorPool();
        //createDescriptorSets();
        //createCommandBuffers();
    }

} // vengine