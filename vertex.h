#ifndef VERTEXH
#define VERTEXH

#define GLFW_INCLUDE_VULKAN

#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
#include <GLFW/glfw3.h>

#include <array>

namespace vengine
{
    typedef struct Vertex {
        glm::vec3 pos;
        glm::vec3 color;
        glm::vec2 texCoord;

        static VkVertexInputBindingDescription getBindingDescription() {
            VkVertexInputBindingDescription bindingDescription = {};
            bindingDescription.binding = 0;
            bindingDescription.stride = sizeof(Vertex);
            bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

            return bindingDescription;
        }
        static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
            std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions = {};

            attributeDescriptions[0].binding = 0;
            attributeDescriptions[0].location = 0;
            attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[0].offset = offsetof(Vertex, pos);

            attributeDescriptions[1].binding = 0;
            attributeDescriptions[1].location = 1;
            attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
            attributeDescriptions[1].offset = offsetof(Vertex, color);

            attributeDescriptions[2].binding = 0;
            attributeDescriptions[2].location = 2;
            attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
            attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

            return attributeDescriptions;
        }
        inline bool operator==(const Vertex& other) const noexcept {
            return pos == other.pos && color == other.color && texCoord == other.texCoord;
        }
    } Vertex;
    // 三角形クラス用
    //const std::vector<Vertex> vertices = {
    //    { { -0.5f, -0.5f, 0.0f },{ 1.0f, 0.0f, 0.0f },{ 1.0f, 0.0f } },
    //    { {  0.5f, -0.5f, 0.0f },{ 0.0f, 1.0f, 0.0f },{ 0.0f, 0.0f } },
    //    { {  0.5f,  0.5f, 0.0f },{ 0.0f, 0.0f, 1.0f },{ 0.0f, 1.0f } },
    //    { { -0.5f,  0.5f, 0.0f },{ 1.0f, 1.0f, 1.0f },{ 1.0f, 1.0f } },
    //
    //    { { -0.5f, -0.5f, 0.5f },{ 1.0f, 0.0f, 0.0f },{ 0.0f, 0.0f } },
    //    { {  0.5f, -0.5f, 0.5f },{ 0.0f, 1.0f, 0.0f },{ 1.0f, 0.0f } },
    //    { {  0.5f,  0.5f, 0.5f },{ 0.0f, 0.0f, 1.0f },{ 1.0f, 1.0f } },
    //    { { -0.5f,  0.5f, 0.5f },{ 1.0f, 1.0f, 1.0f },{ 0.0f, 1.0f } }
    //};
    //
    //const std::vector<uint16_t> indices = {
    //    0, 1, 2, 2, 3, 0,
    //    4, 5, 6, 6, 7, 4
    //};
} // vengine

namespace std {
    template<> struct hash<vengine::Vertex> {
        size_t operator()(vengine::Vertex const& vertex) const {
            return
            (
                (hash<glm::vec3>()(vertex.pos)
              ^ (hash<glm::vec3>()(vertex.color) << 1)) >> 1)
              ^ (hash<glm::vec2>()(vertex.texCoord) << 1
            );
        }
    };
}
#endif