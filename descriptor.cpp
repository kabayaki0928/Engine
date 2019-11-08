#include "stdafx.h"
#include "descriptor.h"
#include "vulkan_graphics_backend.h"

namespace vengine
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    /// <param name="graphics_backend"></param>
    Descriptor::Descriptor(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend) {
        graphics_backend_ = graphics_backend;
        create();
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    Descriptor::~Descriptor() {
        auto device = graphics_backend_->getLogicalDevice();
        vkDestroyDescriptorPool(device, descriptor_pool_, nullptr);
    }

    /// <summary>
    /// VkDescriptorSetLayout作成処理
    /// </summary>
    void Descriptor::create() {
        Descriptor::createDescriptorSetLayout(graphics_backend_, descriptor_set_layout_);
        Descriptor::createDescriptorPool(graphics_backend_, graphics_backend_->getVulkanSwapchain().count(), descriptor_pool_);
    }

    /// <summary>
    /// VkDescriptorSetLayout作成処理
    /// </summary>
    /// <param name="graphics_backend"></param>
    /// <param name="out_descriptor"></param>
    void Descriptor::createDescriptorSetLayout
    (
        std::shared_ptr<VulkanGraphicsBackend> const graphics_backend,
        VkDescriptorSetLayout out_descriptor
    ) {
        VkDescriptorSetLayoutBinding uboLayoutBinding = {};
        uboLayoutBinding.binding = 0;
        uboLayoutBinding.descriptorCount = 1;
        uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        uboLayoutBinding.pImmutableSamplers = nullptr;
        uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

        VkDescriptorSetLayoutBinding samplerLayoutBinding = {};
        samplerLayoutBinding.binding = 1;
        samplerLayoutBinding.descriptorCount = 1;
        samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        samplerLayoutBinding.pImmutableSamplers = nullptr;
        samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

        std::array<VkDescriptorSetLayoutBinding, 2> bindings = { uboLayoutBinding, samplerLayoutBinding };
        VkDescriptorSetLayoutCreateInfo layoutInfo = {};
        layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
        layoutInfo.pBindings = bindings.data();

        VkResult result = vkCreateDescriptorSetLayout(graphics_backend->getLogicalDevice(), &layoutInfo, nullptr, &out_descriptor);
        if (result != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor set layout!");
        }
    }

    void Descriptor::createDescriptorPool
    (
        std::shared_ptr<VulkanGraphicsBackend> const graphics_backend,
        int descriptor_count,
        VkDescriptorPool out_descriptor_pool
    ) {
        std::array<VkDescriptorPoolSize, 2> pool_size = {};
        pool_size[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        pool_size[0].descriptorCount = static_cast<uint32_t>(descriptor_count);
        pool_size[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
        pool_size[1].descriptorCount = static_cast<uint32_t>(descriptor_count);

        VkDescriptorPoolCreateInfo pool_info = {};
        pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        pool_info.poolSizeCount = static_cast<uint32_t>(pool_size.size());
        pool_info.pPoolSizes = pool_size.data();
        pool_info.maxSets = static_cast<uint32_t>(descriptor_count);

        if (vkCreateDescriptorPool(graphics_backend->getLogicalDevice(), &pool_info, nullptr, &out_descriptor_pool) != VK_SUCCESS) {
            throw std::runtime_error("failed to create descriptor pool!");
        }
    }

    /// <summary>
    /// 
    /// </summary>
    void Descriptor::createDescriptorSet() {
        std::vector<VkDescriptorSetLayout> layouts(swapChainImages.size(), descriptorSetLayout);
        VkDescriptorSetAllocateInfo allocInfo = {};
        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
        allocInfo.descriptorPool = descriptorPool;
        allocInfo.descriptorSetCount = static_cast<uint32_t>(swapChainImages.size());
        allocInfo.pSetLayouts = layouts.data();

        descriptorSets.resize(swapChainImages.size());
        if (vkAllocateDescriptorSets(device, &allocInfo, descriptorSets.data()) != VK_SUCCESS) {
            throw std::runtime_error("failed to allocate descriptor sets!");
        }

        for (size_t i = 0; i < swapChainImages.size(); i++) {
            VkDescriptorBufferInfo bufferInfo = {};
            bufferInfo.buffer = uniformBuffers[i];
            bufferInfo.offset = 0;
            bufferInfo.range = sizeof(UniformBufferObject);

            VkDescriptorImageInfo imageInfo = {};
            imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            imageInfo.imageView = textureImageView;
            imageInfo.sampler = textureSampler;

            std::array<VkWriteDescriptorSet, 2> descriptorWrites = {};

            descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrites[0].dstSet = descriptorSets[i];
            descriptorWrites[0].dstBinding = 0;
            descriptorWrites[0].dstArrayElement = 0;
            descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            descriptorWrites[0].descriptorCount = 1;
            descriptorWrites[0].pBufferInfo = &bufferInfo;

            descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
            descriptorWrites[1].dstSet = descriptorSets[i];
            descriptorWrites[1].dstBinding = 1;
            descriptorWrites[1].dstArrayElement = 0;
            descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
            descriptorWrites[1].descriptorCount = 1;
            descriptorWrites[1].pImageInfo = &imageInfo;

            vkUpdateDescriptorSets(device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
        }
    }
} // vengine