#include "simple_loader.h"

#include "model.h"
#include "model_loader.h"
#include "shader.h"
#include "shader_loader.h"
#include "texture.h"
#include "texture_loader.h"

namespace vengine
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="model_loader"></param>
    /// <param name="shader_loader"></param>
    SimpleLoader::SimpleLoader(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend)
    : model_loader_(std::make_unique<ModelLoader>()),
      shader_loader_(std::make_unique<ShaderLoader>(graphics_backend)),
      texture_loader_(std::make_unique<TextureLoader>())
    {

    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    SimpleLoader::~SimpleLoader() {

    }

    template<typename T>
    void SimpleLoader::load(const char* file_name, std::function<void(T)> callback) {
        std::shared_ptr<T> resource = std::make_shared(graphics_backend);

        resource->load(file_name);

        callback(resource);
    }

    /// <summary>
    /// モデル読み込み処理
    /// </summary>
    /// <param name="file_name">ファイル名</param>
    /// <param name="callback">読み込み完了後に呼び出されるコールバック</param>
    template<>
    void SimpleLoader::load(const char* file_name, std::function<void(std::shared_ptr<rengine::Model>)> callback) {
        model_loader_->load(file_name, callback);
    }

    /// <summary>
    /// 頂点シェーダー読み込み
    /// </summary>
    template<>
    void SimpleLoader::load(const char* file_name, std::function<void(std::shared_ptr<VertexShaderModule>)> callback) {
        // TODO 設定値が多すぎるので別ファイル(Unityでいうところのmetaファイル)に逃がしたい
        // templateの引数を増やす方法でもいいかなと一瞬思ったものの別ファイルに逃がす想定なので違和感あるものの現状のままで。
        shader_loader_->loadVertexShader(file_name, callback);
    }

    /// <summary>
    /// フラグメントシェーダー読み込み
    /// </summary>
    template<>
    void SimpleLoader::load(const char* file_name, std::function<void(std::shared_ptr<FragmentShaderModule>)> callback) {
        shader_loader_->loadFragmentShader(file_name, callback);
    }

    /// <summary>
    /// αチャンネル付きテクスチャ読み込み
    /// </summary>
    template<>
    void SimpleLoader::load(const char* file_name, std::function<void(texture::PixelData)> callback) {
        texture_loader_->loadWithAlpha(file_name, callback);
    }
} // rengine
