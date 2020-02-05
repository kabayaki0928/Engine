#include "stdafx.h"
#include "material.h"

#include "shader.h"
#include "texture.h"

// GraphicsResourceフォルダ以下に存在するクラスに関しては
// ユーザとして使う側、RenderingEngine側で必要な機能と分離が出来ていないので修正が必要
namespace rengine
{
    Material::Material(SpShader const shader, SpTextures const textures) 
    : shader_(shader),
      textures_(textures) {
    }

    Material::~Material() {
    }
}