#include "stdafx.h"
#include "material.h"

#include "shader.h"
#include "texture.h"

// GraphicsResource�t�H���_�ȉ��ɑ��݂���N���X�Ɋւ��Ă�
// ���[�U�Ƃ��Ďg�����ARenderingEngine���ŕK�v�ȋ@�\�ƕ������o���Ă��Ȃ��̂ŏC�����K�v
namespace rengine
{
    Material::Material(SpShader const shader, SpTextures const textures) 
    : shader_(shader),
      textures_(textures) {
    }

    Material::~Material() {
    }
}