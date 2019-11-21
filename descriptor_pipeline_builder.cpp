#include "descriptor_pipeline_builder.h"

#include "macro.h"
#include "vulkan_graphics_backend.h"

namespace vengine
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    DescriptorPipelineBuilder::DescriptorPipelineBuilder(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend)
    : graphics_backend_(graphics_backend){
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    DescriptorPipelineBuilder::~DescriptorPipelineBuilder() {
        graphics_backend_ = nullptr;
    }

    void DescriptorPipelineBuilder::buildSetLayoutBinding(const DescriptorLayout layouts[], VkDescriptorSetLayoutBinding bindings[]) {
        
        auto length = COUNTOF(layouts);
        std::vector<VkDescriptorSetLayoutBinding> tmp_bindings(length);
        for (int i = 0; i < length; ++i) {
            auto layout = layouts[i];

            VkDescriptorSetLayoutBinding binding = {
                i,
                layout.type_,
                layout.descriptor_count_,
                layout.shader_stage_flags_,
                nullptr
            };

            tmp_bindings.emplace_back(binding);
        }

        bindings = tmp_bindings.data();
    }
    
    void DescriptorPipelineBuilder::buildSetLayoutInfo(const VkDescriptorSetLayoutBinding bindings[], VkDescriptorSetLayoutCreateInfo out_create_info) {
        out_create_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        out_create_info.bindingCount = COUNTOF(bindings);
        out_create_info.pBindings = bindings;
    }

    void DescriptorPipelineBuilder::buildSetLayout(const VkDescriptorSetLayoutCreateInfo& layout_info, VkDescriptorSetLayout& out_set_layout) {
        VkResult result = vkCreateDescriptorSetLayout(graphics_backend_->getLogicalDevice(), &layout_info, nullptr, &out_set_layout);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor set layout!");
        }
    }

    void DescriptorPipelineBuilder::buildPoolInfo(const DescriptorLayout pool_sizes[], uint32_t max_sets, VkDescriptorPoolCreateInfo& out_create_info) {
        int length = COUNTOF(pool_sizes);
        std::vector<VkDescriptorPoolSize> temp_pool_sizes(length);
        for (int i = 0; i < length; ++i) {
            temp_pool_sizes[i] = {
                pool_sizes[i].type_,
                pool_sizes[i].descriptor_count_,
            };
        }
        
        out_create_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        out_create_info.poolSizeCount = length;
        out_create_info.pPoolSizes = temp_pool_sizes.data();
        out_create_info.maxSets = max_sets;
    }
    void DescriptorPipelineBuilder::buildPool(const VkDescriptorPoolCreateInfo& pool_info, VkDescriptorPool& out_descriptor_pool) {
        VkResult result = vkCreateDescriptorPool(graphics_backend_->getLogicalDevice(), &pool_info, nullptr, &out_descriptor_pool);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor pool!");
        }
    }

    void DescriptorPipelineBuilder::buildSets
    (
        const uint32_t layout_size,
        const VkDescriptorSetLayout& set_layout,
        const VkDescriptorPool& pool,
        std::vector<VkDescriptorSet>& sets
    ) {
        std::vector<VkDescriptorSetLayout> layouts(layout_size, set_layout);
        VkDescriptorSetAllocateInfo alloc_info = {};
        alloc_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        alloc_info.descriptorPool = pool;
        alloc_info.descriptorSetCount = layout_size;
        alloc_info.pSetLayouts = layouts.data();

        sets.resize(layout_size);
        VkResult result = vkAllocateDescriptorSets(graphics_backend_->getLogicalDevice(), &alloc_info, sets.data());
        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate descriptor sets!");
        }

    }

    void DescriptorPipelineBuilder::writeDescriptorSet(uint32_t max_sets, DescriptorSetList sets) {

        for (const auto& descriptor_sets : sets) {
            vkUpdateDescriptorSets
            (
                graphics_backend_->getLogicalDevice(),
                static_cast<uint32_t>(descriptor_sets.size()),
                descriptor_sets.data(),
                0,
                nullptr
            );
        }
    }

    VkWriteDescriptorSet DescriptorPipelineBuilder::createWriteUniformBufferInfo(uint32_t binding_idx, const VkBuffer& buffer, uint32_t range, const VkDescriptorSet& set) {

        VkDescriptorBufferInfo bufferInfo = {};
        bufferInfo.buffer = buffer;
        bufferInfo.offset = 0;
        bufferInfo.range = range;

        VkWriteDescriptorSet descriptor_write = {};
        descriptor_write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptor_write.dstSet = set;
        descriptor_write.dstBinding = binding_idx;
        descriptor_write.dstArrayElement = 0;
        descriptor_write.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptor_write.descriptorCount = 1;
        descriptor_write.pBufferInfo = &bufferInfo;

        return descriptor_write;
    }

    VkWriteDescriptorSet DescriptorPipelineBuilder::createWriteImageBufferInfo(uint32_t binding_idx, const VkImageView& image_view, const VkSampler& sampler, const VkDescriptorSet& set) {

        VkDescriptorImageInfo imageInfo = {};
        imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
        imageInfo.imageView = image_view;
        imageInfo.sampler = sampler;

        VkWriteDescriptorSet descriptor_write = {};
        descriptor_write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptor_write.dstSet = set;
        descriptor_write.dstBinding = binding_idx;
        descriptor_write.dstArrayElement = 0;
        descriptor_write.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        descriptor_write.descriptorCount = 1;
        descriptor_write.pImageInfo = &imageInfo;

        return descriptor_write;
    }

    void DescriptorPipelineBuilder::buildSimpleDescriptor
    (
        uint32_t swapchain_count,
        const std::vector<VkBuffer> uniform_buffer_objects,
        uint32_t range,
        const VkImageView& image_view, 
        const VkSampler& sampler
    ) {
        // 本来はこの構造体を外からもらう
        // uniform buffer object = mesh_renderer、ないしdrawable_buffer毎に必要なので
        // 一定量確保して使いまわす形式が望ましい
        DescriptorLayout layouts[2] = {
            {
                VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
                swapchain_count,
                VK_SHADER_STAGE_VERTEX_BIT,
            },
            {
                VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                swapchain_count,
                VK_SHADER_STAGE_FRAGMENT_BIT
            }
        };
        VkDescriptorSetLayoutBinding bindings[2];
        VkDescriptorSetLayoutCreateInfo set_layout_create_info;
        VkDescriptorSetLayout set_layout;
        VkDescriptorPoolCreateInfo pool_info;
        VkDescriptorPool pool;
        std::vector<VkDescriptorSet> sets;
        buildSetLayoutBinding(layouts, bindings);
        buildSetLayoutInfo(bindings, set_layout_create_info);
        buildSetLayout(set_layout_create_info, set_layout);

        buildPoolInfo(layouts, swapchain_count, pool_info);
        buildPool(pool_info, pool);
        buildSets(swapchain_count, set_layout, pool, sets);

        DescriptorSetList list(swapchain_count);
        uint32_t binding_idx = 0;
        for (auto i = 0; i < swapchain_count; ++i) {
            auto descriptor_sets = list[i];
            descriptor_sets.resize(COUNTOF(layouts));
            
            binding_idx = 0;
            for (const auto& layout : layouts) {
                switch (layout.type_) {
                case VkDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER:
                    descriptor_sets.emplace_back(
                        createWriteUniformBufferInfo(
                            binding_idx,
                            uniform_buffer_objects[i],
                            range,
                            sets[binding_idx]
                        )
                    );
                    break;
                case VkDescriptorType::VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER:
                    descriptor_sets.emplace_back(
                        createWriteImageBufferInfo(
                            binding_idx,
                            image_view,
                            sampler,
                            sets[binding_idx]
                        )
                    );
                    break;
                default:
                    assert("not defined descriptor type. %s", layout.type_);
                    break;
                }
                ++binding_idx;
            }
        }

        writeDescriptorSet(swapchain_count, list);
    }
} // vengine
