#pragma once

#include "transform.h"

namespace cengine
{
    /// <summary>
    /// 振る舞いの定義用クラス
    /// シーン内に存在しているモノは基本的にこれを継承している想定
    /// </summary>
    class Behaviour
    {
    protected:
        Transform transform_;
        bool is_active_;
    public:
        Behaviour();
        Behaviour(const Behaviour& self);
        virtual void update() {}
        void setActive(const bool is_active) noexcept { is_active_ = is_active; }
        bool isActive() const noexcept { return is_active_; }
        const Transform& getTransform() const noexcept { return transform_; }
    };
} // cengine
