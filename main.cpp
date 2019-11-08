//
////#include "stdafx.h"
//
////#define GLFW_INCLUDE_VULKAN
////#define STB_IMAGE_IMPLEMENTATION
////#define GLM_FORCE_RADIANS
////#define GLM_FORCE_DEPTH_ZERO_TO_ONE
////#define GLM_ENABLE_EXPERIMENTAL
////#define TINYOBJLOADER_IMPLEMENTATION
////
////#include <tiny_obj_loader.h>
////#include <stb_image.h>
////
////#include <GLFW/glfw3.h>
////#include <glm/glm.hpp>
////#include <glm/gtc/matrix_transform.hpp>
////#include <glm/gtx/hash.hpp>
////#include <chrono>
////
////#include <iostream>
////#include <stdexcept>
////#include <algorithm>
////#include <vector>
////#include <cstring>
////#include <cstdlib>
////#include <optional>
////#include <set>
////#include <array>
//
////#include "binaryLoader.h"
////#include "CommandBuffer.h"
////#include "DebugUtils.h"
////#include "Vertex.h"
////#include "VulkanInstance.h"
////#include "VulkanUtils.h"
////#include "Surface.h"
////#include "UserDefine.h"
////#include "Window.h"
//
////const std::string MODEL_PATH = "models/chalet.obj";
////const std::string TEXTURE_PATH = "textures/chalet.jpg";
////
////#ifdef NDEBUG
////const bool enableValidationLayers = false;
////#else
////const bool enableValidationLayers = true;
////#endif
////
////class HelloTriangleApplication {
////public:
////
////    void run() {
////        initWindow();
////        initVulkan();
////        mainLoop();
////        cleanup();
////    }
////
////private:
////    Window<HelloTriangleApplication>* pWindow;
////    VulkanInstance* pInstance;
////    Debug::Messanger* pDebugMessanger;
////    Surface* pSurface;
////    PhysicalDeviceOwner* pPhysicalDeviceOwner;
////    PhysicalDevice* pPhysicalDevice;
////    LogicalDevice* pLogicalDevice;
////    SwapChain* pSwapChain;
////
////    //VkInstance instance;
////
////    VkPhysicalDevice pPhysicalDevice = VK_NULL_HANDLE;
////    VkDevice device;
////
////    VkQueue graphicsQueue;
////    VkQueue presentQueue;
////
////    VkShaderModule vertShaderModule;
////    VkShaderModule fragShaderModule;
////    VkDescriptorSetLayout descriptorSetLayout;
////    VkPipelineLayout pipelineLayout;
////    VkRenderPass renderPass;
////    VkPipeline graphicsPipeline;
////    std::vector<VkFramebuffer> swapChainFramebuffers;
////    VkCommandPool commandPool;
////    std::vector<VkCommandBuffer> commandBuffers;
////    std::vector<VkSemaphore> imageAvailableSemaphores;
////    std::vector<VkSemaphore> renderFinishedSemaphores;
////    std::vector<VkFence> inFlightFences;
////    const int MAX_FAMES_IN_FLIGHT = 2;
////    bool framebufferResized = false;
////    size_t currentFrame = 0;
////    VkBuffer vertexBuffer;
////    VkDeviceMemory vertexBufferMemory;
////    VkBuffer indexBuffer;
////    VkDeviceMemory indexBufferMemory;
////    std::vector<VkBuffer> uniformBuffers;
////    std::vector<VkDeviceMemory> uniformBuffersMemory;
////    VkDescriptorPool descriptorPool;
////    std::vector<VkDescriptorSet> descriptorSets;
////
////    uint32_t mipLevels;
////    VkImage textureImage;
////    VkDeviceMemory textureImageMemory;
////    VkImageView textureImageView;
////    VkSampler textureSampler;
////
////    VkImage depthImage;
////    VkDeviceMemory depthImageMemory;
////    VkImageView depthImageView;
////    VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;
////
////    VkImage colorImage;
////    VkDeviceMemory colorImageMemory;
////    VkImageView colorImageView;
////
////    void initWindow() {
////        pWindow = new Window("Vulkan", UserDefine::WIDTH, UserDefine::HEIGHT);
////    }
////
////    void initVulkan() {
////        createInstance();
////        setupDebugMessenger();
////        createSurface();
////        createPhysicalDevice();
////        createLogicalDevice();
////        createSwapChain();
////        createMisc();
////
////        createSwapChainImageViews();
////        createRenderPass();
////        createDescriptorSetLayout();
////        createGraphicsPipeline();
////        createCommandPool();
////        createDepthResources();
////        createFramebuffers();
////        createTextureImage();
////        createTextureImageView();
////        createTextureSampler();
////        loadModel();
////        //createVertexBuffer();
////        //createIndexBuffer();
////        createUniformBuffers();
////        createDescriptorPool();
////        createDescriptorSets();
////        createCommandBuffers();
////        createSyncObjects();
////    }
////
////    void recreateSwapChain() {
////        pWindow->recreateSwapChain();
////
////        vkDeviceWaitIdle(device);
////
////        cleanupSwapChain();
////
////        createSwapChain();
////        createSwapChainImageViews();
////        createRenderPass();
////        createGraphicsPipeline();
////        createColorResources();
////        createDepthResources();
////        createFramebuffers();
////        createUniformBuffers();
////        createDescriptorPool();
////        createDescriptorSets();
////        createCommandBuffers();
////    }
////
////    void mainLoop() {
////        while (!pWindow->IsShouldClose()) {
////            glfwPollEvents();
////            drawFrame();
////        }
////        vkDeviceWaitIdle(device);
////    }
////
////    void cleanupSwapChain() {
////        vkDestroyImageView(device, colorImageView, nullptr);
////        vkDestroyImage(device, colorImage, nullptr);
////        vkFreeMemory(device, colorImageMemory, nullptr);
////
////        for (size_t i = 0; i < swapChainFramebuffers.size(); ++i) {
////            vkDestroyFramebuffer(device, swapChainFramebuffers[i], nullptr);
////        }
////        vkFreeCommandBuffers(device, commandPool, static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());
////
////        vkDestroyPipeline(device, graphicsPipeline, nullptr);
////        vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
////        vkDestroyRenderPass(device, renderPass, nullptr);
////
////        //for (size_t i = 0; i < swapChainImageViews.size(); ++i) {
////        //    vkDestroyImageView(device, swapChainImageViews[i], nullptr);
////        //}
////        //vkDestroySwapchainKHR(device, swapChain, nullptr);
////        
////        for (size_t i = 0; i < uniformBuffers.size(); ++i) {
////            vkDestroyBuffer(device, uniformBuffers[i], nullptr);
////            vkFreeMemory(device, uniformBuffersMemory[i], nullptr);
////        }
////        vkDestroyDescriptorPool(device, descriptorPool, nullptr);
////    }
////
////    void cleanup() {
////        cleanupSwapChain();
////
////        vkDestroyImage(device, depthImage, nullptr);
////        vkDestroyImageView(device, depthImageView, nullptr);
////        vkFreeMemory(device, depthImageMemory, nullptr);
////
////        vkDestroySampler(device, textureSampler, nullptr);
////        vkDestroyImageView(device, textureImageView, nullptr);
////
////        vkDestroyImage(device, textureImage, nullptr);
////        vkFreeMemory(device, textureImageMemory, nullptr);
////
////        vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);
////
////        vkDestroyBuffer(device, vertexBuffer, nullptr);
////        vkFreeMemory(device, vertexBufferMemory, nullptr);
////
////        vkDestroyBuffer(device, indexBuffer, nullptr);
////        vkFreeMemory(device, indexBufferMemory, nullptr);
////
////        for (size_t i = 0; i < MAX_FAMES_IN_FLIGHT; ++i) {
////            vkDestroySemaphore(device, renderFinishedSemaphores[i], nullptr);
////            vkDestroySemaphore(device, imageAvailableSemaphores[i], nullptr);
////        }
////        vkDestroyCommandPool(device, commandPool, nullptr);
////
////        vkDestroyDevice(device, nullptr);
////        
////        DisposeContainer container = 
////        {
////            *pInstance,
////            *pLogicalDevice,
////            nullptr
////        };
////
////        pDebugMessanger->dispose(container, enableValidationLayers);
////        pSurface->dispose(container);
////        vkDestroyInstance(*pInstance, nullptr);
////
////        pWindow->dispose();
////
////        glfwTerminate();
////    }
////
////    void loadModel() {
////
////    }
////
////    void createInstance() {
////        if (enableValidationLayers && !checkValidationLayerSupport()) {
////            throw std::runtime_error("validation layers requested, but not available!");
////        }
////
////        pInstance = new VulkanInstance("triangle", "no engine");
////    }
////
////    void setupDebugMessenger() {
////        pDebugMessanger = new Debug::Messanger();
////    }
////
////    void createSurface() {
////        CreateContainer container = 
////        {
////            *pWindow,
////            *pInstance,
////            nullptr,
////            nullptr,
////            nullptr
////        };
////        pSurface = new Surface();
////        pSurface->create(*pInstance, *pWindow);
////    }
////
////    void createPhysicalDevice() {
////        CreateContainer container =
////        {
////            *pWindow,
////            *pInstance,
////            nullptr,
////            nullptr,
////            *pSurface
////        };
////        pPhysicalDeviceOwner = new PhysicalDeviceOwner();
////        pPhysicalDeviceOwner->Initialize(container);
////        pPhysicalDeviceOwner->takeCurrentDevice(container, *pPhysicalDevice);
////    }
////
////    void createLogicalDevice() {
////        CreateContainer container =
////        {
////            *pWindow,
////            *pInstance,
////            *pPhysicalDevice,
////            nullptr,
////            *pSurface
////        };
////        pLogicalDevice = new LogicalDevice();
////        pLogicalDevice->create(container);
////    }
////
////    void createSwapChain() {
////        CreateContainer container =
////        {
////            *pWindow,
////            *pInstance,
////            *pPhysicalDevice,
////            *pLogicalDevice,
////            *pSurface
////        };
////        pSwapChain = new SwapChain();
////        pSwapChain->create(container, UserDefine::WIDTH, UserDefine::HEIGHT);
////    }
////
////    void createSwapChainImageViews() {
////
////    }
////
////    // �N���X������قǂł͂Ȃ����̂̍����Ă��������Ȃ��̂Ŋ֐����番�����Ă��������̂̏W����
////    // TODO ���������㐮������
////    void createMisc() {
////        CreateContainer container =
////        {
////            *pWindow,
////            *pInstance,
////            *pPhysicalDevice,
////            *pLogicalDevice,
////            *pSurface
////        };
////        auto indices = QueueFamily::findQueueFamilies(container);
////
////        vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
////        vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
////
////        VkPhysicalDeviceProperties physicalDeviceProperties;
////        vkGetPhysicalDeviceProperties(*pPhysicalDevice, &physicalDeviceProperties);
////
////        VkSampleCountFlags counts = std::min(physicalDeviceProperties.limits.framebufferColorSampleCounts, physicalDeviceProperties.limits.framebufferDepthSampleCounts);
////
////        msaaSamples = VK_SAMPLE_COUNT_1_BIT;
////
////        if (counts & VK_SAMPLE_COUNT_64_BIT) { msaaSamples = VK_SAMPLE_COUNT_64_BIT; }
////        if (counts & VK_SAMPLE_COUNT_32_BIT) { msaaSamples = VK_SAMPLE_COUNT_32_BIT; }
////        if (counts & VK_SAMPLE_COUNT_16_BIT) { msaaSamples = VK_SAMPLE_COUNT_16_BIT; }
////        if (counts & VK_SAMPLE_COUNT_8_BIT)  { msaaSamples = VK_SAMPLE_COUNT_8_BIT; }
////        if (counts & VK_SAMPLE_COUNT_4_BIT)  { msaaSamples = VK_SAMPLE_COUNT_4_BIT; }
////        if (counts & VK_SAMPLE_COUNT_2_BIT)  { msaaSamples = VK_SAMPLE_COUNT_2_BIT; }
////    }
////
////
////    void createRenderPass() {
////        VkAttachmentDescription colorAttachment = {};
////        colorAttachment.format = swapChainImageFormat;
////        colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
////        colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
////        colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
////        colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
////        colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
////        colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
////        colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
////
////        VkAttachmentDescription depthAttachment = {};
////        depthAttachment.format = findDepthFormat();
////        depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
////        depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
////        depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
////        depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
////        depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
////        depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
////        depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
////
////        VkAttachmentReference colorAttachmentRef = {};
////        colorAttachmentRef.attachment = 0;
////        colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
////
////        VkAttachmentReference depthAttachmentRef = {};
////        depthAttachmentRef.attachment = 1;
////        depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
////
////        VkSubpassDescription subpass = {};
////        subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
////        subpass.colorAttachmentCount = 1;
////        subpass.pColorAttachments = &colorAttachmentRef;
////        subpass.pDepthStencilAttachment = &depthAttachmentRef;
////
////        VkSubpassDependency dependency = {};
////        dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
////        dependency.dstSubpass = 0;
////        dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
////        dependency.srcAccessMask = 0;
////        dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
////        dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
////
////        std::array<VkAttachmentDescription, 2> attachments = { colorAttachment, depthAttachment };
////        VkRenderPassCreateInfo renderPassInfo = {};
////        renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
////        renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
////        renderPassInfo.pAttachments = attachments.data();
////        renderPassInfo.subpassCount = 1;
////        renderPassInfo.pSubpasses = &subpass;
////        renderPassInfo.dependencyCount = 1;
////        renderPassInfo.pDependencies = &dependency;
////
////        if (vkCreateRenderPass(device, &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS) {
////            throw std::runtime_error("failed to create render pass!");
////        }
////    }
////
////    void createDescriptorSetLayout() {
////        VkDescriptorSetLayoutBinding uboLayoutBinding = {};
////        uboLayoutBinding.binding = 0;
////        uboLayoutBinding.descriptorCount = 1;
////        uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
////        uboLayoutBinding.pImmutableSamplers = nullptr;
////        uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
////
////        VkDescriptorSetLayoutBinding samplerLayoutBinding = {};
////        samplerLayoutBinding.binding = 1;
////        samplerLayoutBinding.descriptorCount = 1;
////        samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
////        samplerLayoutBinding.pImmutableSamplers = nullptr;
////        samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
////
////        std::array<VkDescriptorSetLayoutBinding, 2> bindings = { uboLayoutBinding, samplerLayoutBinding };
////        VkDescriptorSetLayoutCreateInfo layoutInfo = {};
////        layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
////        layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
////        layoutInfo.pBindings = bindings.data();
////
////        if (vkCreateDescriptorSetLayout(device, &layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS) {
////            throw std::runtime_error("failed to create descriptor set layout!");
////        }
////    }
////
////    void createGraphicsPipeline() {
////        //auto vert = BinaryLoader::load(L"shaders/vert.spv");
////        //auto frag = BinaryLoader::load(L"shaders/frag.spv");
////
////        auto vert = BinaryLoader::readFile("shaders/vert.spv");
////        auto frag = BinaryLoader::readFile("shaders/frag.spv");
////
////        vertShaderModule = createShaderModule(vert.data(), vert.size());
////        fragShaderModule = createShaderModule(frag.data(), frag.size());
////
////        // �V�F�[�_�[���W���[�����̃X�e�[�W���쐬
////        // stage = �i�K�H
////        VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
////        vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
////        vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
////        vertShaderStageInfo.module = vertShaderModule;
////        vertShaderStageInfo.pName = "main";
////
////        VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
////        fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
////        fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
////        fragShaderStageInfo.module = fragShaderModule;
////        fragShaderStageInfo.pName = "main";
////
////        VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };
////
////        // ���_����
////        VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
////        vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
////        vertexInputInfo.vertexBindingDescriptionCount = 0;
////        vertexInputInfo.pVertexBindingDescriptions = nullptr; // �C��
////        vertexInputInfo.vertexAttributeDescriptionCount = 0;
////        vertexInputInfo.pVertexAttributeDescriptions = nullptr; // �C��
////
////        // ���_�o�b�t�@�̐ݒ�
////        auto bindingDescription = Vertex::getBindingDescription();
////        auto attributeDescriptions = Vertex::getAttributeDescriptions();
////        vertexInputInfo.vertexBindingDescriptionCount = 1;
////        vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
////        vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
////        vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();
////
////        // �O�p�`�̍\��
////        VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo = {};
////        inputAssemblyInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
////        inputAssemblyInfo.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
////        inputAssemblyInfo.primitiveRestartEnable = VK_FALSE;
////
////        // Viewport
////        VkViewport viewport = {};
////        viewport.x = 0.0f;
////        viewport.y = 0.0f;
////        viewport.width = (float)swapChainExtent.width;
////        viewport.height = (float)swapChainExtent.height;
////        viewport.minDepth = 0.0f;
////        viewport.maxDepth = 1.0f;
////
////        // Viewport�ɑ΂���؂�o���ݒ�
////        VkRect2D scissor = {};
////        scissor.offset = { 0, 0 };
////        scissor.extent = swapChainExtent;
////
////        // Viewport�ƃV�U�[(�؂�o���ݒ��ݒ肷��
////        VkPipelineViewportStateCreateInfo viewportState = {};
////        viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
////        viewportState.viewportCount = 1;
////        viewportState.pViewports = &viewport;
////        viewportState.scissorCount = 1;
////        viewportState.pScissors = &scissor;
////        // ���X�^���C�U
////        VkPipelineRasterizationStateCreateInfo rasterizer = {};
////        rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
////        rasterizer.depthClampEnable = VK_FALSE;
////        rasterizer.rasterizerDiscardEnable = VK_FALSE;
////        rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
////        rasterizer.lineWidth = 1.0f;
////        rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;	// �p�X�P�ʂŎw��ł��鐫���̂��̂Ȃ̂ł́H
////        rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
////        rasterizer.depthBiasEnable = VK_FALSE;
////
////        // �}���`�T���v���ݒ�
////        VkPipelineMultisampleStateCreateInfo multisampling = {};
////        multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
////        multisampling.sampleShadingEnable = VK_FALSE;
////        multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
////
////        VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
////        colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT
////            | VK_COLOR_COMPONENT_G_BIT
////            | VK_COLOR_COMPONENT_B_BIT
////            | VK_COLOR_COMPONENT_A_BIT;
////        colorBlendAttachment.blendEnable = VK_FALSE;
////
////        VkPipelineColorBlendStateCreateInfo colorBlending = {};
////        colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
////        colorBlending.logicOpEnable = VK_FALSE;
////        colorBlending.logicOp = VK_LOGIC_OP_COPY;
////        colorBlending.attachmentCount = 1;
////        colorBlending.pAttachments = &colorBlendAttachment;
////        colorBlending.blendConstants[0] = 0.0f;
////        colorBlending.blendConstants[1] = 0.0f;
////        colorBlending.blendConstants[2] = 0.0f;
////        colorBlending.blendConstants[3] = 0.0f;
////
////        //VkDynamicState dynamicStates[] = {
////        //    VK_DYNAMIC_STATE_VIEWPORT,
////        //    VK_DYNAMIC_STATE_LINE_WIDTH
////        //};
////        //
////        //VkPipelineDynamicStateCreateInfo dynamicState = {};
////        //dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
////        //dynamicState.dynamicStateCount = 2;
////        //dynamicState.pDynamicStates = dynamicStates;
////
////        VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
////        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
////        pipelineLayoutInfo.setLayoutCount = 1;
////        pipelineLayoutInfo.pSetLayouts = &descriptorSetLayout;
////        pipelineLayoutInfo.pushConstantRangeCount = 0;
////        pipelineLayoutInfo.pPushConstantRanges = nullptr;
////
////        if (vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
////            throw std::runtime_error("failed to create pipeline layout!");
////        }
////
////        VkPipelineDepthStencilStateCreateInfo depthStencil = {};
////        depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
////        depthStencil.depthTestEnable = VK_TRUE;
////        depthStencil.depthWriteEnable = VK_TRUE;
////        depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
////        depthStencil.depthBoundsTestEnable = VK_FALSE;
////        depthStencil.minDepthBounds = 0.0f;
////        depthStencil.maxDepthBounds = 1.0f;
////        depthStencil.stencilTestEnable = VK_FALSE;
////        depthStencil.front = {};
////        depthStencil.back = {};
////
////        VkGraphicsPipelineCreateInfo pipelineInfo = {};
////        pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
////        pipelineInfo.stageCount = 2;
////        pipelineInfo.pStages = shaderStages;
////        pipelineInfo.pVertexInputState = &vertexInputInfo;
////        pipelineInfo.pInputAssemblyState = &inputAssemblyInfo;
////        pipelineInfo.pViewportState = &viewportState;
////        pipelineInfo.pRasterizationState = &rasterizer;
////        pipelineInfo.pMultisampleState = &multisampling;
////        pipelineInfo.pColorBlendState = &colorBlending;
////        pipelineInfo.layout = pipelineLayout;
////        pipelineInfo.renderPass = renderPass;
////        pipelineInfo.subpass = 0;
////        pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
////        pipelineInfo.pDepthStencilState = &depthStencil;
////
////        if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS) {
////            throw std::runtime_error("failed to create graphics pipeline!");
////        }
////
////        vkDestroyShaderModule(device, fragShaderModule, nullptr);
////        vkDestroyShaderModule(device, vertShaderModule, nullptr);
////    }
////    void createTextureImage() {
////        int texWidth, texHeight, texChannels;
////
////        stbi_uc* pixels = stbi_load(TEXTURE_PATH.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
////        VkDeviceSize imageSize = texWidth * texHeight * 4;
////
////        mipLevels = static_cast<uint32_t>(std::floor(std::log2(std::max(texWidth, texHeight))));
////
////        if (!pixels) {
////            throw std::runtime_error("failed to load texture image!");
////        }
////
////        VkBuffer stagingBuffer;
////        VkDeviceMemory stagingBufferMemory;
////
////        createBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);
////
////        void* data;
////        vkMapMemory(device, stagingBufferMemory, 0, imageSize, 0, &data);
////        memcpy(data, pixels, static_cast<size_t>(imageSize));
////        vkUnmapMemory(device, stagingBufferMemory);
////
////        stbi_image_free(pixels);
////
////        createImage
////        (
////            texWidth,
////            texHeight,
////            mipLevels,
////            VK_SAMPLE_COUNT_1_BIT,
////            VK_FORMAT_R8G8B8A8_UNORM,
////            VK_IMAGE_TILING_OPTIMAL,
////            VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
////            VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
////            textureImage,
////            textureImageMemory
////        );
////
////        transitionImageLayout(textureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, mipLevels);
////        copyBufferToImage(stagingBuffer, textureImage, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));
////        //transitionImageLayout(textureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, mipLevels);
////
////        vkDestroyBuffer(device, stagingBuffer, nullptr);
////        vkFreeMemory(device, stagingBufferMemory, nullptr);
////
////        generateMipmaps(textureImage, VK_FORMAT_R8G8B8A8_UNORM, texWidth, texHeight, mipLevels);
////    }
////
////
////
////    void endSingleTimeCommands(VkCommandBuffer commandBuffer) {
////        vkEndCommandBuffer(commandBuffer);
////
////        VkSubmitInfo submitInfo = {};
////        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
////        submitInfo.commandBufferCount = 1;
////        submitInfo.pCommandBuffers = &commandBuffer;
////
////        vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
////        vkQueueWaitIdle(graphicsQueue);
////
////        vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
////    }
////
////    void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels) {
////        CreateContainer container = { device, pPhysicalDevice };
////        VkCommandBuffer commandBuffer = CommandBuffer::beginSingleTimeCommands(container, commandPool);
////
////        VkImageMemoryBarrier barrier = {};
////        barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
////        barrier.oldLayout = oldLayout;
////        barrier.newLayout = newLayout;
////        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
////        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
////        barrier.image = image;
////
////        if (newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL) {
////            barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;
////
////            if (hasStencilComponent(format)) {
////                barrier.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
////            }
////        }
////        else {
////            barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
////        }
////
////        barrier.subresourceRange.baseMipLevel = 0;
////        barrier.subresourceRange.levelCount = mipLevels;
////        barrier.subresourceRange.baseArrayLayer = 0;
////        barrier.subresourceRange.layerCount = 1;
////
////        VkPipelineStageFlags sourceStage;
////        VkPipelineStageFlags destinationStage;
////
////        if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
////            barrier.srcAccessMask = 0;
////            barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
////
////            sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
////            destinationStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
////        }
////        else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
////            barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
////            barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
////
////            sourceStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
////            destinationStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
////        }
////        else if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL) {
////            barrier.srcAccessMask = 0;
////            barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
////
////            sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
////            destinationStage = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
////        }
////        else if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL) {
////            barrier.srcAccessMask = 0;
////            barrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
////            sourceStage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT;
////            destinationStage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
////        }
////        else {
////            throw std::invalid_argument("unsupported layout transition!");
////        }
////
////        vkCmdPipelineBarrier(
////            commandBuffer,
////            sourceStage, destinationStage,
////            0,
////            0, nullptr,
////            0, nullptr,
////            1, &barrier
////        );
////
////        endSingleTimeCommands(commandBuffer);
////    }
////
////    void createTextureImageView() {
////        textureImageView = createImageView(textureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_ASPECT_COLOR_BIT, mipLevels);
////    }
////
////    void createTextureSampler() {
////        VkSamplerCreateInfo samplerInfo = {};
////        samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
////        samplerInfo.magFilter = VK_FILTER_LINEAR;
////        samplerInfo.minFilter = VK_FILTER_LINEAR;
////        samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
////        samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
////        samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
////
////        // �ٕ����t�B���^�����O�֘A
////        samplerInfo.anisotropyEnable = VK_FALSE;
////        samplerInfo.maxAnisotropy = 1;
////
////        samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
////        samplerInfo.unnormalizedCoordinates = VK_FALSE;
////        samplerInfo.compareEnable = VK_FALSE;
////        samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
////        samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
////        samplerInfo.mipLodBias = 0.0f;
////        samplerInfo.minLod = 0;
////        samplerInfo.maxLod = static_cast<float>(mipLevels);
////
////        VkResult result = vkCreateSampler(device, &samplerInfo, nullptr, &textureSampler);
////        if (result != VK_SUCCESS) {
////            throw std::runtime_error("failed to create sampler");
////        }
////    }
////
////    void createColorResources() {
////        VkFormat colorFormat = swapChainImageFormat;
////
////        createImage
////        (
////            swapChainExtent.width,
////            swapChainExtent.height,
////            1,
////            msaaSamples,
////            colorFormat,
////            VK_IMAGE_TILING_OPTIMAL,
////            VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
////            VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
////            colorImage,
////            colorImageMemory
////        );
////        colorImageView = createImageView(colorImage, colorFormat, VK_IMAGE_ASPECT_COLOR_BIT, 1);
////        transitionImageLayout(colorImage, colorFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, 1);
////    }
////
////    void createDepthResources() {
////        VkFormat depthFormat = findDepthFormat();
////
////        createImage
////        (
////            swapChainExtent.width,
////            swapChainExtent.height,
////            1,
////            msaaSamples,
////            depthFormat,
////            VK_IMAGE_TILING_OPTIMAL,
////            VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
////            VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
////            depthImage,
////            depthImageMemory
////        );
////        depthImageView = createImageView(depthImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT, 1);
////
////        transitionImageLayout(depthImage, depthFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, 1);
////    }
////
////    VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features) {
////        for (VkFormat format : candidates) {
////            VkFormatProperties props;
////            vkGetPhysicalDeviceFormatProperties(pPhysicalDevice, format, &props);
////            if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
////                return format;
////            }
////            else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
////                return format;
////            }
////        }
////        throw std::runtime_error("failed to find support format");
////    }
////
////    VkFormat findDepthFormat() {
////        return findSupportedFormat
////        (
////            {VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
////            VK_IMAGE_TILING_OPTIMAL,
////            VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
////        );
////    }
////
////    bool hasStencilComponent(VkFormat format) {
////        return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
////    }
////
////    void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels) {
////        // Check if image format supports linear blitting
////        VkFormatProperties formatProperties;
////        vkGetPhysicalDeviceFormatProperties(pPhysicalDevice, imageFormat, &formatProperties);
////
////        if (!(formatProperties.optimalTilingFeatures & VK_FORMAT_FEATURE_SAMPLED_IMAGE_FILTER_LINEAR_BIT)) {
////            throw std::runtime_error("texture image format does not support linear blitting!");
////        }
////
////        VkCommandBuffer commandBuffer = beginSingleTimeCommands();
////
////        VkImageMemoryBarrier barrier = {};
////        barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
////        barrier.image = image;
////        barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
////        barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
////        barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
////        barrier.subresourceRange.baseArrayLayer = 0;
////        barrier.subresourceRange.layerCount = 1;
////        barrier.subresourceRange.levelCount = 1;
////
////        int32_t mipWidth = texWidth;
////        int32_t mipHeight = texHeight;
////
////        for (uint32_t i = 1; i < mipLevels; i++) {
////            barrier.subresourceRange.baseMipLevel = i - 1;
////            barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
////            barrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
////            barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
////            barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
////
////            vkCmdPipelineBarrier(commandBuffer,
////                VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, 0,
////                0, nullptr,
////                0, nullptr,
////                1, &barrier);
////
////            VkImageBlit blit = {};
////            blit.srcOffsets[0] = { 0, 0, 0 };
////            blit.srcOffsets[1] = { mipWidth, mipHeight, 1 };
////            blit.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
////            blit.srcSubresource.mipLevel = i - 1;
////            blit.srcSubresource.baseArrayLayer = 0;
////            blit.srcSubresource.layerCount = 1;
////            blit.dstOffsets[0] = { 0, 0, 0 };
////            blit.dstOffsets[1] = { mipWidth > 1 ? mipWidth / 2 : 1, mipHeight > 1 ? mipHeight / 2 : 1, 1 };
////            blit.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
////            blit.dstSubresource.mipLevel = i;
////            blit.dstSubresource.baseArrayLayer = 0;
////            blit.dstSubresource.layerCount = 1;
////
////            vkCmdBlitImage(commandBuffer,
////                image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
////                image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
////                1, &blit,
////                VK_FILTER_LINEAR);
////
////            barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
////            barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
////            barrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
////            barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
////
////            vkCmdPipelineBarrier(commandBuffer,
////                VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0,
////                0, nullptr,
////                0, nullptr,
////                1, &barrier);
////
////            if (mipWidth > 1) mipWidth /= 2;
////            if (mipHeight > 1) mipHeight /= 2;
////        }
////
////        barrier.subresourceRange.baseMipLevel = mipLevels - 1;
////        barrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
////        barrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
////        barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
////        barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
////
////        vkCmdPipelineBarrier(commandBuffer,
////            VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, 0,
////            0, nullptr,
////            0, nullptr,
////            1, &barrier);
////
////        endSingleTimeCommands(commandBuffer);
////    }
////
////    VkShaderModule createShaderModule(const BinaryLoader::Data& code) {
////        return createShaderModule(reinterpret_cast<const uint32_t*>(code.first.get()), code.second);
////    }
////
////    VkShaderModule createShaderModule(const char* code, size_t codeSize) {
////        return createShaderModule(reinterpret_cast<const uint32_t*>(code), codeSize);
////    }
////
////    VkShaderModule createShaderModule(const uint32_t* pCode, size_t codeSize) {
////        VkShaderModuleCreateInfo createInfo = {};
////        createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
////        createInfo.codeSize = codeSize;
////        createInfo.pCode = pCode;
////
////        VkShaderModule shaderModule;
////        VkResult result = vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule);
////        if (result != VK_SUCCESS)
////        {
////            throw std::runtime_error("failed to create shader module!");
////        }
////        return shaderModule;
////    }
////
////    void createFramebuffers() {
////        swapChainFramebuffers.resize(swapChainImageViews.size());
////
////        for (size_t i = 0; i < swapChainImageViews.size(); ++i) {
////            std::array<VkImageView, 2> attachments = {
////                swapChainImageViews[i],
////                depthImageView
////            };
////
////            VkFramebufferCreateInfo framebufferInfo = {};
////            framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
////            framebufferInfo.renderPass = renderPass;
////            framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
////            framebufferInfo.pAttachments = attachments.data();
////            framebufferInfo.width = swapChainExtent.width;
////            framebufferInfo.height = swapChainExtent.height;
////            framebufferInfo.layers = 1;
////
////            VkResult result = vkCreateFramebuffer(device, &framebufferInfo, nullptr, &swapChainFramebuffers[i]);
////            if (result != VK_SUCCESS) {
////                throw std::runtime_error("failed to create framebuffer!");
////            }
////        }
////    }
////
////    void createCommandPool() {
////        QueueFamilyIndices queueFamilyIndices = findQueueFamilies(pPhysicalDevice);
////
////        VkCommandPoolCreateInfo poolInfo = {};
////        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
////        poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
////        poolInfo.flags = 0;
////
////        VkResult result = vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool);
////        if (result != VK_SUCCESS) {
////            throw std::runtime_error("failed to create command pool");
////        }
////    }
////
////    //void createVertexBuffer() {
////    //    VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();
////    //    VkBufferUsageFlags srcBufferUsageFlags = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
////    //    VkBufferUsageFlags dstBufferUsageFlags = VK_BUFFER_USAGE_TRANSFER_DST_BIT
////    //        | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
////    //    VkMemoryPropertyFlags srcMemoryPropertyFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
////    //        | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
////    //    VkMemoryPropertyFlags dstMemoryPropertyFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
////    //
////    //    VkBuffer stagingBuffer;
////    //    VkDeviceMemory stagingBufferMemory;
////    //
////    //    createBuffer(bufferSize, srcBufferUsageFlags, srcMemoryPropertyFlags, stagingBuffer, stagingBufferMemory);
////    //
////    //    void* data;
////    //    vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
////    //    memcpy(data, vertices.data(), (size_t)bufferSize);
////    //    vkUnmapMemory(device, stagingBufferMemory);
////    //
////    //    createBuffer(bufferSize, dstBufferUsageFlags, dstMemoryPropertyFlags, vertexBuffer, vertexBufferMemory);
////    //    copyBuffer(stagingBuffer, vertexBuffer, bufferSize);
////    //
////    //    vkDestroyBuffer(device, stagingBuffer, nullptr);
////    //    vkFreeMemory(device, stagingBufferMemory, nullptr);
////    //}
////    //
////    //void createIndexBuffer() {
////    //    VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();
////    //
////    //    VkBufferUsageFlags srcBufferUsageFlags = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
////    //    VkBufferUsageFlags dstBufferUsageFlags = VK_BUFFER_USAGE_TRANSFER_DST_BIT
////    //        | VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
////    //    VkMemoryPropertyFlags srcMemoryPropertyFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
////    //        | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
////    //    VkMemoryPropertyFlags dstMemoryPropertyFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
////    //
////    //    VkBuffer stagingBuffer;
////    //    VkDeviceMemory stagingBufferMemory;
////    //
////    //    createBuffer(bufferSize, srcBufferUsageFlags, srcMemoryPropertyFlags, stagingBuffer, stagingBufferMemory);
////    //
////    //    void* data;
////    //    vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
////    //    memcpy(data, indices.data(), (size_t)bufferSize);
////    //    vkUnmapMemory(device, stagingBufferMemory);
////    //
////    //    createBuffer(bufferSize, dstBufferUsageFlags, dstMemoryPropertyFlags, indexBuffer, indexBufferMemory);
////    //    copyBuffer(stagingBuffer, indexBuffer, bufferSize);
////    //
////    //    vkDestroyBuffer(device, stagingBuffer, nullptr);
////    //    vkFreeMemory(device, stagingBufferMemory, nullptr);
////    //}
////
////    void createUniformBuffers() {
////        VkDeviceSize bufferSize = sizeof(UniformBufferObject);
////
////        uniformBuffers.resize(swapChainImages.size());
////        uniformBuffersMemory.resize(swapChainImages.size());
////
////        VkBufferUsageFlags bufferUsageFlags = VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
////        VkMemoryPropertyFlags memoryPropertyFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT
////            | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
////        for (size_t i = 0; i < swapChainImages.size(); ++i) {
////            createBuffer(bufferSize, bufferUsageFlags, memoryPropertyFlags, uniformBuffers[i], uniformBuffersMemory[i]);
////        }
////    }
////    void createDescriptorPool() {
////        std::array<VkDescriptorPoolSize, 2> poolSizes = {};
////        poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
////        poolSizes[0].descriptorCount = static_cast<uint32_t>(swapChainImages.size());
////        poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
////        poolSizes[1].descriptorCount = static_cast<uint32_t>(swapChainImages.size());
////
////        VkDescriptorPoolCreateInfo poolInfo = {};
////        poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
////        poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
////        poolInfo.pPoolSizes = poolSizes.data();
////        poolInfo.maxSets = static_cast<uint32_t>(swapChainImages.size());
////
////        VkResult result = vkCreateDescriptorPool(device, &poolInfo, nullptr, &descriptorPool);
////        if (result != VK_SUCCESS) {
////            throw std::runtime_error("failed to create descriptor pool!");
////        }
////    }
////
////    void createDescriptorSets() {
////        std::vector<VkDescriptorSetLayout> layouts(swapChainImages.size(), descriptorSetLayout);
////        VkDescriptorSetAllocateInfo allocInfo = {};
////        allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
////        allocInfo.descriptorPool = descriptorPool;
////        allocInfo.descriptorSetCount = static_cast<uint32_t>(swapChainImages.size());
////        allocInfo.pSetLayouts = layouts.data();
////
////        descriptorSets.resize(swapChainImages.size());
////        VkResult result = vkAllocateDescriptorSets(device, &allocInfo, descriptorSets.data());
////        if (result != VK_SUCCESS) {
////            throw std::runtime_error("failed to allocate descriptor sets!");
////        }
////
////        uint32_t range = sizeof(UniformBufferObject);
////        for (size_t i = 0; i < swapChainImages.size(); ++i) {
////            VkDescriptorBufferInfo bufferInfo = {};
////            bufferInfo.buffer = uniformBuffers[i];
////            bufferInfo.offset = 0;
////            bufferInfo.range = range;
////
////            VkDescriptorImageInfo imageInfo = {};
////            imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
////            imageInfo.imageView = textureImageView;
////            imageInfo.sampler = textureSampler;
////
////            std::array<VkWriteDescriptorSet, 2> descriptorWrites = {};
////            descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
////            descriptorWrites[0].dstSet = descriptorSets[i];
////            descriptorWrites[0].dstBinding = 0;
////            descriptorWrites[0].dstArrayElement = 0;
////            descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
////            descriptorWrites[0].descriptorCount = 1;
////            descriptorWrites[0].pBufferInfo = &bufferInfo;
////
////            descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
////            descriptorWrites[1].dstSet = descriptorSets[i];
////            descriptorWrites[1].dstBinding = 1;
////            descriptorWrites[1].dstArrayElement = 0;
////            descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
////            descriptorWrites[1].descriptorCount = 1;
////            descriptorWrites[1].pImageInfo = &imageInfo;
////
////            vkUpdateDescriptorSets(device, descriptorWrites.size(), descriptorWrites.data(), 0, nullptr);
////        }
////    }
////
////    void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory) {
////        VkBufferCreateInfo bufferInfo = {};
////
////        bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
////        bufferInfo.size = size;
////        bufferInfo.usage = usage;
////        bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
////
////        VkResult result = vkCreateBuffer(device, &bufferInfo, nullptr, &buffer);
////        if (result != VK_SUCCESS) {
////            throw std::runtime_error("failed to create vertex buffer");
////        }
////
////        VkMemoryRequirements memoryRequirements;
////        vkGetBufferMemoryRequirements(device, buffer, &memoryRequirements);
////
////        VkPhysicalDeviceMemoryProperties memoryProperties;
////        vkGetPhysicalDeviceMemoryProperties(pPhysicalDevice, &memoryProperties);
////
////        VkMemoryAllocateInfo allocInfo = {};
////        allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
////        allocInfo.allocationSize = memoryRequirements.size;
////        allocInfo.memoryTypeIndex = findMemoryType(memoryRequirements.memoryTypeBits, properties);
////
////        result = vkAllocateMemory(device, &allocInfo, nullptr, &bufferMemory);
////        if (result != VK_SUCCESS) {
////            throw std::runtime_error("failed to allocate vertex buffer memory!");
////        }
////
////        vkBindBufferMemory(device, buffer, bufferMemory, 0);
////    }
////
////    void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
////        VkCommandBufferAllocateInfo allocInfo = {};
////        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
////        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
////        allocInfo.commandPool = commandPool;
////        allocInfo.commandBufferCount = 1;
////
////        VkCommandBuffer commandBuffer = beginSingleTimeCommands();
////        {
////            VkBufferCopy copyRegion = {};
////            copyRegion.size = size;
////            vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);
////        }
////        endSingleTimeCommands(commandBuffer);
////    }
////
////    void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height) {
////        VkCommandBuffer commandBuffer = beginSingleTimeCommands();
////
////        {
////            VkBufferImageCopy region = {};
////            region.bufferOffset = 0;
////            region.bufferRowLength = 0;
////            region.bufferImageHeight = 0;
////
////            region.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
////            region.imageSubresource.mipLevel = 0;
////            region.imageSubresource.baseArrayLayer = 0;
////            region.imageSubresource.layerCount = 1;
////
////            region.imageOffset = { 0, 0, 0 };
////            region.imageExtent = 
////            {
////                width,
////                height,
////                1
////            };
////
////            vkCmdCopyBufferToImage
////            (
////                commandBuffer,
////                buffer,
////                image,
////                VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
////                1,
////                &region
////            );
////        }
////
////        endSingleTimeCommands(commandBuffer);
////    }
////
////    void createCommandBuffers() {
////        commandBuffers.resize(swapChainFramebuffers.size());
////
////        VkCommandBufferAllocateInfo allocInfo = {};
////        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
////        allocInfo.commandPool = commandPool;
////        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
////        allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();
////
////        VkResult result = vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data());
////        if (result != VK_SUCCESS) {
////            throw std::runtime_error("failed to allocate command buffers!");
////        }
////
////        for (size_t i = 0; i < commandBuffers.size(); ++i) {
////            VkCommandBufferBeginInfo beginInfo = {};
////            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
////            beginInfo.flags = 0;
////            beginInfo.pInheritanceInfo = nullptr;
////
////            VkRenderPassBeginInfo renderPassInfo = {};
////            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
////            renderPassInfo.renderPass = renderPass;
////            renderPassInfo.framebuffer = swapChainFramebuffers[i];
////            renderPassInfo.renderArea.offset = { 0, 0 };
////            renderPassInfo.renderArea.extent = swapChainExtent;
////
////            std::array<VkClearValue, 2> clearValues = {};
////            clearValues[0].color = { 0, 0, 0, 1 };
////            clearValues[1].depthStencil = {1.0f, 0};
////
////            renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
////            renderPassInfo.pClearValues = clearValues.data();
////
////            result = vkBeginCommandBuffer(commandBuffers[i], &beginInfo);
////            if (result != VK_SUCCESS) {
////                throw std::runtime_error("failed to begin recording command buffer");
////            }
////
////            vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
////
////            vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);
////
////            VkBuffer vertexBuffers[] = { vertexBuffer };
////            VkDeviceSize offsets[] = { 0 };
////            vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, vertexBuffers, offsets);
////            vkCmdBindIndexBuffer(commandBuffers[i], indexBuffer, 0, VK_INDEX_TYPE_UINT32);
////
////            vkCmdBindDescriptorSets(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSets[i], 0, nullptr);
////            //vkCmdDraw(commandBuffers[i], static_cast<uint32_t>(vertices.size()), 1, 0, 0);
////            vkCmdDrawIndexed(commandBuffers[i], static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);
////
////            vkCmdEndRenderPass(commandBuffers[i]);
////
////            result = vkEndCommandBuffer(commandBuffers[i]);
////            if (result != VK_SUCCESS) {
////                throw std::runtime_error("fauled to end recording command bu");
////            }
////        }
////    }
////
////    void createSyncObjects() {
////        imageAvailableSemaphores.resize(MAX_FAMES_IN_FLIGHT);
////        renderFinishedSemaphores.resize(MAX_FAMES_IN_FLIGHT);
////        inFlightFences.resize(MAX_FAMES_IN_FLIGHT);
////
////        VkSemaphoreCreateInfo semaphoreInfo = {};
////        semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
////
////        VkFenceCreateInfo fenceInfo = {};
////        fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
////        fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
////
////        for (size_t i = 0; i < MAX_FAMES_IN_FLIGHT; ++i) {
////            if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS
////                || vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS
////                || vkCreateFence(device, &fenceInfo, nullptr, &inFlightFences[i])) {
////
////                throw std::runtime_error("failed to create semaphores!");
////            }
////        }
////    }
////
////    void updateUniformBuffer(uint32_t currentImage) {
////        static auto startTime = std::chrono::high_resolution_clock::now();
////
////        auto currentTime = std::chrono::high_resolution_clock::now();
////        float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
////
////        UniformBufferObject ubo = {};
////        ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
////        ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
////        ubo.projection = glm::perspective(glm::radians(45.0f), swapChainExtent.width / (float)swapChainExtent.height, 0.1f, 10.0f);
////
////        ubo.projection[1][1] *= -1;
////
////        size_t size = sizeof(ubo);
////        void* data;
////        vkMapMemory(device, uniformBuffersMemory[currentImage], 0, size, 0, &data);
////        memcpy(data, &ubo, size);
////        vkUnmapMemory(device, uniformBuffersMemory[currentImage]);
////    }
////
////    void drawFrame() {
////        // uint64��max����ꂽ�ۃ^�C���A�E�g�������ɂȂ�
////        // �X���b�v�`�F�[���͊g���@�\�ł��邽�߁AVk*KHR�����K���̂���֐����g�p����K�v������
////        vkWaitForFences(device, 1, &inFlightFences[currentFrame], VK_TRUE, std::numeric_limits<uint64_t>::max());
////
////        uint32_t imageIndex;
////        VkResult result = vkAcquireNextImageKHR
////        (
////            device,
////            pSwapChain,
////            std::numeric_limits<uint64_t>::max(),
////            imageAvailableSemaphores[currentFrame],
////            VK_NULL_HANDLE,
////            &imageIndex
////        );
////        if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized) {
////            framebufferResized = false;
////            recreateSwapChain();
////            return;
////        }
////        else if (result != VK_SUCCESS) {
////            throw std::runtime_error("failed to acquire swap chain image!");
////        }
////
////        updateUniformBuffer(imageIndex);
////
////        VkSubmitInfo submitInfo = {};
////        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
////
////        VkSemaphore waitSemaphores[] = { imageAvailableSemaphores[currentFrame] };
////        VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
////        submitInfo.waitSemaphoreCount = 1;
////        submitInfo.pWaitSemaphores = waitSemaphores;
////        submitInfo.pWaitDstStageMask = waitStages;
////
////        submitInfo.commandBufferCount = 1;
////        submitInfo.pCommandBuffers = &commandBuffers[imageIndex];
////
////        VkSemaphore signalSemaphores[] = { renderFinishedSemaphores[currentFrame] };
////        submitInfo.signalSemaphoreCount = 1;
////        submitInfo.pSignalSemaphores = signalSemaphores;
////
////        vkResetFences(device, 1, &inFlightFences[currentFrame]);
////
////        if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS) {
////            throw std::runtime_error("failed to submit draw command buffer!");
////        }
////
////        VkPresentInfoKHR presentInfo = {};
////        presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
////
////        presentInfo.waitSemaphoreCount = 1;
////        presentInfo.pWaitSemaphores = signalSemaphores;
////
////        VkSwapchainKHR swapChains[] = { pSwapChain };
////        presentInfo.swapchainCount = 1;
////        presentInfo.pSwapchains = swapChains;
////
////        presentInfo.pImageIndices = &imageIndex;
////
////        vkQueuePresentKHR(presentQueue, &presentInfo);
////
////        currentFrame = (currentFrame + 1) % MAX_FAMES_IN_FLIGHT;
////    }
////
////    bool checkValidationLayerSupport() {
////        uint32_t layerCount;
////        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
////
////        std::vector<VkLayerProperties> availableLayers(layerCount);
////        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
////
////        for (const char* layerName : validationLayers) {
////            bool layerFound = false;
////
////            for (const auto& layerProperties : availableLayers) {
////                if (strcmp(layerName, layerProperties.layerName) == 0) {
////                    layerFound = true;
////                    break;
////                }
////            }
////
////            if (!layerFound) {
////                return false;
////            }
////        }
////
////        return true;
////    }
////};
////#include "Vector3.h"
////
////int main() {
////    HelloTriangleApplication app;
////    //Vector3 v1 = { 1, 1, 1 };
////    //Vector3 v2 = { 1, 1, 1 };
////    //Vector3 v3 = { 1, 1, 1 };
////    //Vector3 v4 = { 1, 1, 1 };
////    //
////    //Vector3 result = v1 * 1.0f;
////    //result = v1 + v2;
////    //std::cout << result << std::endl;
////    //result = v1 - v2;
////    //result = v1 * v2;
////    //result = v1 / v2;
////    try {
////        app.run();
////    }
////    catch (const std::exception& e) {
////        std::cerr << e.what() << std::endl;
////        return EXIT_FAILURE;
////    }
////
////    return EXIT_SUCCESS;
////}
//
//#include "stdafx.h"
//
//#define TINYOBJLOADER_IMPLEMENTATION
//#define STB_IMAGE_IMPLEMENTATION
//
//#include <tiny_obj_loader.h>
//#include <stb_image.h>


