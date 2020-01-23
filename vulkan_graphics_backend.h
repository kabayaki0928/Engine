#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "igraphics_backend.h"
#include "iwindow.h"
#include "igraphics_instance.h"
#include "igraphics_device.h"
#include "isurface.h"
#include "iswapchain.h"

#include "custom_allocator.h"
#include "graphics_device.h"
#include "graphics_instance.h"
#include "vulkan_instance.h"
#include "vulkan_device.h"
#include "physical_device_owner.h"
#include "physical_device.h"
#include "logical_device.h"
#include "surface.h"
#include "swapchain.h"
#include "window.h"

namespace vengine {

    /// <summary>
    /// VulkanのGraphicsAPIを使用するためのクラス
    /// VulkanAPI群(主にnamespace vengine側はVulaknGraphicsBackend型の参照を保持し
    /// それ以外のメイン層はIGraphicsBackendで保持するイメージ
    /// </summary>
    class VulkanGraphicsBackend final : public std::enable_shared_from_this<VulkanGraphicsBackend>,
                                        public rengine::IGraphicsBackend
    {
    private:
        std::shared_ptr<VulkanGraphicsBackend>  self_;
        std::unique_ptr<GLFWWindow>             window_;
        std::unique_ptr<VulkanInstance>         instance_;
        std::unique_ptr<VulkanDevice>           device_;
        std::unique_ptr<Surface>                surface_;
        std::unique_ptr<Swapchain>              swapchain_;
        std::unique_ptr<CustomAllocator>        allocator_;
    public:
        VulkanGraphicsBackend(const char* name, const char* engine_name, const int& width, const int& height);
        ~VulkanGraphicsBackend();

        //---------------------------------------------------------------
        // override
        void initialize() override;
        void recreateSwapchain() override;
        inline const rengine::IWindow* getWindow() const noexcept override {
            return window_.get();
        }
        inline const rengine::IGraphicsInstance* getInstance() const noexcept override {
            return instance_.get();
        }
        inline const rengine::IGraphicsDevice* getDevice() const noexcept override {
            return device_.get();
        }
        inline const rengine::ISurface* getSurface() const noexcept override {
            return surface_.get();
        }
        inline const rengine::ISwapchain* getSwapchain() const noexcept override {
            return swapchain_.get();
        }

        //---------------------------------------------------------------
        // Vulkan関連
        const GLFWWindow& getGLFWWindow() const noexcept {
            return *window_.get();
        }
        const VulkanInstance& getVulkanInstance() const noexcept {
            return *instance_.get();
        }
        const PhysicalDevice& getPhysicalDevice() const noexcept {
            return (*(*device_->getPhysicalDevice()).get());
        }
        const LogicalDevice& getLogicalDevice() const noexcept {
            return (*(*device_->getLogicalDevice()).get());
        }
        const Surface& getVulkanSurface() const noexcept {
            return *surface_.get();
        }
        const Swapchain& getVulkanSwapchain() const noexcept {
            return *swapchain_.get();
        }
        const CustomAllocator& getAllocator() const noexcept {
            return *allocator_.get();
        }
    };

} // vengine