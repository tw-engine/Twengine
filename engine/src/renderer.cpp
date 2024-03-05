#include "../include/renderer.hpp"
#include "../include/buffer.hpp"
#include "../include/math_types.hpp"
#include "../include/shader.hpp"
#include "../include/window.hpp"

namespace te{
    Renderer::Renderer(const Window* window){
        _window_ptr = window;
    }

    Renderer::~Renderer(){
    }

    void Renderer::Draw() {
		Vertex vertices[] = {
	    	{{50.0f, 50.0f}, {1.0f, 1.0f, 1.0f}},
	    	{{50.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
	    	{{0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}},
	    	{{0.0f, 50.0f}, {1.0f, 1.0f, 1.0f}},
		};

		uint32_t indices[] = {
	    	0, 1, 3,
	    	1, 2, 3
		};

        VertexBuffer vertex_buffer(sizeof(vertices), vertices);

        IndexBuffer index_buffer(sizeof(indices) / sizeof(indices[0]), indices);
        
		/* Configure uniform buffer object */
		vec2 model = {0.0f, 0.0f};
		vec2 pixelSize = {2.0f / _window_ptr->GetWidth(), 2.0f / _window_ptr->GetHeight() * -1.f};
		vec2 origin = {_window_ptr->GetWidth()/2, _window_ptr->GetHeight()/2};

        while(!_window_ptr->ShouldClose()){
	    	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	    	glClear(GL_COLOR_BUFFER_BIT);

            _shader.UpdateState(pixelSize, origin); /* Todo: Should only get updated on window resize */

            _shader.UpdateWorldSpace(model);

            vertex_buffer.Bind();

            index_buffer.Draw();

	    	glfwSwapBuffers(_window_ptr->Get());
	    	glfwPollEvents();
        }
    }
}
