#pragma once

#include "transform.h"
#include "behaviour.h"

namespace vengine
{
    namespace {
        typedef struct Buffer {
            VkImage image_;
            VkDeviceMemory image_memory_;
            VkImageView image_view_;
        };
    }

    class VulkanGraphicsBackend;

    /// <summary>
    /// ƒJƒƒ‰ƒNƒ‰ƒX
    /// </summary>
    class Camera final : public cengine::Behaviour
    {
    private:
        std::shared_ptr<VulkanGraphicsBackend> graphics_backend_;
        Buffer color_buffer_;
        Buffer depth_buffer_;

    public:
        Camera(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend);
        ~Camera();

        
    };
} // vengine