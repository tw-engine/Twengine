#include "../include/application.hpp"
#include "../include/buffer.hpp"
#include "../include/math_types.hpp"
#include "../include/shader.hpp"

namespace te{
    Application::Application(std::string title, int width, int height) : _window(std::move(title), width, height){
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_FALSE); // disables all debugs
        glDebugMessageControl(GL_DONT_CARE, GL_DEBUG_TYPE_ERROR, GL_DONT_CARE, 0, nullptr, GL_TRUE); // Only enables errors

        glDebugMessageCallback(_OGLDebugMessageCallback, 0);
    }

    Application::~Application(){
        std::cout << "Application Terminated\n";
    }

    void Application::Render(){
        _renderer.Draw();
    }

    void Application::Update(){

    }

    void Application::_OGLDebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam){
        fprintf(stderr, "\nGL CALLBACK: %s\ntype: 0x%x\nSeverity: 0x%x\nMessage: %s\n\n", (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
    }
}
