#include "../include/shader.hpp"

#include <fstream>
#include <vector>

static uint32_t create_shader(const char* path, GLenum shader_type);

namespace te {
    Shader::Shader() {
        uint32_t vertex_shader = create_shader("shaders/shader.vert.spv", GL_VERTEX_SHADER);
        uint32_t fragment_shader = create_shader("shaders/shader.frag.spv", GL_FRAGMENT_SHADER);

        _handle = glCreateProgram();

        glAttachShader(_handle, vertex_shader);
        glAttachShader(_handle, fragment_shader);

        glLinkProgram(_handle);

        int success = 0;
        glGetProgramiv(_handle, GL_LINK_STATUS, &success);
        if(success == GL_FALSE) {
            int32_t max_length = 0;
            glGetProgramiv(_handle, GL_INFO_LOG_LENGTH, &max_length);

            std::vector<char> error(max_length);
            glGetProgramInfoLog(_handle, max_length, &max_length, error.data());
            printf("%s\n", error.data());

            glDeleteShader(vertex_shader);
            glDeleteShader(fragment_shader);

            exit(EXIT_FAILURE);
        }

        glUseProgram(_handle);

        _global_uniform_buffer = new UniformBuffer(_handle);

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
    }

    Shader::~Shader() {
        glDeleteProgram(_handle);

        free(_global_uniform_buffer);
    }

    void Shader::UpdateState(vec2 pixelSize, vec2 origin) {
        _global_uniform_object.pixelSize = pixelSize;
        _global_uniform_object.origin = origin;

        _global_uniform_buffer->Update(_global_uniform_object);
    }

    void Shader::UpdateWorldSpace(vec2 model) {
        _global_uniform_object.model = model;

        _global_uniform_buffer->Update(_global_uniform_object);
    }
}

static void load_spirv_module(const char* path, std::vector<char>* module_out);

static uint32_t create_shader(const char* path, GLenum shader_type) {
    uint32_t shader = glCreateShader(shader_type);

    std::vector<char> shader_module;
    load_spirv_module(path, &shader_module);

    glShaderBinary(1, &shader, GL_SHADER_BINARY_FORMAT_SPIR_V_ARB, shader_module.data(), shader_module.size());

    /* "Compile" the shader */
    glSpecializeShaderARB(shader, "main", 0, NULL, NULL);

    /* Error handling */
    int32_t success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(success == GL_FALSE) {
	int32_t max_length = 0;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_length);

	std::vector<char> error(max_length);
	glGetShaderInfoLog(shader, max_length, &max_length, error.data());
	printf("%s\n", error.data());
	
	glDeleteShader(shader);

	exit(EXIT_FAILURE);
    }

    return shader;
}

static void load_spirv_module(const char* path, std::vector<char>* module_out) {
    /* Open binary file */
    std::ifstream fp(path, std::ios::ate | std::ios::binary);

    if(!fp.is_open()) {
        fprintf(stderr, "Shader: Failed to find shader at \"%s\"", path);
        exit(EXIT_FAILURE);
    }

    /* Get file size and resize buffer */
    size_t size = fp.tellg();
    module_out->resize(size);

    /* Reset cursor */
    fp.seekg(0);

    /* Put file contents into buffer */
    fp.read(module_out->data(), size);
    
    fp.close();
}
