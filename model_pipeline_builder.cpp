#include "model_pipeline_builder.h"

#include "uniform_buffer.h"

namespace vengine
{
    ModelPipelineBuilder::ModelPipelineBuilder() {
    }

    ModelPipelineBuilder::~ModelPipelineBuilder() {
    }

    void ModelPipelineBuilder::createUniformBuffers() {
        VkDeviceSize bufferSize = sizeof(UniformBufferObject);

        uniformBuffers.resize(swapChainImages.size());
        uniformBuffersMemory.resize(swapChainImages.size());

        for (size_t i = 0; i < swapChainImages.size(); i++) {
            createBuffer
            (
                bufferSize,
                VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
                | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
                uniformBuffers[i],
                uniformBuffersMemory[i]
            );
        }
    }
} // vengine