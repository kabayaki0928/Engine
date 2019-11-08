#include "stdafx.h"
#include "vulkan_sample_loop01.h"

#include "vulkan_graphics_backend.h"
#include "vulkan_render_pipeline.h"
#include "simple_main_code.h"

#include "user_define.h"

namespace vengine
{
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    VulkanSampleLoop01::VulkanSampleLoop01()
    : graphics_backend_(std::make_shared<VulkanGraphicsBackend>("test", "vulkan", user_define::WIDTH, user_define::HEIGHT)),
      render_pipeline_(std::make_unique<IRenderPipeline>(new VulkanRenderPipeline(graphics_backend_))),
      main_code_(std::make_unique<IMainCode>(new SimpleMainCode(graphics_backend_))) {
        // note
        /*
        �b��ŃR���X�g���N�^�̓�����new����悤�ɂ������̂́ASimpleMainLoop�ł܂��Ȃ������Ȋ�������
        �T���v���𓮂������߂ɃN���X���������̂͂�����Ɩ��ʊ�������̂ŗv�čl
        */
    }

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    VulkanSampleLoop01::~VulkanSampleLoop01() {
    }

    /// <summary>
    /// ����������
    /// </summary>
    void VulkanSampleLoop01::initialize() {
        graphics_backend_->initialize();
        main_code_->initialize();
    }

    /// <summary>
    /// ���s
    /// </summary>
    void VulkanSampleLoop01::run() {
        main_code_->update();
        while (!graphics_backend_->getWindow()->isShouldClose()) {
            main_code_->prepareDraw();
            render_pipeline_->draw();
            main_code_->lateDraw();
        }
    }
} // vengine
