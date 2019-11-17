#include "camera_pipeline_builder.h"

#include "camera.h"

namespace vengine
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    CameraPipelineBuilder::CameraPipelineBuilder() {
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    CameraPipelineBuilder::~CameraPipelineBuilder() {
    }

    /// <summary>
    /// Viewport作成処理
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
        Scissor scissor = camera->getSicssor();

        out_scissor.offset = { scissor.offset_x, scissor.offset_y };
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
    /// ラスタライザ設定
    /// </summary>
    /// <param name="camera"></param>
    /// <param name="out_create_info"></param>
    void CameraPipelineBuilder::buildRasterizer(PCamera camera, VkPipelineRasterizationStateCreateInfo& out_create_info) {
        out_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
        // フラグメントの深度値をクランプするかどうか
        out_create_info.depthClampEnable = VK_FALSE;
        // ラスタライズステージの直前にプリミティブを破棄するかどうか
        out_create_info.rasterizerDiscardEnable = VK_FALSE;
        // https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPolygonMode.html
        out_create_info.polygonMode = VK_POLYGON_MODE_FILL;
        // ラスタライズされたラインセグメントの幅
        out_create_info.lineWidth = 1.0f;
        // https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkCullModeFlagBits.html
        // デフォルトは背面カリング
        out_create_info.cullMode = VK_CULL_MODE_BACK_BIT;
        // https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkFrontFace.html
        // 正の面積を持つ三角形を正面向きと見なす
        out_create_info.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
        // フラグメント深度値にバイアスをかけるかどうか
        out_create_info.depthBiasEnable = VK_FALSE;
    }
    void CameraPipelineBuilder::buildMultisample(PCamera camera, VkPipelineMultisampleStateCreateInfo& out_create_info) {
        out_create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
        // https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#primsrast-sampleshading
        // TODO defferd時にmsaa効かないのでここどうするかは要再考
        // VK_SAMPLE_COUNT_1_BITで実質かかってないとかならそのままでもよさそう
        out_create_info.sampleShadingEnable = VK_FALSE;
        out_create_info.rasterizationSamples = toVkSampleCountFlagBits(camera->getMSAASamples());
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