#pragma once

namespace vengine
{
    class Shader;
    struct ShaderModule;
    class VulkanGraphicsBackend;

    class ShaderLoader final
    {
    private:
        std::shared_ptr<VulkanGraphicsBackend> graphics_backend_;
    public:
        ShaderLoader(std::shared_ptr<VulkanGraphicsBackend> const graphics_backend);
        ~ShaderLoader();
        void loadVertexShader(const char* file_name, std::function<void(std::shared_ptr<VertexShaderModule>)> callback);
        void loadFragmentShader(const char* file_name, std::function<void(std::shared_ptr<FragmentShaderModule>)> callback);
    private:
        static std::vector<char> loadFile(const char* file_name);
        static void createShaderModule
        (
            std::shared_ptr<VulkanGraphicsBackend> const graphics_backend,
            const std::vector<char>& code,
            ShaderModule& out_shader_module
        );
        static void createShaderStage
        (
            const char* name,
            const ShaderStageType stage_type,
            ShaderModule& out_shader_module
        );
        static VkShaderStageFlagBits toShaderStageFlagBits(const ShaderStageType stage_type);
    };
} // vengine