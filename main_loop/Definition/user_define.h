#ifndef GLOBAL_DEFINEH
#define GLOBAL_DEFINEH

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

/// <summary>
/// ÉÜÅ[ÉUíËã`ÇÃÇ‡ÇÎÇ‡ÇÎ
/// </summary>
namespace user_define
{
    const int WIDTH = 800;
    const int HEIGHT = 600;

#ifdef NDEBUG
    const bool enableValidationLayers = false;
#else
    const bool enableValidationLayers = false;  // TODO ñﬂÇ∑
#endif

    /*
    https://vulkan.lunarg.com/doc/view/1.0.69.0/mac/layer_configuration.html
    VK_LAYER_LUNARG_api_dump	            utility	print API calls and their parameters and values
    VK_LAYER_LUNARG_core_validation	        validation	print and validate the descriptor set, pipeline state, and dynamic state;
    validate the interfaces between SPIR-V modules and the graphics pipeline;
    track and validate GPU memory and its binding to objects and command buffers;
    validate texture formats and render target formats
    VK_LAYER_LUNARG_device_simulation	    utility	allows modification of an actual device's reported features, limits, and capabilities
    VK_LAYER_LUNARG_monitor	                utility	outputs the frames-per-second of the target application in the applications title bar
    VK_LAYER_LUNARG_object_tracker	        validation	track all Vulkan objects and flag invalid objects and object memory leaks
    VK_LAYER_LUNARG_parameter_validation    validation	validate API parameter values
    VK_LAYER_LUNARG_screenshot	            utility	outputs specified frames to an image file as they are presented
    VK_LAYER_GOOGLE_threading	            validation	check validity of multi-threaded API usage
    VK_LAYER_GOOGLE_unique_objects	        utility	wrap all Vulkan objects in a unique pointer at create time and unwrap them at use time
    */
    const std::vector<const char*> validationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };

    /*
    https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_swapchain
    */
    const std::vector<const char*> deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };
}

#endif