#pragma once

#include "irender_pipeline.h"

namespace vengine
{
    class VulkanGraphicsBackend;

    class VulkanRenderPipeline final : public rengine::IRenderPipeline
    {
    private:
        const int MAX_FRAMES_IN_FLIGHT = 2;
        std::shared_ptr<VulkanGraphicsBackend> graphics_backend_;

        VkPipelineLayout pipelineLayout;
        VkPipeline graphicsPipeline;
        VkQueue graphics_queue_;
        VkQueue present_queue_;
        std::vector<VkFence> in_flight_fences_;
        std::vector<VkSemaphore> image_available_semaphores_;
        std::vector<VkSemaphore> render_finished_semaphores_;
        size_t current_frame_ = 0;

        std::vector<VkBuffer> uniform_buffers_;
        std::vector<VkDeviceMemory> uniform_buffers_memory_;

        VkCommandPool command_pool_;
        std::vector<VkCommandBuffer> command_buffers_;

    private:
        void createGraphicsPipeline();
        void updateUniformBuffer(uint32_t current_image);
        void createFrameBuffers();
        void createCommandPool();
        void createColorResources();
        void createDepthResources();
        void createSyncObject();

    public:
        VulkanRenderPipeline(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend);
        ~VulkanRenderPipeline();

        void initialize() override;
        void draw() override;
    };
} // rengine
