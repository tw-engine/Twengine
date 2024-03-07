#ifndef TE_APPLICATION_HPP
#define TE_APPLICATION_HPP

#include <memory>
#include <string>

#include "window.hpp"
#include "renderer.hpp"

namespace te{
    class Application : NoCopy{
    public:
        static std::unique_ptr<Application> Create(std::string title, int width, int height, int FPS);

        ~Application();

        void Update();
        void Render();

        inline bool IsRunning() { return !_window.ShouldClose(); }

    private:
        static inline Application* app = nullptr;

        Application(std::string title, int width, int height, int FPS);

        static void _OGLDebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam);

        Window _window;
        Renderer _renderer{&_window};
    };

    inline std::unique_ptr<Application> Application::Create(std::string title, int width, int height, int FPS){
        app = new Application(title, width, height, FPS);
        return std::unique_ptr<Application>(app);
    }
}

#endif
