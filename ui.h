#pragma once

#include <cmath>
#include <iostream>

template <typename... Args>
void print(Args &&...args) {
    (std::cout << ... << args) << std::endl;
}

void clear() {
#ifdef __APPLE__
    system("clear");
#endif
#ifdef __unix__
    system("clear");
#endif
#ifdef __WIN32
    system("cls");
#endif
#ifdef __WIN64
    system("cls");
#endif
}

void displayValues(double l1, double l2, double m1, double m2, double p1, double p2, double pd1, double pd2) {
    clear();
    print("Length1: ", l1, "\tLength2: ", l2);
    print("Mass1: ", m1, "\tMass2: ", m2);
    print("Phi1: ", p1 * 180 / M_PI, "\tPhi2: ", p2 * 180 / M_PI);
    print("Phi_dot1: ", pd1 * 180 / M_PI, "\nPhi_dot2: ", pd2 * 180 / M_PI);
}