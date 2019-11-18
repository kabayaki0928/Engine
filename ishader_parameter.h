#pragma once

namespace vengine
{
    /// <summary>
    /// Vulkan�V�F�[�_�[�̃��������C�A�E�g��ݒ肷��ۂɕK�v�ȃp�����[�^�Q�����邱�Ƃ������C���^�[�t�F�[�X
    /// </summary>
    template<int N>
    class IShaderParameter
    {
    public:
        ~IShaderParameter() {  }

        virtual const VkVertexInputBindingDescription& getBindingDescription() const noexcept = 0;
        virtual const std::array<VkVertexInputAttributeDescription, N> getAttributeDescription() const noexcept = 0;
    };
} // vengine

