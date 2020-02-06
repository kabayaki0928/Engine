#pragma once

#include "ihierarchy_service.h"

namespace cengine
{
    class Behaviour;

    /// <summary>
    /// 標準ヒエラルキーサービス
    /// TODO 登録されている要素の可視化
    /// TODO パフォーマンス計測
    /// TODO UI関連(ここまでこのクラスでやるかは微妙)
    /// </summary>
    class DefaultHierarchyService final : public IHierarchyService
    {
    private:
        std::vector<Behaviour*> behaviour_list_;
    public:
        DefaultHierarchyService();
        ~DefaultHierarchyService();

        void add(Behaviour* const behaviour) override;
        void update() override;
    };
} // cengine