#pragma once

namespace vengine
{
    class PipelineLayout
    {
    private:
        VkPipelineLayout pipeline_layout_;
    public:
        PipelineLayout();
        ~PipelineLayout();

        void create();
        static void create(VkPipelineLayout& out_pipeline_layout);
    };
} // vengine

