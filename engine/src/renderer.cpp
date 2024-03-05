#include "../include/renderer.hpp"
#include "../include/buffer.hpp"
#include "../include/math_types.hpp"
#include "../include/shader.hpp"
#include "../include/window.hpp"

namespace te{
    Renderer::Renderer(){
        uint32_t vertex_shader = create_shader("vert.spv", GL_VERTEX_SHADER);
        uint32_t frag_shader = create_shader("frag.spv", GL_FRAGMENT_SHADER);

        /* Create shader program */
        shader_program = glCreateProgram();

        /* Attach shaders to shader program */
        glAttachShader(shader_program, vertex_shader);
        glAttachShader(shader_program, frag_shader);

        /* Link program to renderer */
        glLinkProgram(shader_program);

        /* Error handling */
        int success = 0;
        glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
        if(success == GL_FALSE) {
            int32_t max_length = 0;
            glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &max_length);

            std::vector<char> error(max_length);
            glGetProgramInfoLog(shader_program, max_length, &max_length, error.data());
            printf("%s\n", error.data());

            glDeleteShader(vertex_shader);
            glDeleteShader(frag_shader);

            exit(EXIT_FAILURE);
        }

        /* Tell opengl to use our shader */
        glUseProgram(shader_program);

        _global_uniform_buffer = new UniformBuffer(shader_program);

        /* Cleanup */
        glDeleteShader(vertex_shader);
        glDeleteShader(frag_shader);

    }

    Renderer::~Renderer(){
        glDeleteProgram(shader_program);

        free(_global_uniform_buffer);
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

        _global_uniform_object = {model, pixelSize, origin};

        while(!window.ShouldClose()){
	    	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	    	glClear(GL_COLOR_BUFFER_BIT);

            _global_uniform_buffer->Update(_global_uniform_object);

            vertex_buffer.Bind();

            index_buffer.Draw();

	    	glfwSwapBuffers(window.Get());
	    	glfwPollEvents();
        }
    }
}
