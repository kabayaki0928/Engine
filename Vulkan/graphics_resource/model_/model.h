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
        //    // bindbuffer‚Ædraw‚ğ•Ê‚É•ª‚¯‚Ä‚¨‚¢‚½‚Ù‚¤‚ª‚¢‚¢‚©‚à‚µ‚ê‚È‚¢
        //    // prepareH
        //    drawable_buffer_.bindBuffer(commandBuffer);
        //    drawable_buffer_.drawIndices(commandBuffer);
        //}
    };

} // vengine

