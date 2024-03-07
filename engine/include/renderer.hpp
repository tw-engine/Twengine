#ifndef TE_RENDERER_HPP
#define TE_RENDERER_HPP

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

        void SetClearColor(const vec4& color) { _clearColor = color; }

    private:
        const Window* _window_ptr = nullptr;
        Shader _shader;

        vec4 _clearColor{0.0f, 0.0f, 0.0f, 0.0f};
    };
}

#endif
