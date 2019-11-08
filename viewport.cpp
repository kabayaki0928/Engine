#include "viewport.h"

#include "vulkan_graphics_backend.h"

namespace vengine
{
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="graphics_backend"></param>
    Viewport::Viewport(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend) {
        graphics_backend_ = graphics_backend;
    }

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    Viewport::~Viewport() {
    }

    /// <summary>
    /// VkPipelineViewportStateCreateInfo�쐬����
    /// </summary>
    void Viewport::create() {
        Viewport::create(graphics_backend_->getVulkanSwapchain().getExtent(), create_info_);
    }

    /// <summary>
    /// �쐬����
    /// �J�������ɋ@�\���񂹂��ق���������������Ȃ�
    /// �R���X�g���N�^��Camera�N���X�����炤�C���[�W
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