#ifndef COMMAND_POOLH
#define COMMAND_POOLH

#define GLFW_INCLUDE_VULKAN

#include <GLFW/glfw3.h>

class CommandPool
{
private:
    VkCommandPool commandPool;
public:
    operator VkCommandPool() {
        return commandPool;
    }
    operator VkCommandPool&() {
        return commandPool;
    }
    constexpr operator const VkCommandPool() const {
        return commandPool;
    }
    constexpr operator const VkCommandPool&() const {
        return commandPool;
    }
};

#endif