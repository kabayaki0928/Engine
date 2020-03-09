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
    /// �R���X�g���N�^
    /// </summary>
    SimpleMainCode::SimpleMainCode(std::shared_ptr<rengine::ILoader> const loader)
    : loader_(loader),
      model_(nullptr),
      shader_(nullptr) {
    }

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    SimpleMainCode::~SimpleMainCode() {
    }

    /// <summary>
    /// ����������
    /// �G���W����(GraphicsBackend)�������I����ɌĂяo�����
    /// </summary>
    void SimpleMainCode::initialize() {
        auto count = 0;

        loader_->load<SharedModel>("models/chalet.obj", [&](SharedModel resource) -> void { model_ = resource; ++count; });
        loader_->load<texture::PixelData>("textures/chalet.jpg", [&](texture::PixelData data) -> void { texture_ = std::shared_ptr<Texture>(graphics_backend, data); });

        SharedVertexShaderModule vertex_shader;
        SharedFragmentShaderModule fragment_shader;
        loader_->load<SharedVertexShaderModule>  ("", [&](SharedVertexShaderModule resource)   -> void { vertex_shader = resource; });
        loader_->load<SharedFragmentShaderModule>("", [&](SharedFragmentShaderModule resource) -> void { fragment_shader = resource; });
        
        // �{���͏����҂����Ȃ��Ƃ����Ȃ����ǂ��̂܂�Shader�����
        shader_ = std::make_shared<Shader>(vertex_shader, fragment_shader, std::make_shared<IShaderParameter>(new SimpleShaderParameter()));
    }

    /// <summary>
    /// �X�V����
    /// </summary>
    void SimpleMainCode::update() {

    }

    /// <summary>
    /// �`��O����
    /// </summary>
    void SimpleMainCode::prepareDraw() {

    }

    /// <summary>
    /// �`��㏈��
    /// </summary>
    void SimpleMainCode::lateDraw() {

    }

} // vengine
