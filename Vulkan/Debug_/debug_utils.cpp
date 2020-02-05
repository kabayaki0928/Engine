
#include "debug_utils.h"
#include "vulkan_graphics_backend.h"
#include "user_define.h"

namespace vengine
{
namespace debug
{
    Messanger::Messanger(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend) {
        graphics_backend_ = graphics_backend;
    }

    Messanger::~Messanger() {
        if (user_define::enableValidationLayers) {
            DestroyDebugUtilsMessengerEXT(graphics_backend_->getVulkanInstance(), debug_messenger_, nullptr);
        }
    }


} // debug
} // vengine