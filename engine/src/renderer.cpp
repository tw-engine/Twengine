#include "../include/renderer.hpp"
#include "../include/buffer.hpp"
#include "../include/math_types.hpp"
#include "../include/shader.hpp"
#include "../include/window.hpp"
#include "../include/sprite.hpp"

namespace te{
    Renderer::Renderer(const Window* window){
        _window_ptr = window;
    }

    Renderer::~Renderer(){
    }

    void Renderer::Draw() {
		Vertex vertices[] = {
	    	{{150.0f, 150.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
	    	{{150.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
	    	{{0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
	    	{{0.0f, 150.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
		};

		uint32_t indices[] = {
	    	0, 1, 3,
	    	1, 2, 3
		};

        VertexBuffer vertex_buffer(sizeof(vertices), vertices);

        IndexBuffer index_buffer(sizeof(indices) / sizeof(indices[0]), indices);
        
		Sprite aSprite(&vertex_buffer, &index_buffer);
		aSprite.LoadTexture("textures/newpfp.png", GL_RGBA, GL_RGBA);

		/* Configure uniform buffer object */
		vec2 model = {0.0f, 0.0f};
		vec2 pixelSize = {2.0f / _window_ptr->GetWidth(), 2.0f / _window_ptr->GetHeight()};
		vec2 origin = {_window_ptr->GetWidth()/2, _window_ptr->GetHeight()/2};

        while(!_window_ptr->ShouldClose()){
	    	glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
	    	glClear(GL_COLOR_BUFFER_BIT);

			pixelSize = {2.0f / _window_ptr->GetWidth(), 2.0f / _window_ptr->GetHeight()};
			origin = {_window_ptr->GetWidth()/2, _window_ptr->GetHeight()/2};
            _shader.UpdateState(pixelSize, origin); /* Todo: Should only get updated on window resize */

            _shader.UpdateWorldSpace(model);

			aSprite.Draw();

	    	glfwSwapBuffers(_window_ptr->Get());
	    	glfwPollEvents();
        }
    }
}
