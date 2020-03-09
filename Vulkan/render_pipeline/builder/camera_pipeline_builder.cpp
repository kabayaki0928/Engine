#include "camera_pipeline_builder.h"

#include "../vulkan/component/camera.h"
#include "../vulkan/core/vulkan_graphics_backend.h"

namespace vengine
{
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    CameraPipelineBuilder::CameraPipelineBuilder(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend)
    : graphics_backend_(graphics_backend) {
    }

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    CameraPipelineBuilder::~CameraPipelineBuilder() {
    }

    /// <summary>
    /// Viewport�쐬����
    /// </summary>
    /// <param name="camera"></param>
    /// <param name="out_viewport"></param>
    void CameraPipelineBuilder::buildViewport(PCamera camera, VkViewport& out_viewport) {
        Viewport viewport = camera->getViewport();

        out_viewport.x = viewport.x;
        out_viewport.y = viewport.y;
        out_viewport.width = viewport.width;
        out_viewport.height = viewport.height;
        out_viewport.minDepth = viewport.min_depth;
        out_viewport.maxDepth = viewport.max_depth;
    }
    void CameraPipelineBuilder::buildScissor(PCamera camera, VkRect2D& out_scissor) {
        Scissor scissor = camera->getScissor();

        out_scissor.offset = { static_cast<uint32_t>(scissor.offset_x), static_cast<uint32_t>(scissor.offset_y) };
        out_scissor.extent = { scissor.extent_x, scissor.extent_y }; 
    }
    void CameraPipelineBuilder::buildViewportState(PCamera camera, const VkViewport& viewport, const VkRect2D& scissor, VkPipelineViewportStateCreateInfo& out_create_info) {
        out_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
        out_create_info.viewportCount = 1;
        out_create_info.pViewports = &viewport;
        out_create_info.scissorCount = 1;
        out_create_info.pScissors = &scissor;
    }
    /// <summary>
    /// https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPipelineRasterizationStateCreateInfo.html
    /// ���X�^���C�U�ݒ�
    /// </summary>
    /// <param name="camera"></param>
    /// <param name="out_create_info"></param>
    void CameraPipelineBuilder::buildRasterizer(PCamera camera, VkPipelineRasterizationStateCreateInfo& out_create_info) {
        out_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        // �t���O�����g�̐[�x�l���N�����v���邩�ǂ���
        out_create_info.depthClampEnable = VK_FALSE;
        // ���X�^���C�Y�X�e�[�W�̒��O�Ƀv���~�e�B�u��j�����邩�ǂ���
        out_create_info.rasterizerDiscardEnable = VK_FALSE;
        // https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPolygonMode.html
        out_create_info.polygonMode = VK_POLYGON_MODE_FILL;
        // ���X�^���C�Y���ꂽ���C���Z�O�����g�̕�
        out_create_info.lineWidth = 1.0f;
        // https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkCullModeFlagBits.html
        // �f�t�H���g�͔w�ʃJ�����O
        out_create_info.cullMode = VK_CULL_MODE_BACK_BIT;
        // https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFrontFace.html
        // ���̖ʐς����O�p�`�𐳖ʌ����ƌ��Ȃ�
        out_create_info.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
        // �t���O�����g�[�x�l�Ƀo�C�A�X�������邩�ǂ���
        out_create_info.depthBiasEnable = VK_FALSE;
    }
    void CameraPipelineBuilder::buildMultisample(PCamera camera, VkPipelineMultisampleStateCreateInfo& out_create_info) {
        out_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        // https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#primsrast-sampleshading
        // TODO defferd����msaa�����Ȃ��̂ł����ǂ����邩�͗v�čl
        // VK_SAMPLE_COUNT_1_BIT�Ŏ����������ĂȂ��Ƃ��Ȃ炻�̂܂܂ł��悳����
        out_create_info.sampleShadingEnable = VK_FALSE;
        out_create_info.rasterizationSamples = toVkSampleCountFlagBits(camera->getMSAASamples());
    }

    void CameraPipelineBuilder::buildDepthStencilState(PCamera camera, VkPipelineDepthStencilStateCreateInfo& out_create_info) {
        out_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
        // �[�x���̏������ݐݒ�
        // depth�p�̏��Ȃ̂ł����OK
        // UI�p�̃J�����Ƃ��p�ӂ���Ȃ炱���ŏ�������
        out_create_info.depthTestEnable = VK_TRUE;
        out_create_info.depthWriteEnable = VK_TRUE;
        out_create_info.depthCompareOp = VK_COMPARE_OP_LESS;
        out_create_info.depthBoundsTestEnable = VK_FALSE;
        out_create_info.stencilTestEnable = VK_FALSE;
    }

    void CameraPipelineBuilder::buildColorBlendAttachment(PCamera camera, VkPipelineColorBlendAttachmentState& out_create_info) {
        out_create_info.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
        out_create_info.blendEnable = VK_FALSE;
    }

    void CameraPipelineBuilder::buildColorBlendState(PCamera camera, const VkPipelineColorBlendAttachmentState& attachment, VkPipelineColorBlendStateCreateInfo& out_create_info) {
        out_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
        out_create_info.logicOpEnable = VK_FALSE;
        out_create_info.logicOp = VK_LOGIC_OP_COPY;
        out_create_info.attachmentCount = 1;
        out_create_info.pAttachments = &attachment;
        out_create_info.blendConstants[0] = 0.0f;
        out_create_info.blendConstants[1] = 0.0f;
        out_create_info.blendConstants[2] = 0.0f;
        out_create_info.blendConstants[3] = 0.0f;
    }

    void CameraPipelineBuilder::buildFrameBuffer(PCamera camera, VkFramebuffer& out_frame_buffer) {
        std::array<VkImageView, 3> attachments = {
            camera->getColorBuffer().image_view_,
            camera->getDepthBuffer().image_view_,
            graphics_backend_->getVulkanSwapchain().getBuffer().image_views[i];
        };

        VkFramebufferCreateInfo framebufferInfo = {};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = renderPass;
        framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
        framebufferInfo.pAttachments = attachments.data();
        framebufferInfo.width = extent.width;
        framebufferInfo.height = extent.height;
        framebufferInfo.layers = 1;

        if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {
            throw std::runtime_error("failed to create framebuffer!");
        }
    }

    inline VkSampleCountFlagBits toVkSampleCountFlagBits(const MSAASamples& samples) noexcept {
        switch (samples) {
        case MSAASamples::Sample_1:     return VkSampleCountFlagBits::VK_SAMPLE_COUNT_1_BIT;
        case MSAASamples::Sample_2:     return VkSampleCountFlagBits::VK_SAMPLE_COUNT_2_BIT;
        case MSAASamples::Sample_4:     return VkSampleCountFlagBits::VK_SAMPLE_COUNT_4_BIT;
        case MSAASamples::Sample_8:     return VkSampleCountFlagBits::VK_SAMPLE_COUNT_8_BIT;
        case MSAASamples::Sample_16:    return VkSampleCountFlagBits::VK_SAMPLE_COUNT_16_BIT;
        case MSAASamples::Sample_32:    return VkSampleCountFlagBits::VK_SAMPLE_COUNT_32_BIT;
        case MSAASamples::Sample_64:    return VkSampleCountFlagBits::VK_SAMPLE_COUNT_64_BIT;
        }
        assert("not defined MSAASamples");
    }

} // vengine