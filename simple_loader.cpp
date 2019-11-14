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
    /// �R���X�g���N�^
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
    /// �f�X�g���N�^
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
    /// ���f���ǂݍ��ݏ���
    /// </summary>
    /// <param name="file_name">�t�@�C����</param>
    /// <param name="callback">�ǂݍ��݊�����ɌĂяo�����R�[���o�b�N</param>
    template<>
    void SimpleLoader::load(const char* file_name, std::function<void(std::shared_ptr<rengine::Model>)> callback) {
        model_loader_->load(file_name, callback);
    }

    /// <summary>
    /// ���_�V�F�[�_�[�ǂݍ���
    /// </summary>
    template<>
    void SimpleLoader::load(const char* file_name, std::function<void(std::shared_ptr<VertexShaderModule>)> callback) {
        // TODO �ݒ�l����������̂ŕʃt�@�C��(Unity�ł����Ƃ����meta�t�@�C��)�ɓ���������
        // template�̈����𑝂₷���@�ł��������Ȃƈ�u�v�������̂̕ʃt�@�C���ɓ������z��Ȃ̂ň�a��������̂̌���̂܂܂ŁB
        shader_loader_->loadVertexShader(file_name, callback);
    }

    /// <summary>
    /// �t���O�����g�V�F�[�_�[�ǂݍ���
    /// </summary>
    template<>
    void SimpleLoader::load(const char* file_name, std::function<void(std::shared_ptr<FragmentShaderModule>)> callback) {
        shader_loader_->loadFragmentShader(file_name, callback);
    }

    /// <summary>
    /// ���`�����l���t���e�N�X�`���ǂݍ���
    /// </summary>
    template<>
    void SimpleLoader::load(const char* file_name, std::function<void(texture::PixelData)> callback) {
        texture_loader_->loadWithAlpha(file_name, callback);
    }
} // rengine
