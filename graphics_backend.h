#ifndef GRAPHICS_BACKENDH
#define GRAPHICS_BACKENDH

#include "graphics_instance.h"
#include "igraphics_backend.h"
#include "VulkanDevice.h"
#include "Surface.h"
#include "SwapChain.h"
#include "UserDefine.h"
#include "Window.h"

namespace rengine
{
    /// <summary>
    /// 各GraphicsAPI毎の機能をまとめたもの
    /// </summary>
    class GraphicsBackend final
    {
    protected:
        std::shared_ptr<IGraphicsBackend> graphics_backend_;
    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="pGraphicsBackEnd"></param>
        GraphicsBackend(const IGraphicsBackend* graphics_back_end) {
            graphics_backend_ = std::make_shared<IGraphicsBackend>(graphics_back_end);
        }
        const IGraphicsBackend* operator -> () const noexcept {
            return graphics_backend_.get();
        }
    };

    typedef struct
    {
        const GLFWwindow* pWindow;
        const VkInstance& instance;
        const VkPhysicalDevice& physicalDevice;
        const VkDevice& device;
        const VkSurfaceKHR& surface;
    } CreateContainer;

} // rengine

#endif