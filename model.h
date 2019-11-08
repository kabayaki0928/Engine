#ifndef MODELH
#define MODELH

#include "iloadable_resource.h"

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
        //    // bindbufferとdrawを別に分けておいたほうがいいかもしれない
        //    // prepare？
        //    drawable_buffer_.bindBuffer(commandBuffer);
        //    drawable_buffer_.drawIndices(commandBuffer);
        //}
    };

} // vengine
#endif

