#pragma once

#include "../main_loop/interface/imain_loop.h"

namespace vengine
{
	namespace rengine
	{
		class IRenderPipeline;
		class IMainCode;
	}
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

