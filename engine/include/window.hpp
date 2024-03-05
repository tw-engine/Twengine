#ifndef TE_WINDOW_HPP
#define TE_WINDOW_HPP

#include <functional>

#include "common.hpp"

namespace te{
    class Window final : NoCopy{
    public:
        ~Window();

        void SetFramebufferSizeCallback(const std::function<void(int width, int height)>& callback);

	    GLFWwindow* Get();

	    bool ShouldClose() const;

		float GetWidth() const;

		float GetHeight() const;

    private:
        friend class Application;
        friend void OnFramebufferSizeChange(GLFWwindow* glfwWin, int width, int height);

        Window(const std::string& title, int width, int height);

        int width, height;

        GLFWwindow* handle;
        std::function<void(int width, int height)> framebufferSizeCallback = nullptr;

        static void OnFramebufferSizeChange(GLFWwindow* glfwWindow, int width, int height);

        static inline Window* window = nullptr;
    };
}

#endif
