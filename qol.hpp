#include <GLFW/glfw3.h>
#include <OpenGL/glu.h>

#include <fstream>
#include <iostream>
#include <string>
#include <thread>
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

namespace qol {

void runpy() { system("python3 graph.py"); }

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

void displayUiText(double x, double y, std::string message) {
    glRasterPos2f(x, y);
    glColor3d(1., 1., 1.);

    for (int i = 0; i < message.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
    }
}

void removeDataFile(const char *filename) { remove(filename); }

void saveData(double time, const sim::state st) {
    std::ofstream myfile("data.txt", std::ios::out | std::ios::app);

    myfile << time << " " << st.theta.first * 180 / M_PI << " " << st.theta.second * 180 / M_PI << "\n";

    myfile.close();
}

}  // namespace qol