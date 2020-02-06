#pragma once

namespace vengine
{
    /// <summary>
    /// Allocator
    /// </summary>
    class CustomAllocator
    {
    private:
        std::unique_ptr<VkAllocationCallbacks> allocator_;

    public:
        CustomAllocator();
        ~CustomAllocator();


        //-------------------------------------
        // operatorŒQ
        inline operator VkAllocationCallbacks*() const {
            return allocator_.get();
        }
        inline operator const VkAllocationCallbacks*() const {
            return allocator_.get();
        }
    };
} // vengine