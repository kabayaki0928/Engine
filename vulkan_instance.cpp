#include "vulkan_instance.h"

#include "vulkan_graphics_backend.h"

#include "debug_utils.h"
#include "VulkanUtils.h"
#include "user_define.h"


namespace vengine
{
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="application_name">�A�v���P�[�V������</param>
    /// <param name="engine_name">�G���W����</param>
    VulkanInstance::VulkanInstance(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend, const char* application_name, const char* engine_name) {
        graphics_backend_ = graphics_backend;
        create(application_name, engine_name);
    }

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    VulkanInstance::~VulkanInstance() {
        graphics_backend_.reset();
        // TODO instance_�j������
    }
    
    /// <summary>
    /// VkInstance�쐬����
    /// </summary>
    /// <param name="application_name">�A�v���P�[�V������</param>
    /// <param name="engine_name">�G���W����</param>
    void VulkanInstance::create(const char* application_name, const char* engine_name) {
        VulkanInstance::create(&instance_, application_name, engine_name);
    }

    /// <summary>
    /// VkInstance�쐬����
    /// </summary>
    /// <param name="instance">Vulkan�̎���</param>
    /// <param name="application_name">�A�v���P�[�V������</param>
    /// <param name="engine_name">�G���W����</param>
    void VulkanInstance::create(VkInstance* instance, const char* application_name, const char* engine_name) {
        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = application_name;
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = engine_name;
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        auto extensions = VulkanUtils::getRequiredExtensions(user_define::enableValidationLayers);
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo;
        if (user_define::enableValidationLayers) {
            createInfo.enabledLayerCount = static_cast<uint32_t>(user_define::validationLayers.size());
            createInfo.ppEnabledLayerNames = user_define::validationLayers.data();

            debug::Messanger::populateDebugMessengerCreateInfo(debugCreateInfo);
            createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debugCreateInfo;
        }
        else {
            createInfo.enabledLayerCount = 0;

            createInfo.pNext = nullptr;
        }

        if (vkCreateInstance(&createInfo, nullptr, instance) != VK_SUCCESS) {
            throw std::runtime_error("failed to create instance!");
        }
    }
} // vengine