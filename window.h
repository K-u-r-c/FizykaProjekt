#pragma once

#include <GLFW/glfw3.h>

class Window {
   private:
    GLFWwindow* window;
    int width, height;

   public:
    GLFWwindow* getWindow();
    int getWidth();
    int getHeight();

    Window(int width, int height, const char* title);
    ~Window();
};