#pragma once

namespace vengine
{
    class ModelPipelineBuilder
    {
    public:
        ModelPipelineBuilder();
        ~ModelPipelineBuilder();

        void createModelInfo
        (
            VkPipelineShaderStageCreateInfo[] & out_shader_stage,
        );
        void createUniformBuffers();
    };
} // vengine