#pragma once

#include "../vulkan/graphics_resource/shader/ishader_parameter.h"

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

        const VkVertexInputBindingDescription& getBindingDescription() const noexcept override { return binding_; }
        const VertexInputAttributeDescription& getAttributeDescription() const noexcept override { return attributes_; }
    };
} // vengine

