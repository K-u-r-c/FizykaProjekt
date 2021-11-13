#include "simulation.h"

#include "input.h"
#include "save.h"
#include "shapes.h"
#include "ui.h"

Simulation::Simulation(GLFWwindow* window, status st, psystem pss, int width, int height) {
    removeDataFile("data.txt");

    double t = 0, timestep = 0.05;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2, 0.2, 0.2, 0);

        displayValues(pss.length1, pss.length2, pss.mass1, pss.mass2, st.phi1 * 180 / M_PI, st.phi2 * 180 / M_PI, st.phi_dot1, st.phi_dot2);
        saveData(t, st.phi1 * 180 / M_PI, st.phi2 * 180 / M_PI);
        handleKeyInput(window, pss, timestep);

        glLineWidth(4);

        line(0, 0, pss.length1 * sin(st.phi1) / width, -(pss.length1 * cos(st.phi1) / height));
        line(pss.length1 * sin(st.phi1) / width, -(pss.length1 * cos(st.phi1) / height),
             (pss.length1 * sin(st.phi1) + pss.length2 * sin(st.phi2)) / width, -(pss.length1 * cos(st.phi1) + pss.length2 * cos(st.phi2)) / height);

        circle(0, 0, 0.03);
        circle(pss.length1 * sin(st.phi1) / width, -(pss.length1 * cos(st.phi1)) / height, pss.mass1 * 0.01);
        circle((pss.length1 * sin(st.phi1) + pss.length2 * sin(st.phi2)) / width, -(pss.length1 * cos(st.phi1) + pss.length2 * cos(st.phi2)) / height,
               pss.mass2 * 0.01);

        // advance system
        st = update(st, pss, timestep);
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