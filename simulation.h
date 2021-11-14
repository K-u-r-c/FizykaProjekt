#pragma once

#include <GLFW/glfw3.h>

struct status {
    double phi1, phi2, phi_dot1, phi_dot2;
};

struct psystem {
    double mass1, mass2, length1, length2;
};

class Simulation {
   private:
    double g = 9.81;
    double dt = 0.05;
    double trailpCount = 100;

   public:
    status derivative(status& stat, psystem& sys);
    status rungeKutta4(status& stat, psystem& sys);
    status update(status& stat, psystem& sys, double t);

    Simulation(GLFWwindow* window, status st, psystem pss, int width, int height);
    Simulation(GLFWwindow* window, int width, int height, int number, int mode = 0);
    ~Simulation();
};