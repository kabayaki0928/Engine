#include "stdafx.h"
#include "custom_allocator.h"

namespace vengine
{
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    CustomAllocator::CustomAllocator()
    : allocator_(std::make_unique<VkAllocationCallbacks>()) {
    }

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    CustomAllocator::~CustomAllocator() {
    }

} // vengine