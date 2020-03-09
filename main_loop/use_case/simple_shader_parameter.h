#pragma once

#include "../vulkan/graphics_resource/shader/ishader_parameter.h"

namespace vengine
{
    /// <summary>
    /// �V���v��(�W���I��)�ȃV�F�[�_�[�p�����[�^
    /// �ʒu�A�F�Auv������
    /// </summary>
    class SimpleShaderParameter final : IShaderParameter
    {
    private:
        VkVertexInputBindingDescription binding_;
        VertexInputAttributeDescription attributes_;

    public:
        SimpleShaderParameter();

        const VkVertexInputBindingDescription& getBindingDescription() const noexcept override { return binding_; }
        const VertexInputAttributeDescription& getAttributeDescription() const noexcept override { return attributes_; }
    };
} // vengine

