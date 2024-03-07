#include "../include/window.hpp"

namespace te{
    static void glfw_error_callback(int error, const char* message){
        fprintf(stderr, "GLFW Error %d: %s\n", error, message);
    }

    Window::Window(const std::string& _title, int _width, int _height, int FPS) : width(_width), height(_height){
        window = this;
        
        glfwSetErrorCallback(glfw_error_callback);

        if(!glfwInit()){
            const char* message;
            glfwGetError(&message);
            printf("GLFW initialization error: %s\n", message);
            exit(1);
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

        handle = glfwCreateWindow(width, height, _title.c_str(), nullptr, nullptr);
        if(!handle){
            printf("GLFW failed window creation");
            glfwTerminate();
            exit(1);
        }

        const GLFWvidmode* vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        glfwSetWindowMonitor(handle, nullptr, (vidmode->width / 2) - (width / 2), (vidmode->height / 2) - (height / 2), width, height, (FPS == -1 ? GL_DONT_CARE : FPS));

        glfwMakeContextCurrent(handle);
        glfwSwapInterval(0); // no vsync

        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
            printf("GLAD failed initialization");
            glfwTerminate();
            exit(1);
        }

        const char* version = (const char*)glGetString(GL_VERSION);
        printf("OpenGL Version: %s\n", version);

        glfwSetFramebufferSizeCallback(handle, OnFramebufferSizeChange);
    }

    Window::~Window(){
        glfwDestroyWindow(handle);
        glfwTerminate();
    }

    GLFWwindow* Window::Get() const{
	return window->handle;
    }

    void Window::OnFramebufferSizeChange(GLFWwindow* glfwWindow, int width, int height){
        window->width = width;
        window->height = height;

        if(window->framebufferSizeCallback != nullptr)
            window->framebufferSizeCallback(width, height);

		glViewport(0, 0, width, height);
    }

    void Window::SetFramebufferSizeCallback(const std::function<void(int width, int height)>& callback){
        framebufferSizeCallback = callback;
    }

    bool Window::ShouldClose() const{
        return glfwWindowShouldClose(handle);
    }

	float Window::GetWidth() const{
		return width;
	}

	float Window::GetHeight() const{
		return height;
	}
}
