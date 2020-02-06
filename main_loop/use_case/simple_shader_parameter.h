#pragma once

#include "ishader_parameter.h"

namespace vengine
{
    /// <summary>
    /// シンプル(標準的な)なシェーダーパラメータ
    /// 位置、色、uvを持つ
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

