#include "default_hierarchy_service.h"
#include "../vulkan/component/behaviour.h"

namespace cengine
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    DefaultHierarchyService::DefaultHierarchyService()
    : behaviour_list_(100) {
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    DefaultHierarchyService::~DefaultHierarchyService() {
        behaviour_list_.clear();
    }

    /// <summary>
    /// 振る舞い基底クラスの追加
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
