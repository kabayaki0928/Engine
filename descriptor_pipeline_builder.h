#pragma once

namespace vengine
{
    class VulkanGraphicsBackend;

    typedef struct DescriptorLayout {
        VkDescriptorType    type_;
        uint32_t            descriptor_count_;
        VkShaderStageFlags  shader_stage_flags_;
    };

    using DescriptorSetList = std::vector<std::vector<VkWriteDescriptorSet>>;

    class DescriptorPipelineBuilder final
    {
    private:
        std::shared_ptr<VulkanGraphicsBackend> graphics_backend_;
    public:
        DescriptorPipelineBuilder(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend);
        ~DescriptorPipelineBuilder();

        void buildSetLayoutBinding(const DescriptorLayout layouts[], VkDescriptorSetLayoutBinding bindings[]);
        void buildSetLayoutInfo(const VkDescriptorSetLayoutBinding bindings[], VkDescriptorSetLayoutCreateInfo out_create_info);
        void buildSetLayout(const VkDescriptorSetLayoutCreateInfo& layout_info, VkDescriptorSetLayout& out_set_layout);
        void buildPoolInfo(const DescriptorLayout pool_sizes[], uint32_t max_sets, VkDescriptorPoolCreateInfo& out_create_info);
        void buildPool(const VkDescriptorPoolCreateInfo& pool_info, VkDescriptorPool& out_descriptor_pool);
        void buildSets(const uint32_t layout_size, const VkDescriptorSetLayout& set_layout, const VkDescriptorPool& pool, std::vector<VkDescriptorSet>& sets);

        void writeDescriptorSet(uint32_t max_sets, const DescriptorSetList sets);

        VkWriteDescriptorSet createWriteUniformBufferInfo(uint32_t binding_idx, const VkBuffer& buffer, uint32_t range, const VkDescriptorSet& set);
        VkWriteDescriptorSet createWriteImageBufferInfo(uint32_t binding_idx, const VkImageView& image_view, const VkSampler& sampler, const VkDescriptorSet& set);

        void buildSimpleDescriptor(
            uint32_t swapchain_count,
            const std::vector<VkBuffer> uniform_buffer_objects,
            uint32_t range,
            const VkImageView& image_view,
            const VkSampler& sampler
        );
    };
} // vengine