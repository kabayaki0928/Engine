#pragma once

#include <functional>

namespace rengine
{
    /// <summary>
    /// �ǂݍ��݋@�\�����邱�Ƃ������C���^�[�t�F�[�X
    /// Texture / Model / Material���̃��\�[�X�P�ʂł͂Ȃ�������w�O���̃��m
    /// �ڂ�����SimpleLoader�Q�Ƃ̂���
    /// </summary>
    class ILoader
    {
    public:
        ~ILoader() {}

        template<typename T>
        void load(const char* file_name, std::function<void(T)> callback) = 0;
    };
} // rengine