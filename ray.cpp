#include "ray.h"
#include "vector3.h"

namespace cengine
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    Ray::Ray() {
    }

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="origin">原点</param>
    /// <param name="direction">方向</param>
    Ray::Ray(const Vector3& origin, const Vector3& direction)
    : origin_(origin),
      direction_(direction){
    }

    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="ray"></param>
    Ray::Ray(const Ray& ray)
        : origin_(ray.origin_),
        direction_(ray.direction_) {
    }

    Vector3 Ray::pointAtParameter(float t) const {
        return origin_ + direction_ * t;
    }
} // cengine