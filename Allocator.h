#ifndef ALLOCATORH
#define ALLOCATORH

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class Allocator
{
public:
    operator VkAllocationCallbacks* () {
        return nullptr;
    }
    operator const VkAllocationCallbacks* () const {
        return nullptr;
    }
};

#endif