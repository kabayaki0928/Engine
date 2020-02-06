#pragma once

#include "ihierarchy_service.h"

namespace cengine
{
    class Behaviour;

    /// <summary>
    /// �W���q�G�����L�[�T�[�r�X
    /// TODO �o�^����Ă���v�f�̉���
    /// TODO �p�t�H�[�}���X�v��
    /// TODO UI�֘A(�����܂ł��̃N���X�ł�邩�͔���)
    /// </summary>
    class DefaultHierarchyService final : public IHierarchyService
    {
    private:
        std::vector<Behaviour*> behaviour_list_;
    public:
        DefaultHierarchyService();
        ~DefaultHierarchyService();

        void add(Behaviour* const behaviour) override;
        void update() override;
    };
} // cengine