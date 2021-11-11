// clang++ -std=c++20 main.cpp -o program.out -lglfw -framework OpenGL -Wno-deprecated-declarations
#include "qol.hpp"

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

void loop(GLFWwindow* window, std::pair<int, int>& dimensions, sim::initialValues& initial) {
    sim::state st{{initial.theta1, initial.theta2}, {0, 0}};
    sim::system ss{{initial.mass1, initial.mass2}, {initial.length1, initial.length2}};

    double time = 0;

    qol::saveData(time, st);

    glLineWidth(4);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        qol::displayUiText(-0.98, 0.95, "length1 = " + std::to_string(ss.length.first));
        qol::displayUiText(-0.4, 0.95, "length2 = " + std::to_string(ss.length.second));
        qol::displayUiText(-0.98, 0.9, "mass1 = " + std::to_string(ss.mass.first));
        qol::displayUiText(-0.4, 0.9, "mass2 = " + std::to_string(ss.mass.second));
        qol::displayUiText(-0.98, 0.85, "theta1 = " + std::to_string(std::fmod((st.theta.first * 180) / M_PI, 360)));
        qol::displayUiText(-0.4, 0.85, "theta2 = " + std::to_string(std::fmod((st.theta.second * 180) / M_PI, 360)));
        qol::displayUiText(-0.98, 0.8, "theta_dot1 = " + std::to_string(st.theta_dot.first));
        qol::displayUiText(-0.4, 0.8, "theta_dot2 = " + std::to_string(st.theta_dot.second));

        qol::saveData(time, st);

        glBegin(GL_LINE_STRIP);
        glColor3d(0.7, 0.7, 0.3);
        glVertex2d(0, 0);

        std::pair<double, double> first_line{ss.length.first * sin(st.theta.first), ss.length.first * cos(st.theta.first)};
        glVertex2d(first_line.first / dimensions.first, -first_line.second / dimensions.second);
        std::pair<double, double> second_line{first_line.first + ss.length.second * sin(st.theta.second),
                                              first_line.second + ss.length.second * cos(st.theta.second)};
        glVertex2d(second_line.first / dimensions.first, -second_line.second / dimensions.second);

        glEnd();

        qol::handleKeyInput(window, ss);

        sphere({0, 0}, 0.02);
        sphere({first_line.first / dimensions.first, -first_line.second / dimensions.second}, 0.02);
        sphere({second_line.first / dimensions.first, -second_line.second / dimensions.second}, 0.02);

        st = sim::update(st, ss, 0.2);
        time += 0.2;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

int main(int argc, char** argv) {
    sim::initialValues initial;
    std::pair<int, int> dimensions{1500, 1500};

    qol::removeDataFile("data.txt");

    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    auto window = glfwCreateWindow(dimensions.first / 2, dimensions.second / 2, "Podwojne wachadlo", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);
    glViewport(0, 0, dimensions.first, dimensions.second);
    glClearColor(0.2, 0.2, 0.2, 0);

    initial.theta1 = std::stod(argv[1]);
    initial.theta2 = std::stod(argv[2]);
    initial.length1 = 500;
    initial.length2 = 500;
    initial.mass1 = 1;
    initial.mass2 = 1;

    loop(window, dimensions, initial);

    glfwDestroyWindow(window);
    glfwTerminate();
}