#include <GLFW/glfw3.h>
#include <OpenGL/glu.h>

#include <iostream>
#include <string>
#include <utility>

#include "simulation.hpp"

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

template <typename... Args>
void print(Args &&...args) {
    (std::cout << ... << args) << std::endl;
}

template <typename... Args>
void read(Args &...args) {
    (std::cin >> ... >> args);
}

namespace keys {

void handleKeyInput(GLFWwindow *window, sim::system &ss) {
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS))
        ss.length.first += 1;
    else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        ss.length.first += 5;
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS))
        ss.length.first -= 1;
    else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        ss.length.first -= 5;

    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS))
        ss.length.second += 1;
    else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        ss.length.second += 5;
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS))
        ss.length.second -= 1;
    else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        ss.length.second -= 5;

    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS))
        ss.mass.first += 0.05;
    else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        ss.mass.first += 1;
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS))
        ss.mass.first -= 0.05;
    else if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        ss.mass.first -= 1;

    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS))
        ss.mass.second += 0.05;
    else if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        ss.mass.second += 1;
    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS))
        ss.mass.second -= 0.05;
    else if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        ss.mass.second -= 1;
}

}  // namespace keys