#include "../include/renderer.hpp"
#include "../include/buffer.hpp"
#include "../include/math_types.hpp"
#include "../include/shader.hpp"
#include "../include/window.hpp"

namespace te{
    Renderer::Renderer(){
        
    }

    Renderer::~Renderer(){

    }

    void Renderer::Draw(Window& window) {
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
		vec2 pixelSize = {2.0f / window.GetWidth(), 2.0f / window.GetHeight() * -1.f};
		vec2 origin = {window.GetWidth()/2, window.GetHeight()/2};

        while(!window.ShouldClose()){
	    	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	    	glClear(GL_COLOR_BUFFER_BIT);

            _shader.UpdateState((UBO){model, pixelSize, origin});

            vertex_buffer.Bind();

            index_buffer.Draw();

	    	glfwSwapBuffers(window.Get());
	    	glfwPollEvents();
        }
    }
}
