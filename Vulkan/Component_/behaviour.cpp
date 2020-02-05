#include "behaviour.h"
#include "hierarchy_service.h"
#include "transform.h"
#include "component.h"


namespace cengine
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Behaviour::Behaviour()
    : is_active_(true) {
        HierarchyService::add(this);
    }
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="self"></param>
    Behaviour::Behaviour(const Behaviour& self)
    : is_active_(true) {
        HierarchyService::add(this);
    }

    SharedComponent Behaviour::addComponent(SharedComponent const component) {
        components_.push_back(component);
    }
} // cengine