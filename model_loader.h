#pragma once

#include <tiny_obj_loader.h>

namespace vengine
{
    class Model;
    class Vertex;
    class DrawableBuffer;

    namespace {
        typedef struct RawData {
            std::vector<Vertex> vertices;
            std::vector<uint32_t> indices;
            tinyobj::attrib_t attribute;
            std::vector<tinyobj::shape_t> shapes;
            std::vector<tinyobj::material_t> materials;
            std::unordered_map<Vertex, uint32_t> unique_vertices;
        } RawData;
    }

    /// <summary>
    /// ƒ‚ƒfƒ‹‚Ì“Ç‚İ‚İ‚ğŠÇ—‚·‚éƒNƒ‰ƒX
    /// </summary>
    class ModelLoader final {
    private:
        static void loadFile(const char* file_name, RawData& out_raw_data);
        static void distinctVertex(RawData& out_raw_data);
        static void createDrawableBuffer(const RawData& raw_data, std::shared_ptr<DrawableBuffer>& out_buffer);
    public:
        ModelLoader() {}
        ~ModelLoader() {}
        void load(const char* file_name, std::function<void(std::shared_ptr<Model>)>);
    };

} // rengine