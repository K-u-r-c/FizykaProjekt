#pragma once

#include "simulation.h"

void handleKeyInput(GLFWwindow *window, psystem &pss, double &timestep, bool &trail_enabled) {
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS))
        pss.length1 += 1;
    else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        pss.length1 += 5;
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS))
        pss.length1 -= 1;
    else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        pss.length1 -= 5;

    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS))
        pss.length2 += 1;
    else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        pss.length2 += 5;
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS))
        pss.length2 -= 1;
    else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        pss.length2 -= 5;

    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS))
        pss.mass1 += 0.05;
    else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        pss.mass1 += 1;
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS))
        pss.mass1 -= 0.05;
    else if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        pss.mass1 -= 1;

    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS))
        pss.mass2 += 0.05;
    else if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        pss.mass2 += 1;
    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS))
        pss.mass2 -= 0.05;
    else if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        pss.mass2 -= 1;

    if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS))
        timestep += 0.001;
    else if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        timestep += 0.01;
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS))
        timestep -= 0.001;
    else if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        timestep -= 0.01;

    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)) trail_enabled = 1;
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS && (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)) trail_enabled = 0;
}