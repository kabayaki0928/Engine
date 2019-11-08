#include "viewport.h"

#include "vulkan_graphics_backend.h"

namespace vengine
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="graphics_backend"></param>
    Viewport::Viewport(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend) {
        graphics_backend_ = graphics_backend;
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    Viewport::~Viewport() {
    }

    /// <summary>
    /// VkPipelineViewportStateCreateInfo作成処理
    /// </summary>
    void Viewport::create() {
        Viewport::create(graphics_backend_->getVulkanSwapchain().getExtent(), create_info_);
    }

    /// <summary>
    /// 作成処理
    /// カメラ側に機能を寄せたほうがいいかもしれない
    /// コンストラクタでCameraクラスをもらうイメージ
    /// </summary>
    /// <param name="extent"></param>
    /// <param name="out_create_info"></param>
    void Viewport::create(const VkExtent2D& extent, VkPipelineViewportStateCreateInfo& out_create_info) {
        VkViewport viewport = {};
        viewport.x = 0.0f;
        viewport.y = 0.0f;
        viewport.width = (float)extent.width;
        viewport.height = (float)extent.height;
        viewport.minDepth = 0.0f;
        viewport.maxDepth = 1.0f;

        VkRect2D scissor = {};
        scissor.offset = { 0, 0 };
        scissor.extent = extent;

        VkPipelineViewportStateCreateInfo viewportState = {};
        viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        viewportState.viewportCount = 1;
        viewportState.pViewports = &viewport;
        viewportState.scissorCount = 1;
        viewportState.pScissors = &scissor;
    }

} // vengine