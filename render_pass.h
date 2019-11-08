#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace vengine
{
    class VulkanGraphicsBackend;

    class RenderPass
    {
    private:
        std::shared_ptr<VulkanGraphicsBackend> graphics_backend_;
        VkRenderPass render_pass_;
    public:
        RenderPass(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend);
        ~RenderPass();

        void create();
        static void create
        (
            std::shared_ptr<VulkanGraphicsBackend> graphics_backend,
            const VkFormat& colorImageFormat,
            const VkSampleCountFlagBits& colorMsaaSamples,
            const VkFormat& depthFormat,
            const VkSampleCountFlagBits& depthMsaaSamples,
            VkRenderPass& out_render_pass
        );
    };
} // vengine