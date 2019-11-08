#include "simple_main_loop.h"

namespace rengine
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="graphics_backend"></param>
    /// <param name="render_pipeline"></param>
    /// <param name="main_code"></param>
    SimpleMainLoop::SimpleMainLoop
    (
        const IGraphicsBackend* graphics_backend,
        const IRenderPipeline* render_pipeline,
        const IMainCode* main_code
    ) : graphics_backend_(std::make_unique<IGraphicsBackend>(graphics_backend)),
        render_pipeline_(std::make_unique<IRenderPipeline>(render_pipeline)), 
        main_code_(std::make_unique<IMainCode>(main_code)) {
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    SimpleMainLoop::~SimpleMainLoop() {
        graphics_backend_ = nullptr;
        render_pipeline_ = nullptr;
    }

    /// <summary>
    /// 初期化処理
    /// </summary>
    void SimpleMainLoop::initialize() {
        graphics_backend_->initialize();
        main_code_->initialize();
    }

    /// <summary>
    /// 実行処理
    /// </summary>
    void SimpleMainLoop::run() {
        main_code_->update();
        while (!graphics_backend_->getWindow()->isShouldClose()) {
            main_code_->prepareDraw();
            render_pipeline_->draw();
            main_code_->lateDraw();
        }
    }
}
