#include "simple_shader_parameter.h"

#include "vertex.h"

namespace vengine
{
    SimpleShaderParameter::SimpleShaderParameter() {
        binding_.binding = 0;
        binding_.stride = sizeof(Vertex);
        binding_.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        attributes_[0].binding = 0;
        attributes_[0].location = 0;
        attributes_[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributes_[0].offset = offsetof(Vertex, pos);

        attributes_[1].binding = 0;
        attributes_[1].location = 1;
        attributes_[1].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributes_[1].offset = offsetof(Vertex, color);

        attributes_[2].binding = 0;
        attributes_[2].location = 2;
        attributes_[2].format = VK_FORMAT_R32G32_SFLOAT;
        attributes_[2].offset = offsetof(Vertex, texCoord);
    }
} // vengine