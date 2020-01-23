#include "stdafx.h"
#include "material.h"

#include "shader.h"
#include "texture.h"

namespace rengine
{
    Material::Material(SpShader const shader, SpTextures const textures) 
    : shader_(shader),
      textures_(textures) {
    }

    Material::~Material() {
    }
}