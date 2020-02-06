#include "stdafx.h"
#include "custom_allocator.h"

namespace vengine
{
    /// <summary>
    /// コンストラクタ
    /// </summary>
    CustomAllocator::CustomAllocator()
    : allocator_(std::make_unique<VkAllocationCallbacks>()) {
    }

    /// <summary>
    /// デストラクタ
    /// </summary>
    CustomAllocator::~CustomAllocator() {
    }

} // vengine