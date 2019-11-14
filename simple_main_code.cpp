#include "simple_main_code.h"

#include "vulkan_graphics_backend.h"
#include "simple_loader.h"
#include "model.h"
#include "shader.h"
#include "texture.h"

using SharedModel = std::shared_ptr<rengine::Model>;
using SharedVertexShaderModule = std::shared_ptr<vengine::VertexShaderModule>;
using SharedFragmentShaderModule = std::shared_ptr<vengine::FragmentShaderModule>;

namespace vengine
{
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    SimpleMainCode::SimpleMainCode(std::shared_ptr<ILoader> const loader)
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
        shader_ = std::make_shared<Shader>(vertex_shader, fragment_shader);
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
