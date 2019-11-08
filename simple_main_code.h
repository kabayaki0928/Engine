#pragma once

#include "imain_code.h"

namespace vengine
{
    class VulkanGraphicsBackend;
    class SimpleMainCode final : public rengine::IMainCode
    {
    private:
        std::shared_ptr<VulkanGraphicsBackend> graphics_backend_;
    public:
        SimpleMainCode(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend);
        ~SimpleMainCode();

        void initialize() override;
        void update() override;
        void prepareDraw() override;
        void lateDraw() override;
    };
} // vengine

