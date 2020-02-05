#ifndef SURFACEH
#define SURFACEH

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "isurface.h"

namespace vengine
{
    class VulkanGraphicsBackend;

    /// <summary>
    /// Surface�N���X
    /// Window�N���X�ƍ����Ă�������������Ȃ�
    /// �Ƃ肠���������Ă���
    /// </summary>
    class Surface final : public rengine::ISurface
    {
    private:
        std::shared_ptr<VulkanGraphicsBackend> graphics_backend_;
        VkSurfaceKHR surface_;
    public:
        Surface(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend);
        ~Surface();
        void create();
        static void create(const VkInstance& instance, GLFWwindow* window, VkSurfaceKHR& out_surface);
        //-------------------------------------
        // operator�Q
        operator VkSurfaceKHR&() {
            return surface_;
        }
        operator const VkSurfaceKHR&() const {
            return surface_;
        }
    };
} // vengine

#endif