#include "default_draw_service.h"

#include "model_renderer.h"
#include "idraw_service.h"

namespace rengine
{
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    DefaultDrawService::DefaultDrawService()
    : buffer_list_(100) {
    }

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    DefaultDrawService::~DefaultDrawService() {
        SpModelRendererList().swap(buffer_list_);
    }

    /// <summary>
    /// �ǉ�
    /// </summary>
    /// <param name="drawable_buffer"></param>
    void DefaultDrawService::add(SpModelRenderer const renderer) {
        buffer_list_.emplace_back(renderer);
    }

    /// <summary>
    /// �폜
    /// </summary>
    /// <param name="renderer"></param>
    void DefaultDrawService::remove(SpModelRenderer const renderer) {
        // TODO �����j�����Ă�����̂̂��̃^�C�~���O�ł�nullptr��������Ă�����
        // �J�[�ł���^�C�~���O�ŊJ������Ƃ������@�ł�������������Ȃ�
        // �����܂�default�Ȃ̂Ŋg�����K�v�����Ȃ炻�����őΉ�����
        for (auto itr = buffer_list_.begin(); itr != buffer_list_.end(); itr++) {
            if (*(itr) == renderer) {
                buffer_list_.erase(itr);
                break;
            }
        }
        // �ł��������̂̏d������v�f�͓���Ȃ��z��Ȃ̂ň�U��L�̂܂܂�
        // buffer_list_.erase(std::remove(buffer_list_.begin(), buffer_list_.end(), renderer));
    }

    /// <summary>
    /// �擾
    /// </summary>
    /// <returns></returns>
    SpModelRendererList DefaultDrawService::get() const noexcept {
        return buffer_list_;
    }
    
} // rengine
