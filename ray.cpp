#include "ray.h"
#include "vector3.h"

namespace cengine
{
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Ray::Ray() {
    }

    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="origin">���_</param>
    /// <param name="direction">����</param>
    Ray::Ray(const Vector3& origin, const Vector3& direction)
    : origin_(origin),
      direction_(direction){
    }

    /// <summary>
    /// �R���X�g���N�^
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