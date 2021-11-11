// clang++ -std=c++20 main.cpp -o program.out -lglfw -framework OpenGL -Wno-deprecated-declarations

#include <GLFW/glfw3.h>
#include <OpenGL/glu.h>

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include <random>

#include "simulation.hpp"

void sphere(const std::pair<double, double>& center, double radius) {
    const int segments = 200;

    double delta = M_PI * 2 / segments;
    double c = cos(delta);
    double s = sin(delta);

    std::pair<double, double> xy(radius, 0);
    glColor3d(1, 1, 1);
    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < segments; ++i) {
        glVertex2d(xy.first + center.first, xy.second + center.second);
        glVertex2d(center.first, center.second);

        xy = {c * xy.first - s * xy.second, s * xy.first + c * xy.second};
    }

    glEnd();
}

void loop(GLFWwindow* window, std::pair<int, int>& dimensions) {
    sim::angles_st st{{1.0, 1.0}, {0, 0}};  // theta

    double length = dimensions.first / 2.5f;

    sim::sphere_ss ss{{0.5, 0.5}, {length, length}};

    glLineWidth(4);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_LINE_STRIP);
        glColor3d(1, 0, 0);
        glVertex2d(0, 0);

        std::pair<double, double> first_line{ss.length.first * sin(st.theta.first), ss.length.first * cos(st.theta.first)};
        glVertex2d(first_line.first / dimensions.first, -first_line.second / dimensions.second);

        std::pair<double, double> second_line{first_line.first + ss.length.second * sin(st.theta.second),
                                              first_line.second + ss.length.second * cos(st.theta.second)};
        glVertex2d(second_line.first / dimensions.first, -second_line.second / dimensions.second);

        glEnd();

        if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) ss.length.first += 5;
        if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS) ss.length.first -= 5;

        if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS) ss.length.second += 5;
        if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS) ss.length.second -= 5;

        sphere({0, 0}, 0.03);

        sphere({first_line.first / dimensions.first, -first_line.second / dimensions.second}, 0.03);

        sphere({second_line.first / dimensions.first, -second_line.second / dimensions.second}, 0.03);

        st = sim::update(st, ss, 0.2);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

int main() {
    std::pair<int, int> dimensions{1000, 1000};

    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    auto window = glfwCreateWindow(dimensions.first / 2, dimensions.second / 2, "Podwojne wachadlo", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);
    glViewport(0, 0, dimensions.first, dimensions.second);
    glClearColor(0.2, 0.2, 0.2, 0);

    loop(window, dimensions);

    glfwDestroyWindow(window);
    glfwTerminate();
}