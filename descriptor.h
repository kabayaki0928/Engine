#pragma once

namespace vengine
{
    class VulkanGraphicsBackend;

    class Descriptor final
    {
    private:
        std::shared_ptr<VulkanGraphicsBackend> graphics_backend_;
        VkDescriptorSetLayout descriptor_set_layout_;
        VkDescriptorPool descriptor_pool_;
    public:
        Descriptor(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend);
        ~Descriptor();

        void create();
        static void createDescriptorSetLayout
        (
            std::shared_ptr<VulkanGraphicsBackend> const graphics_backend,
            VkDescriptorSetLayout out_descriptor
        );
        static void createDescriptorPool
        (
            std::shared_ptr<VulkanGraphicsBackend> const graphics_backend,
            int descriptor_count,
            VkDescriptorPool out_descriptor_pool
        );
    };
} // vengine
