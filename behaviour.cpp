#include "behaviour.h"
#include "hierarchy_service.h"

namespace cengine
{
    Behaviour::Behaviour()
    : is_active_(true) {
        HierarchyService::add(this);
    }
    Behaviour::Behaviour(const Behaviour& self)
    : is_active_(true) {
        HierarchyService::add(this);
    }
} // cengine