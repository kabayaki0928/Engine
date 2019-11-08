#pragma once

#define GLFW_INCLUDE_VULKAN
#include <glm/glm.hpp>

namespace vengine
{
    class VulkanGraphicsBackend;

    class Viewport final
    {
    private:
        std::shared_ptr<VulkanGraphicsBackend> graphics_backend_;
        VkPipelineViewportStateCreateInfo create_info_;
    public:
        Viewport(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend);
        ~Viewport();

        inline const VkPipelineViewportStateCreateInfo& getCreateInfo() const noexcept {
            return create_info_;
        }

        void create();
        static void create(const VkExtent2D& extent, VkPipelineViewportStateCreateInfo& out_create_info);
    };
} // vengine