#pragma once

namespace vengine
{
    /// <summary>
    /// Vulkanシェーダーのメモリレイアウトを設定する際に必要なパラメータ群があることを示すインターフェース
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

