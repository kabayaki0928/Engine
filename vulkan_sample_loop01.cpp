#include "stdafx.h"
#include "vulkan_sample_loop01.h"

#include "vulkan_graphics_backend.h"
#include "vulkan_render_pipeline.h"
#include "simple_main_code.h"

#include "user_define.h"

namespace vengine
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    VulkanSampleLoop01::VulkanSampleLoop01()
    : graphics_backend_(std::make_shared<VulkanGraphicsBackend>("test", "vulkan", user_define::WIDTH, user_define::HEIGHT)),
      render_pipeline_(std::make_unique<IRenderPipeline>(new VulkanRenderPipeline(graphics_backend_))),
      main_code_(std::make_unique<IMainCode>(new SimpleMainCode(graphics_backend_))) {
        // note
        /*
        暫定でコンストラクタの内側でnewするようにしたものの、SimpleMainLoopでまかなえそうな感が強い
        サンプルを動かすためにクラスが一つ増えるのはちょっと無駄感があるので要再考
        */
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    VulkanSampleLoop01::~VulkanSampleLoop01() {
    }

    /// <summary>
    /// 初期化処理
    /// </summary>
    void VulkanSampleLoop01::initialize() {
        graphics_backend_->initialize();
        main_code_->initialize();
    }

    /// <summary>
    /// 実行
    /// </summary>
    void VulkanSampleLoop01::run() {
        main_code_->update();
        while (!graphics_backend_->getWindow()->isShouldClose()) {
            main_code_->prepareDraw();
            render_pipeline_->draw();
            main_code_->lateDraw();
        }
    }
} // vengine
