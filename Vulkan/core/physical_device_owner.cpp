#include "physical_device_owner.h"

#include "igraphics_backend.h"
#include "queue_family.h"

namespace vengine
{
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="graphics_backend"></param>
    PhysicalDeviceOwner::PhysicalDeviceOwner(std::shared_ptr<VulkanGraphicsBackend> const vulkan_graphics_backend) {
        graphics_backend_ = vulkan_graphics_backend;
    }

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    PhysicalDeviceOwner::~PhysicalDeviceOwner() {
        physical_devices_.clear();
        current_physical_device_.reset();
        current_physical_device_ = nullptr;
    }

    /// <summary>
    /// ����������
    /// </summary>
    /// <returns></returns>
    void PhysicalDeviceOwner::initialize() {
        // �Q�[������GPU�������茸�����肷�邱�Ƃ͂Ȃ�(�n�Y�c)���̂�
        // ��U�����擾�ł���悤��
        // �܂��A���������ۂ�Initialize�֐����Ăяo�����Ƃōēx�擾���Ȃ�����悤�ɂ��Ă���
        usedIndex = 0;
        enumeratePhysicalDevice();
    }

    /// <summary>
    /// ���ݎ擾�\�ȕ����f�o�C�X�̗񋓏���
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
            // �����f�o�C�X�̏���������
            initialize();
        }
        else {
            ++usedIndex;
        }
        // TODO ������̏����͗v����
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
            // �����f�o�C�X�̏���������
            initialize();
        }
        return current_physical_device_;
    }
} // vengine