#ifndef VULKAN_INSTANCEH
#define VULKAN_INSTANCEH

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "../vulkan/core/interface/igraphics_instance.h"

namespace vengine
{
    class VulkanGraphicsBackend;

    /// <summary>
    /// VkInstanceを管理するクラス
    /// </summary>
    class VulkanInstance final : public rengine::IGraphicsInstance
    {
    private:
        VkInstance instance_;
        std::shared_ptr<VulkanGraphicsBackend> graphics_backend_;
    public:
        VulkanInstance
        (
            std::shared_ptr<VulkanGraphicsBackend> const graphics_backend,
            const char* application_name,
            const char* engine_name
        );
        ~VulkanInstance();
        void create(const char* application_name, const char* engine_name);

        //-------------------------------------------------
        // operator群
        operator VkInstance&() {
            return instance_;
        }
        operator const VkInstance&() const {
            return instance_;
        }
        //-------------------------------------------------
        // static関数
        static void create(VkInstance* instance, const char* application_name, const char* engine_name);
    };
} // vengine

#endif