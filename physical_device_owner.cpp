#include "physical_device_owner.h"

#include "igraphics_backend.h"
#include "queue_family.h"

namespace vengine
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="graphics_backend"></param>
    PhysicalDeviceOwner::PhysicalDeviceOwner(std::shared_ptr<VulkanGraphicsBackend> const vulkan_graphics_backend) {
        graphics_backend_ = vulkan_graphics_backend;
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    PhysicalDeviceOwner::~PhysicalDeviceOwner() {
        physical_devices_.clear();
        current_physical_device_.reset();
        current_physical_device_ = nullptr;
    }

    /// <summary>
    /// 初期化処理
    /// </summary>
    /// <returns></returns>
    void PhysicalDeviceOwner::initialize() {
        // ゲーム中にGPU増えたり減ったりすることはない(ハズ…)ものの
        // 一旦複数取得できるように
        // また、増減した際はInitialize関数を呼び出すことで再度取得しなおせるようにしておく
        usedIndex = 0;
        enumeratePhysicalDevice();
    }

    /// <summary>
    /// 現在取得可能な物理デバイスの列挙処理
    /// </summary>
    void PhysicalDeviceOwner::enumeratePhysicalDevice() {
        uint32_t deviceCount = 0;
        vkEnumeratePhysicalDevices(graphics_backend_->getVulkanInstance(), &deviceCount, nullptr);

        if (deviceCount == 0) {
            throw std::runtime_error("failed to find GPUs with Vulkan support!");
        }

        physical_devices_.resize(deviceCount);

        std::vector<VkPhysicalDevice> tmpVector(deviceCount);
        vkEnumeratePhysicalDevices(graphics_backend_->getVulkanInstance(), &deviceCount, tmpVector.data());

        auto isRegisterPhysicalDevice = false;
        for (const auto& device : tmpVector) {

            if (QueueFamily::isDeviceSuitable(graphics_backend_->getVulkanInstance(), device, graphics_backend_->getVulkanSurface())) {
                auto p = std::make_shared<PhysicalDevice>(device);
                if (!isRegisterPhysicalDevice) {
                    current_physical_device_ = p;
                    isRegisterPhysicalDevice = true;
                }
                physical_devices_.push_back(std::move(p));
            }
        }

        if (current_physical_device_ == VK_NULL_HANDLE) {
            throw std::runtime_error("failed to find a suitable GPU!");
        }
    }

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    std::shared_ptr<PhysicalDevice> PhysicalDeviceOwner::getUnUsedDevice() {
        if (usedIndex == -1) {
            // 物理デバイスの初期化処理
            initialize();
        }
        else {
            ++usedIndex;
        }
        // TODO 上限時の処理は要件等
        if (physical_devices_.size() >= usedIndex) {
            throw std::runtime_error("failed to allocate unused physicaldevice.");
        }
        current_physical_device_ = physical_devices_[usedIndex];

        return current_physical_device_;
    }

    /// <summary>
    /// 
    /// </summary>
    /// <returns></returns>
    std::shared_ptr<PhysicalDevice> PhysicalDeviceOwner::getCurrentDevice() {

        if (usedIndex == -1) {
            // 物理デバイスの初期化処理
            initialize();
        }
        return current_physical_device_;
    }
} // vengine