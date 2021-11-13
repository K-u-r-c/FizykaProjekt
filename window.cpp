#include "window.h"

Window::Window(int width, int height, const char* title) : width(width), height(height) {
    glfwInit();

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    glfwMakeContextCurrent(window);
}

Window::~Window() { glfwTerminate(); }

GLFWwindow* Window::getWindow() { return window; }
int Window::getWidth() { return width; }
int Window::getHeight() { return height; }