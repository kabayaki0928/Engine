#pragma once

namespace vengine
{
    typedef struct VertexInputAttributeDescription {
        VkVertexInputAttributeDescription* attribute_;
        uint32_t length_;
    } VertexInputAttributeDescription;

    /// <summary>
    /// Vulkan�V�F�[�_�[�̃��������C�A�E�g��ݒ肷��ۂɕK�v�ȃp�����[�^�Q�����邱�Ƃ������C���^�[�t�F�[�X
    /// </summary>
    class IShaderParameter
    {
    public:
        ~IShaderParameter() {  }

        virtual const VkVertexInputBindingDescription& getBindingDescription() const noexcept = 0;
        virtual const VertexInputAttributeDescription& getAttributeDescription() const noexcept = 0;
    };
} // vengine

