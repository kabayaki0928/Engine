#pragma once

namespace vengine
{
    typedef struct VertexInputAttributeDescription {
        VkVertexInputAttributeDescription* attribute_;
        uint32_t length_;
    } VertexInputAttributeDescription;

    /// <summary>
    /// Vulkanシェーダーのメモリレイアウトを設定する際に必要なパラメータ群があることを示すインターフェース
    /// </summary>
    class IShaderParameter
    {
    public:
        ~IShaderParameter() {  }

        virtual const VkVertexInputBindingDescription& getBindingDescription() const noexcept = 0;
        virtual const VertexInputAttributeDescription& getAttributeDescription() const noexcept = 0;
    };
} // vengine

