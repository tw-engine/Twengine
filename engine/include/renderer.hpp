#ifndef TE_RENDERER_HPP
#define TE_RENDERER_HPP

#include "buffer.hpp"
#include "common.hpp"
#include "math_types.hpp"
#include "window.hpp"

namespace te{
    class Renderer : NoCopy{
    public:
        Renderer();
        virtual ~Renderer();

        void Draw(Window& window);

        // other

    private:
        uint32_t shader_program; /* TODO: Make shader class so its initialized before uniform buffer  */

        UniformBuffer* _global_uniform_buffer;
        UBO _global_uniform_object;
    };
}

#endif
