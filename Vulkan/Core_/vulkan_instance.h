#ifndef VULKAN_INSTANCEH
#define VULKAN_INSTANCEH

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "igraphics_instance.h"

namespace vengine
{
    class VulkanGraphicsBackend;

    /// <summary>
    /// VkInstanceÇä«óùÇ∑ÇÈÉNÉâÉX
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
        // operatoråQ
        operator VkInstance&() {
            return instance_;
        }
        operator const VkInstance&() const {
            return instance_;
        }
        //-------------------------------------------------
        // staticä÷êî
        static void create(VkInstance* instance, const char* application_name, const char* engine_name);
    };
} // vengine

#endif