#pragma once

#include <cmath>
#include <fstream>

void removeDataFile(const char *filename) { remove(filename); }

void saveData(double x, double y1, double y2) {
    std::ofstream myfile("data.txt", std::ios::out | std::ios::app);

    myfile << x << " " << y1 * 180 / M_PI << " " << y2 * 180 / M_PI << "\n";

    myfile.close();
}