
// Vulkanを使用する
#define USE_VULKAN_

#ifdef USE_VULKAN_
#include "main_code/use_case/vulkan_sample_loop01.h"
#endif
#include  "imain_loop.h"

int main() {
    rengine::IMainLoop* app = nullptr;
#ifdef USE_VULKAN_
    app = new vengine::VulkanSampleLoop01();
    //app = new vengine::VulkanSampleLoop02();
    //app = new vengine::VulkanSampleLoop03();
    // のような使い方想定
#endif

    try {
        app->initialize();
        app->run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
