#ifndef WINDOWH
#define WINDOWH

#include <GLFW/glfw3.h>
#include "igraphics_handle.h"
#include "iwindow.h"
#include "vulkan_graphics_backend.h"

namespace vengine
{
    /// <summary>
    /// Windowクラス
    /// </summary>
    class GLFWWindow final : public rengine::IWindow
    {
    private:
        std::shared_ptr<VulkanGraphicsBackend> graphics_backend_;
        GLFWwindow* window_;
        bool is_frame_buffer_resized_;
    public:
        /// <summary>
        /// コンストラクタ 
        /// </summary>
        /// <param name="name">ウィンドウに表示する名前</param>
        /// <param name="width">ウィンドウ横幅</param>
        /// <param name="height">ウィンドウ縦幅</param>
        GLFWWindow(std::shared_ptr<VulkanGraphicsBackend> graphics_backend, const char* name, const int& width, const int& height) {
            glfwInit();

            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

            window_ = glfwCreateWindow(width, height, name, nullptr, nullptr);
            glfwSetWindowUserPointer(window_, this);
            glfwSetFramebufferSizeCallback(window_, GLFWWindow::framebufferResizeCallback);
        }
        /// <summary>
        /// デストラクタ
        /// </summary>
        ~GLFWWindow() {
            window_ = nullptr;
        }
        /// <summary>
        /// 解放処理
        /// </summary>
        void dispose() const {
            glfwDestroyWindow(window_);
        }

        //-----------------------------------------
        // override群
        /// <summary>
        /// 作成処理
        /// </summary>
        void create() override {
            is_frame_buffer_resized_ = false;

            int width = 0, height = 0;
            while (width == 0 || height == 0) {
                glfwGetFramebufferSize(window_, &width, &height);
                glfwWaitEvents();
            }
        }
        /// <summary>
        /// ウィンドウなにがしかの理由で閉じる必要があるか
        /// <para>大体はウィンドウが閉じられたときにtrueを返す</para>
        /// </summary>
        /// <returns></returns>
        bool isShouldClose() const override {
            return glfwWindowShouldClose(window_);
        }
        /// <summary>
        /// フレームバッファがリサイズされたかどうか
        /// </summary>
        /// <returns></returns>
        bool isFrameBufferResized() const noexcept override {
            return is_frame_buffer_resized_;
        }

        //-----------------------------------------
        // operator群
        operator GLFWwindow*() const {
            return window_;
        }
        operator const GLFWwindow*() const {
            return window_;
        }
        //-----------------------------------------
        /// <summary>
        /// フレームバッファがリサイズされるタイミングで呼び出されるコールバック関数
        /// </summary>
        /// <param name="window"></param>
        /// <param name="width"></param>
        /// <param name="height"></param>
        static void framebufferResizeCallback(GLFWwindow* window, int width, int height) {
            auto app = reinterpret_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
            app->is_frame_buffer_resized_ = true;
        }
    };
} // EEngine

#endif