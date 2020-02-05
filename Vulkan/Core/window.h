#ifndef WINDOWH
#define WINDOWH

#include <GLFW/glfw3.h>
#include "igraphics_handle.h"
#include "iwindow.h"
#include "vulkan_graphics_backend.h"

namespace vengine
{
    /// <summary>
    /// Window�N���X
    /// </summary>
    class GLFWWindow final : public rengine::IWindow
    {
    private:
        std::shared_ptr<VulkanGraphicsBackend> graphics_backend_;
        GLFWwindow* window_;
        bool is_frame_buffer_resized_;
    public:
        /// <summary>
        /// �R���X�g���N�^ 
        /// </summary>
        /// <param name="name">�E�B���h�E�ɕ\�����閼�O</param>
        /// <param name="width">�E�B���h�E����</param>
        /// <param name="height">�E�B���h�E�c��</param>
        GLFWWindow(std::shared_ptr<VulkanGraphicsBackend> graphics_backend, const char* name, const int& width, const int& height) {
            glfwInit();

            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

            window_ = glfwCreateWindow(width, height, name, nullptr, nullptr);
            glfwSetWindowUserPointer(window_, this);
            glfwSetFramebufferSizeCallback(window_, GLFWWindow::framebufferResizeCallback);
        }
        /// <summary>
        /// �f�X�g���N�^
        /// </summary>
        ~GLFWWindow() {
            window_ = nullptr;
        }
        /// <summary>
        /// �������
        /// </summary>
        void dispose() const {
            glfwDestroyWindow(window_);
        }

        //-----------------------------------------
        // override�Q
        /// <summary>
        /// �쐬����
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
        /// �E�B���h�E�Ȃɂ������̗��R�ŕ���K�v�����邩
        /// <para>��̂̓E�B���h�E������ꂽ�Ƃ���true��Ԃ�</para>
        /// </summary>
        /// <returns></returns>
        bool isShouldClose() const override {
            return glfwWindowShouldClose(window_);
        }
        /// <summary>
        /// �t���[���o�b�t�@�����T�C�Y���ꂽ���ǂ���
        /// </summary>
        /// <returns></returns>
        bool isFrameBufferResized() const noexcept override {
            return is_frame_buffer_resized_;
        }

        //-----------------------------------------
        // operator�Q
        operator GLFWwindow*() const {
            return window_;
        }
        operator const GLFWwindow*() const {
            return window_;
        }
        //-----------------------------------------
        /// <summary>
        /// �t���[���o�b�t�@�����T�C�Y�����^�C�~���O�ŌĂяo�����R�[���o�b�N�֐�
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