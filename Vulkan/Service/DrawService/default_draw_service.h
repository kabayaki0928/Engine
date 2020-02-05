#pragma once

#include "idraw_service.h"

namespace rengine
{
    /// <summary>
    /// �`�惋�[�`���ւ̃A�N�Z�X��񋟂��邽�߂̈�ʓI�ȃN���X
    /// ���X�g�ɒǉ����č폜���Ď擾���ł��邾���̋@�\������
    /// </summary>
    class DefaultDrawService final : public IDrawService
    {
    private:
        SpModelRendererList buffer_list_;
    public:
        DefaultDrawService();
        ~DefaultDrawService();

        void add(SpModelRenderer const renderer) noexcept override;
        void remove(SpModelRenderer const renderer) noexcept override;
        SpModelRendererList get() const noexcept override;
    };
} // rengine

