#ifndef TE_APPLICATION_HPP
#define TE_APPLICATION_HPP

#include <memory>
#include <string>

#include "window.hpp"
#include "renderer.hpp"

namespace te{
    class Application : NoCopy{
    public:
        static std::unique_ptr<Application> Create(std::string title, int width, int height);

        ~Application();

        void Run();
        void Update();
        void Render();

    private:
        static inline Application* app = nullptr;

        Application(std::string title, int width, int height);

        Window _window;
        Renderer _renderer{&_window};
    };

    inline std::unique_ptr<Application> Application::Create(std::string title, int width, int height){
        app = new Application(title, width, height);
        return std::unique_ptr<Application>(app);
    }
}

#endif
