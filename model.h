#pragma once

namespace rengine
{
    class DrawableBuffer;
    class Material;

    class Model final
    {
    private:
        std::shared_ptr<DrawableBuffer> drawable_buffer_;
        std::shared_ptr<Material> material_;
    public:
        Model
        (
            std::shared_ptr<DrawableBuffer> const drawable_buffer,
            std::shared_ptr<Material> material
        );
        ~Model();

        //void draw(VkCommandBuffer commandBuffer) {
        //    // bindbufferとdrawを別に分けておいたほうがいいかもしれない
        //    // prepare？
        //    drawable_buffer_.bindBuffer(commandBuffer);
        //    drawable_buffer_.drawIndices(commandBuffer);
        //}
    };

} // vengine

