#pragma once

#include "imain_loop.h"
#include "igraphics_backend.h"
#include "irender_pipeline.h"
#include "imain_code.h"

namespace vengine
{
    class VulkanGraphicsBackend;

    class VulkanSampleLoop01 final : public rengine::IMainLoop
    {
    private:
        std::shared_ptr<VulkanGraphicsBackend> graphics_backend_;
        std::unique_ptr<rengine::IRenderPipeline> render_pipeline_;
        std::unique_ptr<rengine::IMainCode> main_code_;
    public:
        VulkanSampleLoop01();
        ~VulkanSampleLoop01();

        virtual void initialize() override;
        virtual void run() override;
    };
} // vengine

