#pragma once

#include "quaternion.h"
#include "vector3.h"

// rengine内でもいいかも…？
namespace cengine
{
    typedef struct Transform
    {
        Vector3 position_;
        //cengine::Quaternion rotation_;

    } Transform;
} // vengine

