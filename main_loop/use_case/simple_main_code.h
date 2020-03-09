#pragma once

#include "../main_loop/interface/imain_code.h"
#include "../vulkan/loader/iloader.h"

namespace vengine
{
    class VulkanGraphicsBackend;
	namespace rengine
	{
		class ILoader;
		class Model;
	}

	class Shader;
	class Texture;
    
    class SimpleMainCode final : public rengine::IMainCode
    {
    private:
        std::shared_ptr<rengine::ILoader> loader_;
        std::shared_ptr<rengine::Model> model_;
        std::shared_ptr<Shader> shader_;
        std::shared_ptr<Texture> texture_;
    public:
        SimpleMainCode(std::shared_ptr<rengine::ILoader> const loader);
        ~SimpleMainCode();

        void initialize() override;
        void update() override;
        void prepareDraw() override;
        void lateDraw() override;
    };
} // vengine

