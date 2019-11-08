#pragma once

#include "vector3.h"

namespace cengine
{
    class Ray
    {
    public:
        Ray();
        Ray(const Vector3& origin, const Vector3& direction);
        Ray(const Ray& ray);
        Vector3 origin_;
        Vector3 direction_;
        Vector3 origin() const noexcept { return origin_; }
        Vector3 direction() const noexcept { return direction_; }
        Vector3 pointAtParameter(float t) const;
    };
} // cengine
