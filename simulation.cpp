#include "simulation.h"

#include <random>
#include <utility>
#include <vector>

#include "input.h"
#include "save.h"
#include "shapes.h"
#include "ui.h"

Simulation::Simulation(GLFWwindow* window, status st, psystem pss, int width, int height) {
    removeDataFile("data.txt");

    double t = 0, timestep = 0.2;

    std::vector<std::pair<double, double>> points1, points2;
    bool trail_enabled = true;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.1, 0.1, 0.1, 1);

        displayValues(pss.length1, pss.length2, pss.mass1, pss.mass2, st.phi1 * 180 / M_PI, st.phi2 * 180 / M_PI, st.phi_dot1, st.phi_dot2, t);
        saveData(t, st.phi1 * 180 / M_PI, st.phi2 * 180 / M_PI);
        handleKeyInput(window, pss, timestep, trail_enabled);

        double line11 = pss.length1 * sin(st.phi1);
        double line12 = pss.length1 * cos(st.phi1);
        double line21 = line11 + pss.length2 * sin(st.phi2);
        double line22 = line12 + pss.length2 * cos(st.phi2);

        line(0, 0, line11 / width, -(line12 / height));
        line(line11 / width, -(line12 / height), line21 / width, -(line22) / height);

        if (trail_enabled) {
            if (points1.size() < 100) {
            } else {
                points1.erase(points1.begin());
                points2.erase(points2.begin());
            }
            points1.push_back({line11 / width, -(line12 / height)});
            points2.push_back({line21 / width, -(line22) / height});
            trail(points1, Color(1, 0.1, 0.1, 0));
            trail(points2, Color(0.1, 0.1, 1, 2));
        }

        circle(0, 0, 0.02);
        circle(line11 / width, -(line12) / height, 0.02);
        circle(line21 / width, -(line22) / height, 0.02);
        // advance system
        st = update(st, pss, timestep);

        t += timestep;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

Simulation::Simulation(GLFWwindow* window, int width, int height, int number) {
    std::mt19937 generator((std::random_device())());
    std::uniform_real_distribution<> rnd(-2 * M_PI, 2 * M_PI);
    std::uniform_real_distribution<> rndcol(0, 1.);

    removeDataFile("data.txt");

    status st[number];
    Color color[number];
    psystem pss = {1, 1, width / 4., height / 4.};
    double t = 0, timestep = 0.2;

    for (int i = 0; i < number; i++) {
        st[i] = {rnd(generator), rnd(generator), 0, 0};
        color[i].rgb[0] = rndcol(generator);
        color[i].rgb[1] = rndcol(generator);
        color[i].rgb[2] = rndcol(generator);
    }

    std::vector<std::pair<double, double>> points1, points2;
    bool line_enabled = true;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.1, 0.1, 0.1, 1);

        handleKeyInput(window, pss, timestep, line_enabled);

        circle(0, 0, 0.02);
        for (int i = 0; i < number; i++) {
            double line11 = pss.length1 * sin(st[i].phi1);
            double line12 = pss.length1 * cos(st[i].phi1);
            double line21 = line11 + pss.length2 * sin(st[i].phi2);
            double line22 = line12 + pss.length2 * cos(st[i].phi2);

            if (line_enabled) {
                line(0, 0, line11 / width, -(line12 / height));
                line(line11 / width, -(line12 / height), line21 / width, -(line22) / height);
            }

            circle(line11 / width, -(line12) / height, 0.02, color[i]);
            circle(line21 / width, -(line22) / height, 0.02, color[i]);
            // advance system
            st[i] = update(st[i], pss, timestep);
        }

        t += timestep;

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

Simulation::~Simulation() {}

status Simulation::derivative(status& stat, psystem& sys) {
    double delta = stat.phi2 - stat.phi1;
    double mass = sys.mass1 + sys.mass2;

    double sinus = sin(delta);
    double cosinus = cos(delta);

    double denominator = mass * sys.length1 - sys.mass2 * sys.length1 * cosinus * cosinus;

    status der{stat.phi_dot1, stat.phi_dot2, 0, 0};
    der.phi_dot1 = sys.mass2 * sys.length1 * stat.phi_dot1 * stat.phi_dot1 * sinus * cosinus + sys.mass2 * g * sin(stat.phi2) * cosinus +
                   sys.mass2 * sys.length2 * stat.phi_dot2 * stat.phi_dot2 * sinus - mass * g * sin(stat.phi1);

    der.phi_dot1 /= denominator;
    denominator *= sys.length2 / sys.length1;

    der.phi_dot2 = -sys.mass2 * sys.length2 * stat.phi_dot2 * stat.phi_dot2 * sinus * cosinus + mass * g * sin(stat.phi1) * cosinus -
                   mass * sys.length1 * stat.phi_dot1 * stat.phi_dot1 * sinus - mass * g * sin(stat.phi2);

    der.phi_dot2 /= denominator;

    return der;
}

status Simulation::rungeKutta4(status& stat, psystem& sys) {
    status dydx = derivative(stat, sys);
    status k1 = {dydx.phi1 * dt, dydx.phi2 * dt, dydx.phi_dot1 * dt, dydx.phi_dot2 * dt};
    status yt = {stat.phi1 + k1.phi1 / 2, stat.phi2 + k1.phi2 / 2, stat.phi_dot1 + k1.phi_dot1 / 2, stat.phi_dot2 + k1.phi_dot2 / 2};

    dydx = derivative(yt, sys);
    status k2 = {dydx.phi1 * dt, dydx.phi2 * dt, dydx.phi_dot1 * dt, dydx.phi_dot2 * dt};
    yt = {stat.phi1 + k2.phi1 / 2, stat.phi2 + k2.phi2 / 2, stat.phi_dot1 + k2.phi_dot1 / 2, stat.phi_dot2 + k2.phi_dot2 / 2};

    dydx = derivative(yt, sys);
    status k3 = {dydx.phi1 * dt, dydx.phi2 * dt, dydx.phi_dot1 * dt, dydx.phi_dot2 * dt};
    yt = {stat.phi1 + k3.phi1 / 2, stat.phi2 + k3.phi2 / 2, stat.phi_dot1 + k3.phi_dot1 / 2, stat.phi_dot2 + k3.phi_dot2 / 2};

    dydx = derivative(yt, sys);
    status k4 = {dydx.phi1 * dt, dydx.phi2 * dt, dydx.phi_dot1 * dt, dydx.phi_dot2 * dt};

    return {
        stat.phi1 + (1.0 / 6) * k1.phi1 + (1.0 / 3) * k2.phi1 + (1.0 / 3) * k3.phi1 + (1.0 / 6) * k4.phi1,
        stat.phi2 + (1.0 / 6) * k1.phi2 + (1.0 / 3) * k2.phi2 + (1.0 / 3) * k3.phi2 + (1.0 / 6) * k4.phi2,
        stat.phi_dot1 + (1.0 / 6) * k1.phi_dot1 + (1.0 / 3) * k2.phi_dot1 + (1.0 / 3) * k3.phi_dot1 + (1.0 / 6) * k4.phi_dot1,
        stat.phi_dot2 + (1.0 / 6) * k1.phi_dot2 + (1.0 / 3) * k2.phi_dot2 + (1.0 / 3) * k3.phi_dot2 + (1.0 / 6) * k4.phi_dot2,
    };
}

status Simulation::update(status& stat, psystem& sys, double t) {
    double time_passed = 0;

    status updated_stat = stat;

    while (time_passed < t) {
        updated_stat = rungeKutta4(updated_stat, sys);
        time_passed += dt;
    }

    return updated_stat;
}