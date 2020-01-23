#ifndef UNIFORM_BUFFERH
#define UNIFORM_BUFFERH

#define GLFW_INCLUDE_VULKAN
#include <glm/glm.hpp>

namespace vengine
{
    typedef struct UniformBufferObject {
        alignas(16) glm::mat4 model;
        alignas(16) glm::mat4 view;
        alignas(16) glm::mat4 projection;
    } UniformBufferObject;

} // vengine

#endif
