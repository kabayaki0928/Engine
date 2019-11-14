#ifndef MODELH
#define MODELH

namespace rengine
{
    class DrawableBuffer;
    class Shader;
    class Texture;

    class Model final
    {
    private:
        std::shared_ptr<DrawableBuffer> drawable_buffer_;
        std::vector<std::shared_ptr<Texture>> textures_;
        std::shared_ptr<Shader> shader_;
    public:
        Model
        (
            std::shared_ptr<DrawableBuffer> const drawable_buffer,
            std::vector<std::shared_ptr<Texture>> textures,
            std::shared_ptr<Shader> shader
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
#endif

