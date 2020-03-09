#include "../../stdafx.h"

#include "simple_main_code.h"

#include "../vulkan/core/vulkan_graphics_backend.h"
#include "../vulkan/loader/iloader.h"
#include "../vulkan/loader/simple_loader.h"
#include "../vulkan/graphics_resource/model/model.h"
#include "../vulkan/graphics_resource/shader/ishader_parameter.h"
#include "../vulkan/graphics_resource/shader/shader.h"
#include "../vulkan/graphics_resource/texture/texture.h"
#include "../vulkan/primitive/vertex.h"

#include "simple_shader_parameter.h"

using SharedModel = std::shared_ptr<rengine::Model>;
using SharedVertexShaderModule = std::shared_ptr<vengine::VertexShaderModule>;
using SharedFragmentShaderModule = std::shared_ptr<vengine::FragmentShaderModule>;

namespace vengine
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    SimpleMainCode::SimpleMainCode(std::shared_ptr<rengine::ILoader> const loader)
    : loader_(loader),
      model_(nullptr),
      shader_(nullptr) {
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    SimpleMainCode::~SimpleMainCode() {
    }

    /// <summary>
    /// 初期化処理
    /// エンジン側(GraphicsBackend)初期化終了後に呼び出される
    /// </summary>
    void SimpleMainCode::initialize() {
        auto count = 0;

        loader_->load<SharedModel>("models/chalet.obj", [&](SharedModel resource) -> void { model_ = resource; ++count; });
        loader_->load<texture::PixelData>("textures/chalet.jpg", [&](texture::PixelData data) -> void { texture_ = std::shared_ptr<Texture>(graphics_backend, data); });

        SharedVertexShaderModule vertex_shader;
        SharedFragmentShaderModule fragment_shader;
        loader_->load<SharedVertexShaderModule>  ("", [&](SharedVertexShaderModule resource)   -> void { vertex_shader = resource; });
        loader_->load<SharedFragmentShaderModule>("", [&](SharedFragmentShaderModule resource) -> void { fragment_shader = resource; });
        
        // 本当は処理待ちしないといけないけどそのままShaderを作る
        shader_ = std::make_shared<Shader>(vertex_shader, fragment_shader, std::make_shared<IShaderParameter>(new SimpleShaderParameter()));
    }

    /// <summary>
    /// 更新処理
    /// </summary>
    void SimpleMainCode::update() {

    }

    /// <summary>
    /// 描画前処理
    /// </summary>
    void SimpleMainCode::prepareDraw() {

    }

    /// <summary>
    /// 描画後処理
    /// </summary>
    void SimpleMainCode::lateDraw() {

    }

} // vengine
