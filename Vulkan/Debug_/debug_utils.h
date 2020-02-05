#ifndef DEBUG_UTILSH
#define DEBUG_UTILSH

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <iostream>

#include "vulkan_utils.h"
#include "user_define.h"

#include "vulkan_graphics_backend.h"

namespace vengine
{
namespace debug
{
    class Messanger
    {
    private:
        std::shared_ptr<VulkanGraphicsBackend> graphics_backend_;
        VkDebugUtilsMessengerEXT debug_messenger_;
    public:
        Messanger(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend);
        ~Messanger();

        /// <summary>
        /// ���b�Z�[�W�̎󂯎���ʂ̐ݒ菈��
        /// </summary>
        /// <param name="instance"></param>
        /// <param name="enableValidationLayer"></param>
        void setupDebug(const VkInstance& instance, bool enableValidationLayer) {
            setupDebugMessenger(instance, enableValidationLayer, &debug_messenger_);
        }

        /// <summary>
        /// �f�o�b�O���b�Z�[�W�̎󂯎����̐ݒ�
        /// </summary>
        /// <param name="instance">vulkan instance</param>
        /// <param name="enableValidationLayers">Validation Layer��L�������邩�ǂ���</param>
        /// <param name="debugMessanger">[Out]�󂯎��v�N���X ��enableValidationLayers���^�̂Ƃ������ŏ����������</param>
        static void setupDebugMessenger 
        (
            const VkInstance& instance,
            bool enableValidationLayers,
            VkDebugUtilsMessengerEXT* debugMessanger
        ) {
            if (!enableValidationLayers) return;

            VkDebugUtilsMessengerCreateInfoEXT createInfo;
            populateDebugMessengerCreateInfo(createInfo);

            VkResult result = CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, debugMessanger);
            if (result != VK_SUCCESS) {
                throw std::runtime_error("failed to set up debug messenger!");
            }
        }

        /// <summary>
        /// �쐬����
        /// </summary>
        /// <param name="instance"></param>
        /// <param name="pCreateInfo"></param>
        /// <param name="pAllocator"></param>
        /// <param name="pDebugMessenger"></param>
        /// <returns></returns>
        static VkResult CreateDebugUtilsMessengerEXT
        (
            const VkInstance& instance,
            const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
            const VkAllocationCallbacks* pAllocator,
            VkDebugUtilsMessengerEXT* pDebugMessenger
        ) {
            static const char* pName = "vkCreateDebugUtilsMessengerEXT";
            auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, pName);
            if (func != nullptr) {
                return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
            }
            else {
                return VK_ERROR_EXTENSION_NOT_PRESENT;
            }
        }

        /// <summary>
        /// �j������
        /// </summary>
        /// <param name="instance"></param>
        /// <param name="debugMessenger"></param>
        /// <param name="pAllocator"></param>
        static void DestroyDebugUtilsMessengerEXT
        (
            const VkInstance& instance,
            VkDebugUtilsMessengerEXT debugMessenger,
            const VkAllocationCallbacks* pAllocator
        ) {
            static const char* pName = "vkDestroyDebugUtilsMessengerEXT";
            auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, pName);
            if (func != nullptr) {
                func(instance, debugMessenger, pAllocator);
            }
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="createInfo">[Out] �f�o�b�O���b�Z���W���[�쐬���</param>
        static void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
            createInfo = {};
            createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
            // Vulkan��ValidationLayer�Ŏ󂯎�郁�b�Z�[�W�̎�ʂ�ݒ�
            // https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkDebugUtilsMessageSeverityFlagBitsEXT.html
            createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT    // �ڍׂȏ����󂯎��
                | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT    // ���[�j���O���󂯎��
                | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;     // �G���[���󂯎��

            // https://www.khronos.org/registry/vulkan/specs/1.1-extensions/man/html/VkDebugUtilsMessageTypeFlagBitsEXT.html
            createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT            // �J�e�S���C�Y�ł��Ȃ�����擾����
                | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT         // validation�Ɋւ�����
                | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;       // �p�t�H�[�}���X�Ɋւ�����

            createInfo.pfnUserCallback = debugCallback;
        }

        /// <summary>
        /// ValidationLayer���L��������Ă���ۂɌĂяo�����R�[���o�b�N�֐�
        /// </summary>
        /// <param name="messageSeverity"></param>
        /// <param name="messageType"></param>
        /// <param name="pCallbackData"></param>
        /// <param name="pUserData"></param>
        /// <returns></returns>
        static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback
        (
            VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
            VkDebugUtilsMessageTypeFlagsEXT messageType,
            const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
            void* pUserData
        ) {
            std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

            return VK_FALSE;
        }
    };
} // debug
} // vengine

#endif