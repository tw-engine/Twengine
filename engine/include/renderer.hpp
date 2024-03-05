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
        Renderer();
        virtual ~Renderer();

        void Draw(Window& window);

        // other

    private:
        Shader _shader;
    };
}

#endif
