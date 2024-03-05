#include "../include/application.hpp"
#include "../include/buffer.hpp"
#include "../include/math_types.hpp"
#include "../include/shader.hpp"

namespace te{
    Application::Application(std::string title, int width, int height) : _window(std::move(title), width, height){
    }

    Application::~Application(){
        std::cout << "Application Terminated\n";
    }

    void Application::Run(){
        _renderer.Draw();
    }
}