// Vulkan���g�p����
#define USE_VULKAN_

#ifdef USE_VULKAN_
#include "vulkan_sample_loop01.h"
#endif
#include  "imain_loop.h"

int main() {
    rengine::IMainLoop* app = nullptr;
#ifdef USE_VULKAN_
    app = new vengine::VulkanSampleLoop01();
    //app = new vengine::VulkanSampleLoop02();
    //app = new vengine::VulkanSampleLoop03();
    // �̂悤�Ȏg�����z��
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

//const std::string MODEL_PATH = "models/chalet.obj";
//const std::string TEXTURE_PATH = "textures/chalet.jpg";

//
//VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
//    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
//    if (func != nullptr) {
//        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
//    }
//    else {
//        return VK_ERROR_EXTENSION_NOT_PRESENT;
//    }
//}
//
//void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
//    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
//    if (func != nullptr) {
//        func(instance, debugMessenger, pAllocator);
//    }
//}

//struct QueueFamilyIndices {
//    std::optional<uint32_t> graphicsFamily;
//    std::optional<uint32_t> presentFamily;
//
//    bool isComplete() {
//        return graphicsFamily.has_value() && presentFamily.has_value();
//    }
//};

//struct SwapChainSupportDetails {
//    VkSurfaceCapabilitiesKHR capabilities;
//    std::vector<VkSurfaceFormatKHR> formats;
//    std::vector<VkPresentModeKHR> presentModes;
//};

//struct Vertex {
//    glm::vec3 pos;
//    glm::vec3 color;
//    glm::vec2 texCoord;
//
//    static VkVertexInputBindingDescription getBindingDescription() {
//        VkVertexInputBindingDescription bindingDescription = {};
//        bindingDescription.binding = 0;
//        bindingDescription.stride = sizeof(Vertex);
//        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
//
//        return bindingDescription;
//    }
//
//    static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() {
//        std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions = {};
//
//        attributeDescriptions[0].binding = 0;
//        attributeDescriptions[0].location = 0;
//        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
//        attributeDescriptions[0].offset = offsetof(Vertex, pos);
//
//        attributeDescriptions[1].binding = 0;
//        attributeDescriptions[1].location = 1;
//        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
//        attributeDescriptions[1].offset = offsetof(Vertex, color);
//
//        attributeDescriptions[2].binding = 0;
//        attributeDescriptions[2].location = 2;
//        attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
//        attributeDescriptions[2].offset = offsetof(Vertex, texCoord);
//
//        return attributeDescriptions;
//    }
//
//    bool operator==(const Vertex& other) const {
//        return pos == other.pos && color == other.color && texCoord == other.texCoord;
//    }
//};
//
//namespace std {
//    template<> struct hash<Vertex> {
//        size_t operator()(Vertex const& vertex) const {
//            return ((hash<glm::vec3>()(vertex.pos) ^ (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^ (hash<glm::vec2>()(vertex.texCoord) << 1);
//        }
//    };
//}
//

//class HelloTriangleApplication {
//public:
//    HelloTriangleApplication()
//#ifdef USE_VULKAN_
//        : graphics_backend_
//          (
//              std::make_unique<rengine::IGraphicsBackend>(new vengine::VulkanGraphicsBackend("test", "vulkan", user_define::WIDTH, user_define::HEIGHT))
//          )
//#endif
//    {
//
//    }
//    void run() {
//        initWindow();
//        initVulkan();
//        mainLoop();
//        cleanup();
//    }
//
//private:
//    //std::unique_ptr<Debug::Messanger> pMessanger;
//    std::unique_ptr<rengine::IGraphicsBackend> graphics_backend_;
//
//    //VkDevice device; // TODO ����
//
//    VkSampleCountFlagBits msaaSamples = VK_SAMPLE_COUNT_1_BIT;
//
//    //VkQueue graphicsQueue;
//    //VkQueue presentQueue;
//
//    //VkSwapchainKHR swapChain;
//    //std::vector<VkImage> swapChainImages;
//    //VkFormat swapChainImageFormat;
//    //VkExtent2D swapChainExtent;
//    //std::vector<VkImageView> swapChainImageViews;
//    //std::vector<VkFramebuffer> swapChainFramebuffers;
//
//    //VkRenderPass renderPass;
//    //VkDescriptorSetLayout descriptorSetLayout;
//    //VkPipelineLayout pipelineLayout;
//    //VkPipeline graphicsPipeline;
//
//    //VkCommandPool commandPool;
//
//    //VkImage colorImage;
//    //VkDeviceMemory colorImageMemory;
//    //VkImageView colorImageView;
//
//    //VkImage depthImage;
//    //VkDeviceMemory depthImageMemory;
//    //VkImageView depthImageView;
//
//    uint32_t mipLevels;
//    VkImage textureImage;
//    VkDeviceMemory textureImageMemory;
//    VkImageView textureImageView;
//    VkSampler textureSampler;
//
//    std::vector<Vertex> vertices;
//    std::vector<uint32_t> indices;
//    VkBuffer vertexBuffer;
//    VkDeviceMemory vertexBufferMemory;
//    VkBuffer indexBuffer;
//    VkDeviceMemory indexBufferMemory;
//
//    std::vector<VkBuffer> uniformBuffers;
//    std::vector<VkDeviceMemory> uniformBuffersMemory;
//
//    //VkDescriptorPool descriptorPool;
//    std::vector<VkDescriptorSet> descriptorSets;
//
//    //std::vector<VkCommandBuffer> commandBuffers;
//
//    //std::vector<VkSemaphore> imageAvailableSemaphores;
//    //std::vector<VkSemaphore> renderFinishedSemaphores;
//    //std::vector<VkFence> inFlightFences;
//    //size_t currentFrame = 0;
//
//    void initWindow() {
//        //pWindow = new Window("vulkan", UserDefine::WIDTH, UserDefine::HEIGHT);
//    }
//
//    void initVulkan() {
//        createInstance();
//        setupDebugMessenger();
//        createSurface();
//        pickPhysicalDevice();
//        createLogicalDevice();
//        createSwapChain();
//        createImageViews();
//        createRenderPass();
//        createDescriptorSetLayout();
//        createGraphicsPipeline();
//        createCommandPool();
//        createColorResources();
//        createDepthResources();
//        createFramebuffers();
//        createTextureImage();
//        createTextureImageView();
//        createTextureSampler();
//        loadModel();
//        createVertexBuffer();
//        createIndexBuffer();
//        createUniformBuffers();
//        createDescriptorPool();
//        createDescriptorSets();
//        createCommandBuffers();
//        createSyncObjects();
//    }
//
//    void mainLoop() {
//        //while (!graphics_backend_->getWindow()->isShouldClose()) {
//        //    glfwPollEvents();
//        //    drawFrame();
//        //}
//
//        // TODO GraphicsBackend����
//        //vkDeviceWaitIdle(device);
//    }
//
//    void cleanupSwapChain() {
//        //vkDestroyImageView(device, depthImageView, nullptr);
//        //vkDestroyImage(device, depthImage, nullptr);
//        //vkFreeMemory(device, depthImageMemory, nullptr);
//
//        //vkDestroyImageView(device, colorImageView, nullptr);
//        //vkDestroyImage(device, colorImage, nullptr);
//        //vkFreeMemory(device, colorImageMemory, nullptr);
//
//        /*
//        VkDevice device;
//
//        for (auto framebuffer : swapChainFramebuffers) {
//            vkDestroyFramebuffer(device, framebuffer, nullptr);
//        }
//
//        vkFreeCommandBuffers(device, commandPool, static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());
//         
//        vkDestroyPipeline(device, graphicsPipeline, nullptr);
//        vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
//        vkDestroyRenderPass(device, renderPass, nullptr);
//
//        for (auto imageView : swapChainImageViews) {
//            vkDestroyImageView(device, imageView, nullptr);
//        }
//
//        vkDestroySwapchainKHR(device, swapChain, nullptr);
//
//        for (size_t i = 0; i < swapChainImages.size(); i++) {
//            vkDestroyBuffer(device, uniformBuffers[i], nullptr);
//            vkFreeMemory(device, uniformBuffersMemory[i], nullptr);
//        }
//        */
//
//        //vkDestroyDescriptorPool(device, descriptorPool, nullptr);
//    }
//
//    void cleanup() {
//        //auto container = disposeContainer(pInstance, nullptr);
//
//        /*
//        cleanupSwapChain();
//
//        vkDestroySampler(device, textureSampler, nullptr);
//        vkDestroyImageView(device, textureImageView, nullptr);
//
//        vkDestroyImage(device, textureImage, nullptr);
//        vkFreeMemory(device, textureImageMemory, nullptr);
//
//        vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);
//
//        vkDestroyBuffer(device, indexBuffer, nullptr);
//        vkFreeMemory(device, indexBufferMemory, nullptr);
//
//        vkDestroyBuffer(device, vertexBuffer, nullptr);
//        vkFreeMemory(device, vertexBufferMemory, nullptr);
//
//        //for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
//        //    vkDestroySemaphore(device, renderFinishedSemaphores[i], nullptr);
//        //    vkDestroySemaphore(device, imageAvailableSemaphores[i], nullptr);
//        //    vkDestroyFence(device, inFlightFences[i], nullptr);
//        //}
//
//        vkDestroyCommandPool(device, commandPool, nullptr);
//
//        vkDestroyDevice(device, nullptr);
//
//        //pMessanger->dispose(container);
//        //pSurface->dispose(container);
//        //pInstance->dispose();
//        //pWindow->dispose();
//
//        glfwTerminate();
//        */
//    }
//
//    void recreateSwapChain() {
//        //pWindow->recreateSwapChain();
//
//        //vkDeviceWaitIdle(device);
//
//        cleanupSwapChain();
//
//        createSwapChain();
//        createImageViews();
//        createRenderPass();
//        createGraphicsPipeline();
//        createColorResources();
//        createDepthResources();
//        createFramebuffers();
//        createUniformBuffers();
//        createDescriptorPool();
//        createDescriptorSets();
//        createCommandBuffers();
//    }
//
//    void createInstance() {
//        //if (UserDefine::enableValidationLayers && !checkValidationLayerSupport()) {
//        //    throw std::runtime_error("validation layers requested, but not available!");
//        //}
//        //
//        //pInstance = new VulkanInstance("Hello Triangle", "No Engine");
//    }
//
//    void setupDebugMessenger() {
//        //if (!UserDefine::enableValidationLayers) return;
//        //
//        //pMessanger = new Debug::Messanger();
//        //pMessanger->setupDebug(*pInstance, UserDefine::enableValidationLayers);
//    }
//
//    void createSurface() {
//        //pSurface = new Surface();
//        //pSurface->create(createContainer(pWindow, pInstance, pPhysicalDevice, pSurface));
//    }
//
//    void pickPhysicalDevice() {
//        //pPhysicalDeviceOwner = new PhysicalDeviceOwner();
//        //pPhysicalDeviceOwner->Initialize(createContainer(pWindow, pInstance, pPhysicalDevice, pSurface));
//        //pPhysicalDeviceOwner->takeCurrentDevice(createContainer(pWindow, pInstance, pPhysicalDevice, pSurface), pPhysicalDevice);
//    }
//
//    void createLogicalDevice() {
//        //pLogicalDevice = new LogicalDevice();
//        //pLogicalDevice->create(createContainer(pWindow, pInstance, pPhysicalDevice, pSurface));
//
//
//        //QueueFamilyIndices indices = findQueueFamilies(*pPhysicalDevice);
//        //
//        //std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
//        //std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };
//        //
//        //float queuePriority = 1.0f;
//        //for (uint32_t queueFamily : uniqueQueueFamilies) {
//        //    VkDeviceQueueCreateInfo queueCreateInfo = {};
//        //    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
//        //    queueCreateInfo.queueFamilyIndex = queueFamily;
//        //    queueCreateInfo.queueCount = 1;
//        //    queueCreateInfo.pQueuePriorities = &queuePriority;
//        //    queueCreateInfos.push_back(queueCreateInfo);
//        //}
//        //
//        //VkPhysicalDeviceFeatures deviceFeatures = {};
//        //deviceFeatures.samplerAnisotropy = VK_TRUE;
//        //
//        //VkDeviceCreateInfo createInfo = {};
//        //createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
//        //
//        //createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
//        //createInfo.pQueueCreateInfos = queueCreateInfos.data();
//        //
//        //createInfo.pEnabledFeatures = &deviceFeatures;
//        //
//        //createInfo.enabledExtensionCount = static_cast<uint32_t>(UserDefine::deviceExtensions.size());
//        //createInfo.ppEnabledExtensionNames = UserDefine::deviceExtensions.data();
//        //
//        //if (UserDefine::enableValidationLayers) {
//        //    createInfo.enabledLayerCount = static_cast<uint32_t>(UserDefine::validationLayers.size());
//        //    createInfo.ppEnabledLayerNames = UserDefine::validationLayers.data();
//        //}
//        //else {
//        //    createInfo.enabledLayerCount = 0;
//        //}
//        //
//        //if (vkCreateDevice(*pPhysicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
//        //    throw std::runtime_error("failed to create logical device!");
//        //}
//        //
//        //vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
//        //vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
//    }
//
//    void createSwapChain() {
//        //SwapChainSupportDetails swapChainSupport = querySwapChainSupport(*pPhysicalDevice);
//        //
//        //VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
//        //VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
//        //VkExtent2D extent = chooseSwapExtent(swapChainSupport.capabilities);
//        //
//        //uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
//        //if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
//        //    imageCount = swapChainSupport.capabilities.maxImageCount;
//        //}
//        //
//        //VkSwapchainCreateInfoKHR createInfo = {};
//        //createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
//        //createInfo.surface = *pSurface;
//        //
//        //createInfo.minImageCount = imageCount;
//        //createInfo.imageFormat = surfaceFormat.format;
//        //createInfo.imageColorSpace = surfaceFormat.colorSpace;
//        //createInfo.imageExtent = extent;
//        //createInfo.imageArrayLayers = 1;
//        //createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
//        //
//        //QueueFamilyIndices indices = findQueueFamilies(*pPhysicalDevice);
//        //uint32_t queueFamilyIndices[] = { indices.graphicsFamily.value(), indices.presentFamily.value() };
//        //
//        //if (indices.graphicsFamily != indices.presentFamily) {
//        //    createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
//        //    createInfo.queueFamilyIndexCount = 2;
//        //    createInfo.pQueueFamilyIndices = queueFamilyIndices;
//        //}
//        //else {
//        //    createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
//        //}
//        //
//        //createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
//        //createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
//        //createInfo.presentMode = presentMode;
//        //createInfo.clipped = VK_TRUE;
//        //
//        //if (vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain) != VK_SUCCESS) {
//        //    throw std::runtime_error("failed to create swap chain!");
//        //}
//        //
//        //vkGetSwapchainImagesKHR(device, swapChain, &imageCount, nullptr);
//        //swapChainImages.resize(imageCount);
//        //vkGetSwapchainImagesKHR(device, swapChain, &imageCount, swapChainImages.data());
//        //
//        //swapChainImageFormat = surfaceFormat.format;
//        //swapChainExtent = extent;
//    }
//
//    void createImageViews() {
//        //swapChainImageViews.resize(swapChainImages.size());
//
//        //for (uint32_t i = 0; i < swapChainImages.size(); i++) {
//        //    swapChainImageViews[i] = createImageView(swapChainImages[i], swapChainImageFormat, VK_IMAGE_ASPECT_COLOR_BIT, 1);
//        //}
//    }
//
//    void createRenderPass() {
//        //VkAttachmentDescription colorAttachment = {};
//        //colorAttachment.format = swapChainImageFormat;
//        //colorAttachment.samples = msaaSamples;
//        //colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
//        //colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
//        //colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
//        //colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
//        //colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
//        //colorAttachment.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
//
//        //VkAttachmentDescription depthAttachment = {};
//        //depthAttachment.format = findDepthFormat();
//        //depthAttachment.samples = msaaSamples;
//        //depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
//        //depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
//        //depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
//        //depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
//        //depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
//        //depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
//
//        //VkAttachmentDescription colorAttachmentResolve = {};
//        //colorAttachmentResolve.format = swapChainImageFormat;
//        //colorAttachmentResolve.samples = VK_SAMPLE_COUNT_1_BIT;
//        //colorAttachmentResolve.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
//        //colorAttachmentResolve.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
//        //colorAttachmentResolve.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
//        //colorAttachmentResolve.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
//        //colorAttachmentResolve.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
//        //colorAttachmentResolve.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
//
//        //VkAttachmentReference colorAttachmentRef = {};
//        //colorAttachmentRef.attachment = 0;
//        //colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
//
//        //VkAttachmentReference depthAttachmentRef = {};
//        //depthAttachmentRef.attachment = 1;
//        //depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
//
//        //VkAttachmentReference colorAttachmentResolveRef = {};
//        //colorAttachmentResolveRef.attachment = 2;
//        //colorAttachmentResolveRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
//
//        //VkSubpassDescription subpass = {};
//        //subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
//        //subpass.colorAttachmentCount = 1;
//        //subpass.pColorAttachments = &colorAttachmentRef;
//        //subpass.pDepthStencilAttachment = &depthAttachmentRef;
//        //subpass.pResolveAttachments = &colorAttachmentResolveRef;
//
//        //VkSubpassDependency dependency = {};
//        //dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
//        //dependency.dstSubpass = 0;
//        //dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
//        //dependency.srcAccessMask = 0;
//        //dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
//        //dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
//
//        //std::array<VkAttachmentDescription, 3> attachments = { colorAttachment, depthAttachment, colorAttachmentResolve };
//        //VkRenderPassCreateInfo renderPassInfo = {};
//        //renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
//        //renderPassInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
//        //renderPassInfo.pAttachments = attachments.data();
//        //renderPassInfo.subpassCount = 1;
//        //renderPassInfo.pSubpasses = &subpass;
//        //renderPassInfo.dependencyCount = 1;
//        //renderPassInfo.pDependencies = &dependency;
//
//        //if (vkCreateRenderPass(device, &renderPassInfo, nullptr, &renderPass) != VK_SUCCESS) {
//        //    throw std::runtime_error("failed to create render pass!");
//        //}
//    }
//
//    void createDescriptorSetLayout() {
//        //VkDescriptorSetLayoutBinding uboLayoutBinding = {};
//        //uboLayoutBinding.binding = 0;
//        //uboLayoutBinding.descriptorCount = 1;
//        //uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
//        //uboLayoutBinding.pImmutableSamplers = nullptr;
//        //uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
//
//        //VkDescriptorSetLayoutBinding samplerLayoutBinding = {};
//        //samplerLayoutBinding.binding = 1;
//        //samplerLayoutBinding.descriptorCount = 1;
//        //samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
//        //samplerLayoutBinding.pImmutableSamplers = nullptr;
//        //samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;
//
//        //std::array<VkDescriptorSetLayoutBinding, 2> bindings = { uboLayoutBinding, samplerLayoutBinding };
//        //VkDescriptorSetLayoutCreateInfo layoutInfo = {};
//        //layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
//        //layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
//        //layoutInfo.pBindings = bindings.data();
//
//        //if (vkCreateDescriptorSetLayout(device, &layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS) {
//        //    throw std::runtime_error("failed to create descriptor set layout!");
//        //}
//    }
//
//    void createGraphicsPipeline() {
//        /*auto vertShaderCode = readFile("shaders/vert.spv");
//        auto fragShaderCode = readFile("shaders/frag.spv");
//
//        VkShaderModule vertShaderModule = createShaderModule(vertShaderCode);
//        VkShaderModule fragShaderModule = createShaderModule(fragShaderCode);
//
//        VkPipelineShaderStageCreateInfo vertShaderStageInfo = {};
//        vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
//        vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
//        vertShaderStageInfo.module = vertShaderModule;
//        vertShaderStageInfo.pName = "main";
//
//        VkPipelineShaderStageCreateInfo fragShaderStageInfo = {};
//        fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
//        fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
//        fragShaderStageInfo.module = fragShaderModule;
//        fragShaderStageInfo.pName = "main";
//
//        VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };
//
//        VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
//        vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
//
//        auto bindingDescription = Vertex::getBindingDescription();
//        auto attributeDescriptions = Vertex::getAttributeDescriptions();
//
//        vertexInputInfo.vertexBindingDescriptionCount = 1;
//        vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
//        vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
//        vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();
//
//        VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
//        inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
//        inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
//        inputAssembly.primitiveRestartEnable = VK_FALSE;
//
//        VkViewport viewport = {};
//        viewport.x = 0.0f;
//        viewport.y = 0.0f;
//        viewport.width = (float)swapChainExtent.width;
//        viewport.height = (float)swapChainExtent.height;
//        viewport.minDepth = 0.0f;
//        viewport.maxDepth = 1.0f;
//
//        VkRect2D scissor = {};
//        scissor.offset = { 0, 0 };
//        scissor.extent = swapChainExtent;
//
//        VkPipelineViewportStateCreateInfo viewportState = {};
//        viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
//        viewportState.viewportCount = 1;
//        viewportState.pViewports = &viewport;
//        viewportState.scissorCount = 1;
//        viewportState.pScissors = &scissor;
//
//        VkPipelineRasterizationStateCreateInfo rasterizer = {};
//        rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
//        rasterizer.depthClampEnable = VK_FALSE;
//        rasterizer.rasterizerDiscardEnable = VK_FALSE;
//        rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
//        rasterizer.lineWidth = 1.0f;
//        rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
//        rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
//        rasterizer.depthBiasEnable = VK_FALSE;
//
//        VkPipelineMultisampleStateCreateInfo multisampling = {};
//        multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
//        multisampling.sampleShadingEnable = VK_FALSE;
//        multisampling.rasterizationSamples = msaaSamples;
//
//        VkPipelineDepthStencilStateCreateInfo depthStencil = {};
//        depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
//        depthStencil.depthTestEnable = VK_TRUE;
//        depthStencil.depthWriteEnable = VK_TRUE;
//        depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
//        depthStencil.depthBoundsTestEnable = VK_FALSE;
//        depthStencil.stencilTestEnable = VK_FALSE;
//
//        VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
//        colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
//        colorBlendAttachment.blendEnable = VK_FALSE;
//
//        VkPipelineColorBlendStateCreateInfo colorBlending = {};
//        colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
//        colorBlending.logicOpEnable = VK_FALSE;
//        colorBlending.logicOp = VK_LOGIC_OP_COPY;
//        colorBlending.attachmentCount = 1;
//        colorBlending.pAttachments = &colorBlendAttachment;
//        colorBlending.blendConstants[0] = 0.0f;
//        colorBlending.blendConstants[1] = 0.0f;
//        colorBlending.blendConstants[2] = 0.0f;
//        colorBlending.blendConstants[3] = 0.0f;
//
//        VkPipelineLayoutCreateInfo pipelineLayoutInfo = {};
//        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
//        pipelineLayoutInfo.setLayoutCount = 1;
//        pipelineLayoutInfo.pSetLayouts = &descriptorSetLayout;
//
//        if (vkCreatePipelineLayout(device, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
//            throw std::runtime_error("failed to create pipeline layout!");
//        }
//
//        VkGraphicsPipelineCreateInfo pipelineInfo = {};
//        pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
//        pipelineInfo.stageCount = 2;
//        pipelineInfo.pStages = shaderStages;
//        pipelineInfo.pVertexInputState = &vertexInputInfo;
//        pipelineInfo.pInputAssemblyState = &inputAssembly;
//        pipelineInfo.pViewportState = &viewportState;
//        pipelineInfo.pRasterizationState = &rasterizer;
//        pipelineInfo.pMultisampleState = &multisampling;
//        pipelineInfo.pDepthStencilState = &depthStencil;
//        pipelineInfo.pColorBlendState = &colorBlending;
//        pipelineInfo.layout = pipelineLayout;
//        pipelineInfo.renderPass = renderPass;
//        pipelineInfo.subpass = 0;
//        pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
//
//        if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline) != VK_SUCCESS) {
//            throw std::runtime_error("failed to create graphics pipeline!");
//        }
//
//        vkDestroyShaderModule(device, fragShaderModule, nullptr);
//        vkDestroyShaderModule(device, vertShaderModule, nullptr);*/
//    }
//
//    void createFramebuffers() {
//        //swapChainFramebuffers.resize(swapChainImageViews.size());
//
//        //for (size_t i = 0; i < swapChainImageViews.size(); i++) {
//        //    std::array<VkImageView, 3> attachments = {
//        //        colorImageView,
//        //        depthImageView,
//        //        swapChainImageViews[i]
//        //    };
//
//        //    VkFramebufferCreateInfo framebufferInfo = {};
//        //    framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
//        //    framebufferInfo.renderPass = renderPass;
//        //    framebufferInfo.attachmentCount = static_cast<uint32_t>(attachments.size());
//        //    framebufferInfo.pAttachments = attachments.data();
//        //    framebufferInfo.width = swapChainExtent.width;
//        //    framebufferInfo.height = swapChainExtent.height;
//        //    framebufferInfo.layers = 1;
//
//        //    if (vkCreateFramebuffer(device, &framebufferInfo, nullptr, &swapChainFramebuffers[i]) != VK_SUCCESS) {
//        //        throw std::runtime_error("failed to create framebuffer!");
//        //    }
//        //}
//    }
//
//    void createCommandPool() {
//        //QueueFamilyIndices queueFamilyIndices = findQueueFamilies(*pPhysicalDevice);
//
//        //VkCommandPoolCreateInfo poolInfo = {};
//        //poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
//        //poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();
//
//        //if (vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS) {
//        //    throw std::runtime_error("failed to create graphics command pool!");
//        //}
//    }
//
//    void createColorResources() {
//        //VkFormat colorFormat = swapChainImageFormat;
//
//        //createImage(swapChainExtent.width, swapChainExtent.height, 1, msaaSamples, colorFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT | VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, colorImage, colorImageMemory);
//        //colorImageView = createImageView(colorImage, colorFormat, VK_IMAGE_ASPECT_COLOR_BIT, 1);
//
//        //transitionImageLayout(colorImage, colorFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, 1);
//    }
//
//    void createDepthResources() {
//        //VkFormat depthFormat = findDepthFormat();
//
//        //createImage(swapChainExtent.width, swapChainExtent.height, 1, msaaSamples, depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, depthImage, depthImageMemory);
//        //depthImageView = createImageView(depthImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT, 1);
//
//        //transitionImageLayout(depthImage, depthFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL, 1);
//    }
//
//    //VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features) {
//    //    for (VkFormat format : candidates) {
//    //        VkFormatProperties props;
//    //        vkGetPhysicalDeviceFormatProperties(*pPhysicalDevice, format, &props);
//
//    //        if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
//    //            return format;
//    //        }
//    //        else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
//    //            return format;
//    //        }
//    //    }
//
//    //    throw std::runtime_error("failed to find supported format!");
//    //}
//
//    //VkFormat findDepthFormat() {
//    //    return findSupportedFormat(
//    //        { VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT },
//    //        VK_IMAGE_TILING_OPTIMAL,
//    //        VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
//    //    );
//    //}
//
//    //bool hasStencilComponent(VkFormat format) {
//    //    return format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT;
//    //}
//
//    void createTextureImage() {
//        //int texWidth, texHeight, texChannels;
//        //stbi_uc* pixels = stbi_load(TEXTURE_PATH.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
//        //VkDeviceSize imageSize = texWidth * texHeight * 4;
//        //mipLevels = static_cast<uint32_t>(std::floor(std::log2(std::max(texWidth, texHeight)))) + 1;
//
//        //if (!pixels) {
//        //    throw std::runtime_error("failed to load texture image!");
//        //}
//
//        //VkBuffer stagingBuffer;
//        //VkDeviceMemory stagingBufferMemory;
//        //createBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);
//
//        //void* data;
//        //vkMapMemory(device, stagingBufferMemory, 0, imageSize, 0, &data);
//        //memcpy(data, pixels, static_cast<size_t>(imageSize));
//        //vkUnmapMemory(device, stagingBufferMemory);
//
//        //stbi_image_free(pixels);
//
//        //createImage(texWidth, texHeight, mipLevels, VK_SAMPLE_COUNT_1_BIT, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, textureImage, textureImageMemory);
//
//        //transitionImageLayout(textureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, mipLevels);
//        //copyBufferToImage(stagingBuffer, textureImage, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));
//        ////transitioned to VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL while generating mipmaps
//
//        //vkDestroyBuffer(device, stagingBuffer, nullptr);
//        //vkFreeMemory(device, stagingBufferMemory, nullptr);
//
//        //generateMipmaps(textureImage, VK_FORMAT_R8G8B8A8_UNORM, texWidth, texHeight, mipLevels);
//    }
//
//    void createTextureImageView() {
//        textureImageView = createImageView(textureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_ASPECT_COLOR_BIT, mipLevels);
//    }
//
//    void createTextureSampler() {
//        //VkSamplerCreateInfo samplerInfo = {};
//        ////samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
//        //samplerInfo.magFilter = VK_FILTER_LINEAR;
//        //samplerInfo.minFilter = VK_FILTER_LINEAR;
//        //samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
//        //samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
//        //samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
//        //samplerInfo.anisotropyEnable = VK_TRUE;
//        //samplerInfo.maxAnisotropy = 16;
//        //samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
//        //samplerInfo.unnormalizedCoordinates = VK_FALSE;
//        //samplerInfo.compareEnable = VK_FALSE;
//        //samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;
//        //samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
//        //samplerInfo.minLod = 0;
//        //samplerInfo.maxLod = static_cast<float>(mipLevels);
//        //samplerInfo.mipLodBias = 0;
//
//        //if (vkCreateSampler(device, &samplerInfo, nullptr, &textureSampler) != VK_SUCCESS) {
//        //    throw std::runtime_error("failed to create texture sampler!");
//        //}
//    }
//
//    VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels) {
//        //VkImageViewCreateInfo viewInfo = {};
//        //viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
//        //viewInfo.image = image;
//        //viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
//        //viewInfo.format = format;
//        //viewInfo.subresourceRange.aspectMask = aspectFlags;
//        //viewInfo.subresourceRange.baseMipLevel = 0;
//        //viewInfo.subresourceRange.levelCount = mipLevels;
//        //viewInfo.subresourceRange.baseArrayLayer = 0;
//        //viewInfo.subresourceRange.layerCount = 1;
//
//        //VkImageView imageView;
//        //if (vkCreateImageView(device, &viewInfo, nullptr, &imageView) != VK_SUCCESS) {
//        //    throw std::runtime_error("failed to create texture image view!");
//        //}
//
//        //return imageView;
//    }
//
//    void createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory) {
//        //VkImageCreateInfo imageInfo = {};
//        //imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
//        //imageInfo.imageType = VK_IMAGE_TYPE_2D;
//        //imageInfo.extent.width = width;
//        //imageInfo.extent.height = height;
//        //imageInfo.extent.depth = 1;
//        //imageInfo.mipLevels = mipLevels;
//        //imageInfo.arrayLayers = 1;
//        //imageInfo.format = format;
//        //imageInfo.tiling = tiling;
//        //imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
//        //imageInfo.usage = usage;
//        //imageInfo.samples = numSamples;
//        //imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
//
//        //if (vkCreateImage(device, &imageInfo, nullptr, &image) != VK_SUCCESS) {
//        //    throw std::runtime_error("failed to create image!");
//        //}
//
//        //VkMemoryRequirements memRequirements;
//        //vkGetImageMemoryRequirements(device, image, &memRequirements);
//
//        //VkMemoryAllocateInfo allocInfo = {};
//        //allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
//        //allocInfo.allocationSize = memRequirements.size;
//        //allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);
//
//        //if (vkAllocateMemory(device, &allocInfo, nullptr, &imageMemory) != VK_SUCCESS) {
//        //    throw std::runtime_error("failed to allocate image memory!");
//        //}
//
//        //vkBindImageMemory(device, image, imageMemory, 0);
//    }
//
//    void loadModel() {
//        //tinyobj::attrib_t attrib;
//        //std::vector<tinyobj::shape_t> shapes;
//        //std::vector<tinyobj::material_t> materials;
//        //std::string warn, err;
//
//        //if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, MODEL_PATH.c_str())) {
//        //    throw std::runtime_error(warn + err);
//        //}
//
//        //std::unordered_map<Vertex, uint32_t> uniqueVertices = {};
//
//        //for (const auto& shape : shapes) {
//        //    for (const auto& index : shape.mesh.indices) {
//        //        Vertex vertex = {};
//
//        //        vertex.pos = {
//        //            attrib.vertices[3 * index.vertex_index + 0],
//        //            attrib.vertices[3 * index.vertex_index + 1],
//        //            attrib.vertices[3 * index.vertex_index + 2]
//        //        };
//
//        //        vertex.texCoord = {
//        //            attrib.texcoords[2 * index.texcoord_index + 0],
//        //            1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
//        //        };
//
//        //        vertex.color = { 1.0f, 1.0f, 1.0f };
//
//        //        if (uniqueVertices.count(vertex) == 0) {
//        //            uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
//        //            vertices.push_back(vertex);
//        //        }
//
//        //        indices.push_back(uniqueVertices[vertex]);
//        //    }
//        //}
//    }
//
//    void createVertexBuffer() {
//        //VkDeviceSize bufferSize = sizeof(vertices[0]) * vertices.size();
//
//        //VkBuffer stagingBuffer;
//        //VkDeviceMemory stagingBufferMemory;
//        //createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);
//
//        //void* data;
//        //vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
//        //memcpy(data, vertices.data(), (size_t)bufferSize);
//        //vkUnmapMemory(device, stagingBufferMemory);
//
//        //createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);
//
//        //copyBuffer(stagingBuffer, vertexBuffer, bufferSize);
//
//        //vkDestroyBuffer(device, stagingBuffer, nullptr);
//        //vkFreeMemory(device, stagingBufferMemory, nullptr);
//    }
//
//    void createIndexBuffer() {
//        //VkDeviceSize bufferSize = sizeof(indices[0]) * indices.size();
//
//        //VkBuffer stagingBuffer;
//        //VkDeviceMemory stagingBufferMemory;
//        //createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);
//
//        //void* data;
//        //vkMapMemory(device, stagingBufferMemory, 0, bufferSize, 0, &data);
//        //memcpy(data, indices.data(), (size_t)bufferSize);
//        //vkUnmapMemory(device, stagingBufferMemory);
//
//        //createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);
//
//        //copyBuffer(stagingBuffer, indexBuffer, bufferSize);
//
//        //vkDestroyBuffer(device, stagingBuffer, nullptr);
//        //vkFreeMemory(device, stagingBufferMemory, nullptr);
//    }
//
//    void createUniformBuffers() {
//        //VkDeviceSize bufferSize = sizeof(UniformBufferObject);
//
//        //uniformBuffers.resize(swapChainImages.size());
//        //uniformBuffersMemory.resize(swapChainImages.size());
//
//        //for (size_t i = 0; i < swapChainImages.size(); i++) {
//        //    createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffers[i], uniformBuffersMemory[i]);
//        //}
//    }
//
//    void createDescriptorPool() {
//        //std::array<VkDescriptorPoolSize, 2> poolSizes = {};
//        //poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
//        //poolSizes[0].descriptorCount = static_cast<uint32_t>(swapChainImages.size());
//        //poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
//        //poolSizes[1].descriptorCount = static_cast<uint32_t>(swapChainImages.size());
//
//        //VkDescriptorPoolCreateInfo poolInfo = {};
//        //poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
//        //poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
//        //poolInfo.pPoolSizes = poolSizes.data();
//        //poolInfo.maxSets = static_cast<uint32_t>(swapChainImages.size());
//
//        //if (vkCreateDescriptorPool(device, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS) {
//        //    throw std::runtime_error("failed to create descriptor pool!");
//        //}
//    }
//
//    void createDescriptorSets() {
//        //std::vector<VkDescriptorSetLayout> layouts(swapChainImages.size(), descriptorSetLayout);
//        //VkDescriptorSetAllocateInfo allocInfo = {};
//        //allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
//        //allocInfo.descriptorPool = descriptorPool;
//        //allocInfo.descriptorSetCount = static_cast<uint32_t>(swapChainImages.size());
//        //allocInfo.pSetLayouts = layouts.data();
//
//        //descriptorSets.resize(swapChainImages.size());
//        //if (vkAllocateDescriptorSets(device, &allocInfo, descriptorSets.data()) != VK_SUCCESS) {
//        //    throw std::runtime_error("failed to allocate descriptor sets!");
//        //}
//
//        //for (size_t i = 0; i < swapChainImages.size(); i++) {
//        //    VkDescriptorBufferInfo bufferInfo = {};
//        //    bufferInfo.buffer = uniformBuffers[i];
//        //    bufferInfo.offset = 0;
//        //    bufferInfo.range = sizeof(UniformBufferObject);
//
//        //    VkDescriptorImageInfo imageInfo = {};
//        //    imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
//        //    imageInfo.imageView = textureImageView;
//        //    imageInfo.sampler = textureSampler;
//
//        //    std::array<VkWriteDescriptorSet, 2> descriptorWrites = {};
//
//        //    descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
//        //    descriptorWrites[0].dstSet = descriptorSets[i];
//        //    descriptorWrites[0].dstBinding = 0;
//        //    descriptorWrites[0].dstArrayElement = 0;
//        //    descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
//        //    descriptorWrites[0].descriptorCount = 1;
//        //    descriptorWrites[0].pBufferInfo = &bufferInfo;
//
//        //    descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
//        //    descriptorWrites[1].dstSet = descriptorSets[i];
//        //    descriptorWrites[1].dstBinding = 1;
//        //    descriptorWrites[1].dstArrayElement = 0;
//        //    descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
//        //    descriptorWrites[1].descriptorCount = 1;
//        //    descriptorWrites[1].pImageInfo = &imageInfo;
//
//        //    vkUpdateDescriptorSets(device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
//        //}
//    }
//
//    //void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory) {
//    //    VkBufferCreateInfo bufferInfo = {};
//    //    bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
//    //    bufferInfo.size = size;
//    //    bufferInfo.usage = usage;
//    //    bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
//
//    //    if (vkCreateBuffer(device, &bufferInfo, nullptr, &buffer) != VK_SUCCESS) {
//    //        throw std::runtime_error("failed to create buffer!");
//    //    }
//
//    //    VkMemoryRequirements memRequirements;
//    //    vkGetBufferMemoryRequirements(device, buffer, &memRequirements);
//
//    //    VkMemoryAllocateInfo allocInfo = {};
//    //    allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
//    //    allocInfo.allocationSize = memRequirements.size;
//    //    allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);
//
//    //    if (vkAllocateMemory(device, &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS) {
//    //        throw std::runtime_error("failed to allocate buffer memory!");
//    //    }
//
//    //    vkBindBufferMemory(device, buffer, bufferMemory, 0);
//    //}
//
//    //VkCommandBuffer beginSingleTimeCommands() {
//    //    VkCommandBufferAllocateInfo allocInfo = {};
//    //    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
//    //    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
//    //    allocInfo.commandPool = commandPool;
//    //    allocInfo.commandBufferCount = 1;
//
//    //    VkCommandBuffer commandBuffer;
//    //    vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer);
//
//    //    VkCommandBufferBeginInfo beginInfo = {};
//    //    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
//    //    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
//
//    //    vkBeginCommandBuffer(commandBuffer, &beginInfo);
//
//    //    return commandBuffer;
//    //}
//
//    //void endSingleTimeCommands(VkCommandBuffer commandBuffer) {
//    //    vkEndCommandBuffer(commandBuffer);
//
//    //    VkSubmitInfo submitInfo = {};
//    //    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
//    //    submitInfo.commandBufferCount = 1;
//    //    submitInfo.pCommandBuffers = &commandBuffer;
//
//    //    vkQueueSubmit(graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
//    //    vkQueueWaitIdle(graphicsQueue);
//
//    //    vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
//    //}
//
//    //void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size) {
//    //    VkCommandBuffer commandBuffer = beginSingleTimeCommands();
//
//    //    VkBufferCopy copyRegion = {};
//    //    copyRegion.size = size;
//    //    vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);
//
//    //    endSingleTimeCommands(commandBuffer);
//    //}
//
//
//    void createCommandBuffers() {
//        //commandBuffers.resize(swapChainFramebuffers.size());
//
//        //VkCommandBufferAllocateInfo allocInfo = {};
//        //allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
//        //allocInfo.commandPool = commandPool;
//        //allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
//        //allocInfo.commandBufferCount = (uint32_t)commandBuffers.size();
//
//        //if (vkAllocateCommandBuffers(device, &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
//        //    throw std::runtime_error("failed to allocate command buffers!");
//        //}
//
//        //for (size_t i = 0; i < commandBuffers.size(); i++) {
//        //    VkCommandBufferBeginInfo beginInfo = {};
//        //    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
//
//        //    if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS) {
//        //        throw std::runtime_error("failed to begin recording command buffer!");
//        //    }
//
//        //    VkRenderPassBeginInfo renderPassInfo = {};
//        //    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
//        //    renderPassInfo.renderPass = renderPass;
//        //    renderPassInfo.framebuffer = swapChainFramebuffers[i];
//        //    renderPassInfo.renderArea.offset = { 0, 0 };
//        //    renderPassInfo.renderArea.extent = swapChainExtent;
//
//        //    std::array<VkClearValue, 2> clearValues = {};
//        //    clearValues[0].color = { 0.0f, 0.0f, 0.0f, 1.0f };
//        //    clearValues[1].depthStencil = { 1.0f, 0 };
//
//        //    renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
//        //    renderPassInfo.pClearValues = clearValues.data();
//
//        //    vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
//
//        //    vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, graphicsPipeline);
//
//        //    VkBuffer vertexBuffers[] = { vertexBuffer };
//        //    VkDeviceSize offsets[] = { 0 };
//        //    vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, vertexBuffers, offsets);
//
//        //    vkCmdBindIndexBuffer(commandBuffers[i], indexBuffer, 0, VK_INDEX_TYPE_UINT32);
//
//        //    vkCmdBindDescriptorSets(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, pipelineLayout, 0, 1, &descriptorSets[i], 0, nullptr);
//
//        //    vkCmdDrawIndexed(commandBuffers[i], static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);
//
//        //    vkCmdEndRenderPass(commandBuffers[i]);
//
//        //    if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
//        //        throw std::runtime_error("failed to record command buffer!");
//        //    }
//        //}
//    }
//
//    void createSyncObjects() {
//        //imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
//        //renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
//        //inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
//
//        //VkSemaphoreCreateInfo semaphoreInfo = {};
//        //semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
//
//        //VkFenceCreateInfo fenceInfo = {};
//        //fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
//        //fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
//
//        //for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
//        //    if (vkCreateSemaphore(device, &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
//        //        vkCreateSemaphore(device, &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS ||
//        //        vkCreateFence(device, &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS) {
//        //        throw std::runtime_error("failed to create synchronization objects for a frame!");
//        //    }
//        //}
//    }
//
//    void updateUniformBuffer(uint32_t currentImage) {
//        //static auto startTime = std::chrono::high_resolution_clock::now();
//
//        //auto currentTime = std::chrono::high_resolution_clock::now();
//        //float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
//
//        //UniformBufferObject ubo = {};
//        //ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
//        //ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
//        //ubo.proj = glm::perspective(glm::radians(45.0f), swapChainExtent.width / (float)swapChainExtent.height, 0.1f, 10.0f);
//        //ubo.proj[1][1] *= -1;
//
//        //void* data;
//        //vkMapMemory(device, uniformBuffersMemory[currentImage], 0, sizeof(ubo), 0, &data);
//        //memcpy(data, &ubo, sizeof(ubo));
//        //vkUnmapMemory(device, uniformBuffersMemory[currentImage]);
//    }
//
//    //void drawFrame() {
//    //}
//
//    //VkShaderModule createShaderModule(const std::vector<char>& code) {
//        //VkShaderModuleCreateInfo createInfo = {};
//        //createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
//        //createInfo.codeSize = code.size();
//        //createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());
//
//        //VkShaderModule shaderModule;
//        //if (vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
//        //    throw std::runtime_error("failed to create shader module!");
//        //}
//
//        //return shaderModule;
//    //}
//
//    //static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
//    //    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;
//
//    //    return VK_FALSE;
//    //}
//};
/*

int main() {
    auto app = new HelloTriangleApplication();

    try {
        app.run();
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}*/