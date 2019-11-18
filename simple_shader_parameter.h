#pragma once

#include "ishader_parameter.h"

namespace vengine
{
    /// <summary>
    /// �V���v��(�W���I��)�ȃV�F�[�_�[�p�����[�^
    /// </summary>
    class SimpleShaderParameter final : IShaderParameter<3>
    {
    private:
        VkVertexInputBindingDescription binding_;
        std::array<VkVertexInputAttributeDescription, 3> attributes_;

    public:
        SimpleShaderParameter();
        ~SimpleShaderParameter();

        virtual const VkVertexInputBindingDescription& getBindingDescription() const noexcept { return binding_; }
        virtual const std::array<VkVertexInputAttributeDescription, 3> getAttributeDescription() const noexcept { return attributes_; }
    };
} // vengine

