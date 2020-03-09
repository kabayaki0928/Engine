#include "simple_shader_parameter.h"

#include "../vulkan/utils/macro.h"
#include "../vulkan/primitive/vertex.h"

namespace vengine
{
    SimpleShaderParameter::SimpleShaderParameter() {
        binding_.binding = 0;
        binding_.stride = sizeof(Vertex);
        binding_.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        auto attribute = attributes_.attribute_;

        attribute[0].binding = 0;
        attribute[0].location = 0;
        attribute[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attribute[0].offset = offsetof(Vertex, pos);

        attribute[1].binding = 0;
        attribute[1].location = 1;
        attribute[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attribute[1].offset = offsetof(Vertex, color);

        attribute[2].binding = 0;
        attribute[2].location = 2;
        attribute[2].format = VK_FORMAT_R32G32_SFLOAT;
        attribute[2].offset = offsetof(Vertex, texCoord);

        attributes_.length_ = COUNTOF(attribute);
    }
} // vengine