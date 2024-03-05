#ifndef TE_RENDERER_HPP
#define TE_RENDERER_HPP

#include "buffer.hpp"
#include "common.hpp"
#include "math_types.hpp"
#include "shader.hpp"
#include "window.hpp"

namespace te{
    class Renderer : NoCopy{
    public:
        Renderer(const Window* window);
        virtual ~Renderer();

        void Draw();

        // other

    private:
        const Window* _window_ptr = NULL;
        Shader _shader;
    };
}

#endif
