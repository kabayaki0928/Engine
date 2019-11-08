#ifndef VULKAN_UTILSH
#define VULKAN_UTILSH

#define GLFW_INCLUDE_VULKAN

#include <glm/glm.hpp>

// 雑記 GraphicsBackEnd(存在しない)にこのあたりを逃がして
// DirectxでもVulkanでもMetalでも動くようにするとよりよさそう
// データ的にはconstruct injectionしていくのがよさそうな雰囲気
// main層(Serviceとして切り出しても可)から渡すものはGraphicsBackEnd

#include "vulkan_graphics_backend.h"
#include "command_buffer.h"

namespace vengine
{
    /// <summary>
    /// サポート情報の詳細を保持する構造体
    /// </summary>
    struct SwapChainSupportDetails {
        VkSurfaceCapabilitiesKHR capabilities;
        std::vector<VkSurfaceFormatKHR> formats;
        std::vector<VkPresentModeKHR> presentModes;
    };


    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    namespace VulkanUtils
    {
        // 雑多な関数まとめ
        /// <summary>
        /// glfwの拡張機能の取得
        /// </summary>
        /// <returns></returns>
        static std::vector<const char*> getRequiredExtensions(const bool isEnableValidationLayers) {
            uint32_t glfwExtensionCount = 0;
            const char** glfwExtensions;
            glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

            std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

            if (isEnableValidationLayers) {
                extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
            }

            return extensions;
        }
        /// <summary>
        /// スワップチェーンに使用するフォーマットの取得
        /// </summary>
        /// <param name="availableFormats"></param>
        /// <returns></returns>
        static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats) {
            for (const auto& availableFormat : availableFormats) {
                if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
                    return availableFormat;
                }
            }

            return availableFormats[0];
        }

        /// <summary>
        /// スワップチェーンの扱い方を選択する
        /// https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkPresentModeKHR.html
        /// </summary>
        /// <param name="availablePresentModes"></param>
        /// <returns></returns>
        static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes) {
            VkPresentModeKHR bestMode = VK_PRESENT_MODE_FIFO_KHR;

            for (const auto& availablePresentMode : availablePresentModes) {
                /*
                specifies that the presentation engine waits for the next vertical blanking period to update the current image.
                Tearing cannot be observed.
                An internal single-entry queue is used to hold pending presentation requests.
                If the queue is full when a new presentation request is received,
                the new request replaces the existing entry, and any images associated with the prior entry become available for re-use by the application.
                One request is removed from the queue and processed during each vertical blanking period in which the queue is non-empty.
                */
                // MAILBOX設定が入ってるならそれを使用する
                if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
                    return availablePresentMode;
                }
                else if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR) {
                    bestMode = availablePresentMode;
                }
            }

            return bestMode;
        }


        /// <summary>
        /// スワップチェーンの横幅縦幅の取得
        /// </summary>
        /// <param name="window"></param>
        /// <param name="capabilities"></param>
        /// <param name="width">[Out]横幅</param>
        /// <param name="height">[OUt]縦幅</param>
        /// <returns></returns>
        static VkExtent2D chooseSwapExtent
        (
            const GLFWwindow* window,
            const VkSurfaceCapabilitiesKHR& capabilities,
            const int& width,
            const int& height
        ) {
            if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
                return capabilities.currentExtent;
            }
            else {
                VkExtent2D actualExtent = { width, height };

                //actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
                //actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

                int width, height;
                glfwGetFramebufferSize(const_cast<GLFWwindow*>(window), &width, &height);
                actualExtent = {
                    static_cast<uint32_t>(width),
                    static_cast<uint32_t>(height)
                };
                return actualExtent;
            }
        }

        static VkFormat findSupportedFormat
        (
            std::shared_ptr<VulkanGraphicsBackend> const graphics_backend,
            const std::vector<VkFormat>& candidates,
            VkImageTiling tiling,
            VkFormatFeatureFlags features
        ) {
            for (VkFormat format : candidates) {
                VkFormatProperties props;
                vkGetPhysicalDeviceFormatProperties(graphics_backend->getPhysicalDevice(), format, &props);

                if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
                    return format;
                }
                else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
                    return format;
                }
            }

            throw std::runtime_error("failed to find supported format!");
        }

        static VkFormat findDepthFormat(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend) {
            return findSupportedFormat(
                graphics_backend,
                { VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT },
                VK_IMAGE_TILING_OPTIMAL,
                VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
            );
        }


        static VkSampleCountFlagBits getMaxUsableSampleCount(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend) {
            VkPhysicalDeviceProperties physical_device_properties;
            vkGetPhysicalDeviceProperties(graphics_backend->getPhysicalDevice(), &physical_device_properties);

            VkSampleCountFlags counts = std::min(physical_device_properties.limits.framebufferColorSampleCounts, physical_device_properties.limits.framebufferDepthSampleCounts);
            if (counts & VK_SAMPLE_COUNT_64_BIT) { return VK_SAMPLE_COUNT_64_BIT; }
            if (counts & VK_SAMPLE_COUNT_32_BIT) { return VK_SAMPLE_COUNT_32_BIT; }
            if (counts & VK_SAMPLE_COUNT_16_BIT) { return VK_SAMPLE_COUNT_16_BIT; }
            if (counts & VK_SAMPLE_COUNT_8_BIT) { return VK_SAMPLE_COUNT_8_BIT; }
            if (counts & VK_SAMPLE_COUNT_4_BIT) { return VK_SAMPLE_COUNT_4_BIT; }
            if (counts & VK_SAMPLE_COUNT_2_BIT) { return VK_SAMPLE_COUNT_2_BIT; }

            return VK_SAMPLE_COUNT_1_BIT;
        }
         
        static bool checkValidationLayerSupport() {
            uint32_t layer_count;
            vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

            std::vector<VkLayerProperties> availableLayers(layer_count);
            vkEnumerateInstanceLayerProperties(&layer_count, availableLayers.data());

            for (const char* layerName : user_define::validationLayers) {

                for (const auto& layerProperties : availableLayers) {
                    if (strcmp(layerName, layerProperties.layerName) == 0) {
                        // layer found
                        return true;
                    }
                }
            }

            return false;
        }

        bool hasStencilComponent(VkFormat format) {
            return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
        }
    }
} // vengine
#endif