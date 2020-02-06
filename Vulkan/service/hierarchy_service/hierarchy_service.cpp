#include "hierarchy_service.h"

#include "default_hierarchy_service.h"
#include "behaviour.h"

namespace cengine
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="service"></param>
    HierarchyService::HierarchyService(std::shared_ptr<IHierarchyService> const service) {
        // staticなのでこれで正しい
        if (service_ != nullptr) {
            service_.reset();
        }
        service_ = service;
    }

    HierarchyService::~HierarchyService() {
        service_ = nullptr;
    }

    void HierarchyService::add(Behaviour* const behaviour) {
        if (service_ == nullptr) {
            service_ = std::make_shared<IHierarchyService>(new DefaultHierarchyService());
        }
        service_->add(behaviour);
    }
} // cengine