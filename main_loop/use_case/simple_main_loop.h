#pragma once

#include "../main_loop/interface/imain_loop.h"

namespace rengine
{
	class IGraphicsBackend;
	class IRenderPipeline;
	class IMainCode;

    class SimpleMainLoop final : public IMainLoop
    {
    private:
        std::unique_ptr<IGraphicsBackend> graphics_backend_;
        std::unique_ptr<IRenderPipeline> render_pipeline_;
        std::unique_ptr<IMainCode> main_code_;
    public:
        SimpleMainLoop
        (
            const IGraphicsBackend* graphics_backend,
            const IRenderPipeline* render_pipeline,
            const IMainCode* main_code
        );
        ~SimpleMainLoop();
        void initialize() override;
        void run() override;
        
    };
} // rengine