#pragma once

namespace cengine
{
    /// <summary>
    /// Behaviour�ɑ΂��ċ@�\��t�^����N���X
    /// </summary>
    class Component
    {
    private:
        bool is_enable_;
    public:
        Component() : is_enable_(true) {}
        Component(const Component& component) : is_enable_(true) {}

        bool isEnable() const noexcept { return is_enable_; }
        bool setEnable(bool const is_enable) { is_enable_ = is_enable; }
        void toggleEnable() { is_enable_ = !is_enable_; }
    };
} // cengine