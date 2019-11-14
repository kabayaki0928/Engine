#pragma once

#include "imain_code.h"
#include "iloader.h"

namespace vengine
{
    class VulkanGraphicsBackend;
    class rengine::Model;

    class SimpleMainCode final : public rengine::IMainCode
    {
    private:
        std::shared_ptr<rengine::ILoader> loader_;
        std::shared_ptr<rengine::Model> model_;
        std::shared_ptr<vengine::Shader> shader_;
        std::shared_ptr<vengine::Texture> texture_;
    public:
        SimpleMainCode(std::shared_ptr<rengine::ILoader> const loader);
        ~SimpleMainCode();

        void initialize() override;
        void update() override;
        void prepareDraw() override;
        void lateDraw() override;
    };
} // vengine

