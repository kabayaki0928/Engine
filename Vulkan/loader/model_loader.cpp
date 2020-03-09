#include "model_loader.h"

#include "drawable_buffer.h"
#include "../vulkan/graphics_resource/model/model.h"
#include "vertex.h"

namespace vengine
{
    /// <summary>
    /// �ǂݍ��ݏ���
    /// </summary>
    /// <param name="file_name"></param>
    /// <param name="callback"></param>
    void ModelLoader::load(const char* file_name, std::function<void(std::shared_ptr<rengine::Model>)> callback) {
        
        // TODO �L���b�V���n�̋@�\ 

        RawData raw_data = {};
        std::shared_ptr<DrawableBuffer> drawable_buffer;

        loadFile(file_name, raw_data);
        distinctVertex(raw_data);
        createDrawableBuffer(raw_data, drawable_buffer);

        auto model = std::make_shared<rengine::Model>(drawable_buffer, nullptr);

        // TODO �j���Ǘ��n�̉����ɒǉ�
        // �L���b�V�����ł��悢�c�H
        // ���󓯊��ǂݍ��݂��Ă�̂Ń����_������Ȃ��Ă��������̂́A��X���l���Ă������Ă���
        callback(model);
    }

    /// <summary>
    /// �t�@�C���ǂݍ���
    /// </summary>
    /// <param name="file_name"></param>
    /// <param name="out_raw_data"></param>
    void ModelLoader::loadFile(const char* file_name, RawData& out_raw_data) {
        std::string warn;
        std::string err;
        bool result = tinyobj::LoadObj
        (
            &out_raw_data.attribute,
            &out_raw_data.shapes,
            &out_raw_data.materials,
            &warn,
            &err,
            file_name
        );
        if (result == false) {
            throw std::runtime_error(warn + err);
        }
    }

    /// <summary>
    /// �d�����Ă��钸�_ / index�̏�����index�̍쐬
    /// </summary>
    /// <param name="out_raw_data"></param>
    void ModelLoader::distinctVertex(RawData& out_raw_data) {

        // �ǂݍ��ݖ��ɒ��_�̏d���������Ă���̂Ŗ��ʊ�
        // import���ɂ���΂������ǈ�U���u
        for (const auto& shape : out_raw_data.shapes) {
            for (const auto& index : shape.mesh.indices) {
                Vertex vertex = {};
                auto attribute = out_raw_data.attribute;
                auto vertices = out_raw_data.vertices;
                auto unique_vertices = out_raw_data.unique_vertices;

                vertex.pos = {
                    attribute.vertices[3 * index.vertex_index + 0],
                    attribute.vertices[3 * index.vertex_index + 1],
                    attribute.vertices[3 * index.vertex_index + 2]
                };
                vertex.texCoord = {
                    attribute.texcoords[2 * index.texcoord_index + 0],
                    1.0f - attribute.texcoords[2 * index.texcoord_index + 1]
                };
                vertex.color = { 1.0f, 1.0f, 1.0f };

                if (unique_vertices.count(vertex) == 0) {
                    unique_vertices[vertex] = static_cast<uint32_t>(vertices.size());
                    vertices.push_back(vertex);
                }
                out_raw_data.indices.push_back(unique_vertices[vertex]);
            }
        }
    }

    /// <summary>
    /// ���_ / index��CommandBuffer�ɏ悹��`���ɕϊ�
    /// </summary>
    /// <param name="raw_data"></param>
    void ModelLoader::createDrawableBuffer(const RawData& raw_data, std::shared_ptr<DrawableBuffer>& out_buffer) {
        out_buffer = std::make_shared<DrawableBuffer>(graphics_backend_, raw_data.vertices, raw_data.indices);
        out_buffer->create();
    }
} // rengine