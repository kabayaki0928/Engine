#pragma once

#include "transform.h"

namespace cengine
{
    class Component;

    using SharedComponent = std::shared_ptr<Component>;
    using SharedComponentList = std::vector<SharedComponent>;

    /// <summary>
    /// �U�镑���̒�`�p�N���X
    /// �V�[�����ɑ��݂��Ă��郂�m�͊�{�I�ɂ�����p�����Ă���z��
    /// </summary>
    class Behaviour
    {
    protected:
        Transform transform_;
        SharedComponentList components_;
        bool is_active_;
    public:
        Behaviour();
        Behaviour(const Behaviour& self);
        virtual void update() {}
        void setActive(const bool is_active) noexcept { is_active_ = is_active; }
        bool isActive() const noexcept { return is_active_; }
        const Transform& getTransform() const noexcept { return transform_; }


        SharedComponent addComponent(SharedComponent const component);
        template<typename T>
        T getComponent();
        //template<typename T>
        //std::iterator<T> getComponents();
    };
} // cengine
