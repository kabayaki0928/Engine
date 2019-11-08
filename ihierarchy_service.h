#pragma once

namespace cengine
{
    class Behaviour;

    class IHierarchyService
    {
    public:
        ~IHierarchyService() {}

        virtual void add(Behaviour* const behaviour) = 0;
        virtual void update() = 0;
    };
} // cengine

