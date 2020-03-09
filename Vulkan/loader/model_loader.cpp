#include "model_loader.h"

#include "drawable_buffer.h"
#include "../vulkan/graphics_resource/model/model.h"
#include "vertex.h"

namespace vengine
{
    /// <summary>
    /// 読み込み処理
    /// </summary>
    /// <param name="file_name"></param>
    /// <param name="callback"></param>
    void ModelLoader::load(const char* file_name, std::function<void(std::shared_ptr<rengine::Model>)> callback) {
        
        // TODO キャッシュ系の機能 

        RawData raw_data = {};
        std::shared_ptr<DrawableBuffer> drawable_buffer;

        loadFile(file_name, raw_data);
        distinctVertex(raw_data);
        createDrawableBuffer(raw_data, drawable_buffer);

        auto model = std::make_shared<rengine::Model>(drawable_buffer, nullptr);

        // TODO 破棄管理系の何かに追加
        // キャッシュ側でもよい…？
        // 現状同期読み込みしてるのでラムダ式じゃなくてもいいものの、後々を考えてこうしておく
        callback(model);
    }

    /// <summary>
    /// ファイル読み込み
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
    /// 重複している頂点 / indexの除去とindexの作成
    /// </summary>
    /// <param name="out_raw_data"></param>
    void ModelLoader::distinctVertex(RawData& out_raw_data) {

        // 読み込み毎に頂点の重複を除いているので無駄感
        // import時にやれればいいけど一旦放置
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
    /// 頂点 / indexをCommandBufferに乗せる形式に変換
    /// </summary>
    /// <param name="raw_data"></param>
    void ModelLoader::createDrawableBuffer(const RawData& raw_data, std::shared_ptr<DrawableBuffer>& out_buffer) {
        out_buffer = std::make_shared<DrawableBuffer>(graphics_backend_, raw_data.vertices, raw_data.indices);
        out_buffer->create();
    }
} // rengine