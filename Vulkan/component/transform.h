#pragma once

#include "../math/vector3.h"
#include "../math/quaternion.h"

// rengine内でもいいかも…？
namespace cengine
{
    typedef struct Transform
    {
        Vector3 position_;
        //cengine::Quaternion rotation_;

    } Transform;
} // vengine

