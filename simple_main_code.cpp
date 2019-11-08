#include "SimpleMainCode.h"

#include "graphics_backend.h"

namespace vengine
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    SimpleMainCode::SimpleMainCode(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend) {
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    SimpleMainCode::~SimpleMainCode() {
    }

    /// <summary>
    /// 初期化処理
    /// エンジン側(GraphicsBackend)初期化終了後に呼び出される
    /// </summary>
    void SimpleMainCode::initialize() {

    }

    /// <summary>
    /// 更新処理
    /// </summary>
    void SimpleMainCode::update() {

    }

    /// <summary>
    /// 描画前処理
    /// </summary>
    void SimpleMainCode::prepareDraw() {

    }

    /// <summary>
    /// 描画後処理
    /// </summary>
    void SimpleMainCode::lateDraw() {

    }

} // vengine
