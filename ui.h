#pragma once

#include <cmath>
#include <iostream>

#ifdef __APPLE__
#include <GLUT/glut.h>
#endif

template <typename... Args>
void print(Args &&...args) {
    (std::cout << ... << args) << std::endl;
}

void clear() {
#if defined(__APPLE__) || defined(__unix__)
    system("clear");
#elif defined(__WIN32) || defined(__WIN64)
    system("cls");
#endif
}

void displayValues(double l1, double l2, double m1, double m2, double p1, double p2, double pd1, double pd2, double t) {
#ifdef __APPLE__
    std::string message;
    glColor3d(1., 1., 1.);

    glRasterPos2d(-0.98, 0.95);
    message = "Length 1: " + std::to_string(l1);
    for (int i = 0; i < message.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
    }

    glRasterPos2d(-0.4, 0.95);
    message = "Length 2: " + std::to_string(l2);
    for (int i = 0; i < message.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
    }

    glRasterPos2d(-0.98, 0.9);
    message = "Mass 1: " + std::to_string(m1);
    for (int i = 0; i < message.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
    }

    glRasterPos2d(-0.4, 0.9);
    message = "Mass 2: " + std::to_string(m2);
    for (int i = 0; i < message.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
    }

    glRasterPos2d(-0.98, 0.85);
    message = "Phi 1: " + std::to_string(p1);
    for (int i = 0; i < message.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
    }

    glRasterPos2d(-0.4, 0.85);
    message = "Phi 2: " + std::to_string(p2);
    for (int i = 0; i < message.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
    }

    glRasterPos2d(-0.98, 0.8);
    message = "Phi_dot 1: " + std::to_string(pd1);
    for (int i = 0; i < message.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
    }

    glRasterPos2d(-0.4, 0.8);
    message = "Phi_dot 2: " + std::to_string(pd2);
    for (int i = 0; i < message.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
    }

    glRasterPos2d(-0.98, 0.75);
    message = "Time: " + std::to_string(t);
    for (int i = 0; i < message.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
    }
#else
    clear();
    print("Length1: ", l1, "\tLength2: ", l2);
    print("Mass1: ", m1, "\tMass2: ", m2);
    print("Phi1: ", p1 * 180 / M_PI, "\tPhi2: ", p2 * 180 / M_PI);
    print("Phi_dot1: ", pd1 * 180 / M_PI, "\nPhi_dot2: ", pd2 * 180 / M_PI);
#endif
}