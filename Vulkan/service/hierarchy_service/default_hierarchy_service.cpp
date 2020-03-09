#include "default_hierarchy_service.h"
#include "../vulkan/component/behaviour.h"

namespace cengine
{
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    DefaultHierarchyService::DefaultHierarchyService()
    : behaviour_list_(100) {
    }

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    DefaultHierarchyService::~DefaultHierarchyService() {
        behaviour_list_.clear();
    }

    /// <summary>
    /// �U�镑�����N���X�̒ǉ�
    /// </summary>
    void DefaultHierarchyService::add(Behaviour* const behaviour) {
        behaviour_list_.push_back(behaviour);
    }

    void DefaultHierarchyService::update() {
        for (const auto& iterator : behaviour_list_) {
            iterator->update();
        }
    }

} // cengine
