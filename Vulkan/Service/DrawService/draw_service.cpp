#include "draw_service.h"

#include "idraw_service.h"

namespace rengine
{
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    DrawService::DrawService(const IDrawService* service)
    : service_(std::make_shared<IDrawService>(service)) {

    }

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    DrawService::~DrawService() {
        service_ = nullptr;
    }

    /// <summary>
    /// �`��ΏۂƂ��ēo�^
    /// </summary>
    /// <param name="renderer"></param>
    /// <returns></returns>
    void DrawService::add(SpModelRenderer const renderer) noexcept {
        service_->add(renderer);
    }

    /// <summary>
    /// �`��Ώۂ���폜
    /// </summary>
    /// <param name="renderer"></param>
    /// <returns></returns>
    void DrawService::remove(SpModelRenderer const renderer) noexcept {
        service_->remove(renderer);
    }

    /// <summary>
    /// �`��Ώۂ��擾
    /// </summary>
    /// <returns></returns>
    SpModelRendererList DrawService::get() noexcept {
        return service_->get();
    }

} // rengine
