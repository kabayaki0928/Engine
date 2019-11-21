#pragma once

#include "transform.h"
#include "behaviour.h"

namespace vengine
{
    namespace {
        /// <summary>
        /// color / depthで使用するバッファをまとめた構造体
        /// </summary>
        typedef struct Buffer {
            VkImage image_;
            VkDeviceMemory image_memory_;
            VkImageView image_view_;
        } Buffer;
    }

    /// <summary>
    /// 描画先のViewport設定
    /// </summary>
    typedef struct Viewport {
        float x;
        float y;
        float width;
        float height;
        float min_depth;
        float max_depth;
    } Viewport;

    /// <summary>
    /// Viewportの矩形設定
    /// </summary>
    typedef struct Scissor {
        float offset_x;
        float offset_y;
        float extent_x;
        float extent_y;
    } Sicssor;

    enum MSAASamples {
        Sample_1,
        Sample_2,
        Sample_4,
        Sample_8,
        Sample_16,
        Sample_32,
        Sample_64,
    };

    class VulkanGraphicsBackend;

    /// <summary>
    /// カメラクラス
    /// </summary>
    class Camera final : public cengine::Behaviour
    {
    private:
        std::shared_ptr<VulkanGraphicsBackend> graphics_backend_;
        Buffer color_buffer_; // TODO 
        Buffer depth_buffer_;

        Viewport viewport_;
        Scissor scissor_;
        MSAASamples samples_;
    public:
        Camera(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend);
        ~Camera();

        inline const Viewport& getViewport() const noexcept { return viewport_; }
        inline const Scissor& getScissor() const noexcept { return scissor_; }
        inline const MSAASamples& getMSAASamples() const noexcept { return samples_; }
    };
} // vengine