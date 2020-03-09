#include "logical_device.h"

#include "../vulkan/core/vulkan_graphics_backend.h"
#include "physical_device.h"
#include "queue_family.h"

#include "../vulkan/utils/vulkan_utils.h"
#include "../main_loop/definition/user_define.h"

namespace vengine
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="graphics_backend"></param>
    LogicalDevice::LogicalDevice
    (
        std::shared_ptr<VulkanGraphicsBackend> const graphics_backend,
        std::shared_ptr<PhysicalDevice> const physical_device
    ) {
        graphics_backend_ = graphics_backend;
        physical_device_ = physical_device;
        create();
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    LogicalDevice::~LogicalDevice() {
        graphics_backend_.reset();
        graphics_backend_ = nullptr;
        physical_device_.reset();
        physical_device_ = nullptr;
    }

    /// <summary>
    /// VkDevice生成処理
    /// </summary>
    void LogicalDevice::create() {
        LogicalDevice::create(&device_, graphics_backend_->getPhysicalDevice(), graphics_backend_->getVulkanSurface());
    }

    /// <summary>
    /// VkDevice生成処理
    /// </summary>
    /// <param name="device">論理デバイス</param>
    /// <param name="physical_device">物理デバイス</param>
    /// <param name="surface">サーフェース</param>
    void LogicalDevice::create(VkDevice* out_device, const PhysicalDevice& physical_device, const Surface& surface) {

        QueueFamilyIndices indices = QueueFamily::findQueueFamilies(physical_device, surface);

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies) {
            VkDeviceQueueCreateInfo queueCreateInfo = {};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkPhysicalDeviceFeatures deviceFeatures = {};

        VkDeviceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.pEnabledFeatures = &deviceFeatures;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(user_define::deviceExtensions.size());
        createInfo.ppEnabledExtensionNames = user_define::deviceExtensions.data();

        if (user_define::enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(user_define::validationLayers.size());
            createInfo.ppEnabledLayerNames = user_define::validationLayers.data();
        }
        else {
            createInfo.enabledLayerCount = 0;
        }

        VkResult result = vkCreateDevice(physical_device, &createInfo, nullptr, out_device);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to create logical device!");
        }
    }
} // vengine