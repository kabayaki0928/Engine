#pragma once
#include "ihierarchy_service.h"

namespace cengine
{
    class Behaviour;

    /// <summary>
    /// 
    /// </summary>
    class HierarchyService
    {
    private:
        static std::shared_ptr<IHierarchyService> service_;
    public:
        HierarchyService(std::shared_ptr<IHierarchyService> service);
        ~HierarchyService();

        static void add(Behaviour* const behaviour);
    };
} // cengine