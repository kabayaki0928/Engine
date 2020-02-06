#pragma once

#include "ishader_parameter.h"

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

        virtual const VkVertexInputBindingDescription& getBindingDescription() const noexcept { return binding_; }
        virtual const VertexInputAttributeDescription& getAttributeDescription() const noexcept { return attributes_; }
    };
} // vengine

