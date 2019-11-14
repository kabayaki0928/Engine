#pragma once

#include <functional>

namespace rengine
{
    /// <summary>
    /// 読み込み機能があることを示すインターフェース
    /// Texture / Model / Material等のリソース単位ではなくもう一層外苑のモノ
    /// 詳しくはSimpleLoader参照のこと
    /// </summary>
    class ILoader
    {
    public:
        ~ILoader() {}

        template<typename T>
        void load(const char* file_name, std::function<void(T)> callback) = 0;
    };
} // rengine