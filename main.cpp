#include <string>

#include "simulation.h"
#include "window.h"

enum { ARG_NAME, ARG_PHI1, ARG_PHI2, ARG_WIDTH, ARG_HEIGHT, ARG_ARGC };

int main(int argc, char** argv) {
    auto win = Window(std::stoi(argv[ARG_WIDTH]), std::stoi(argv[ARG_HEIGHT]), "Double Pendulum Simulation");
    Simulation(win.getWindow(), {std::stod(argv[ARG_PHI1]), std::stod(argv[ARG_PHI2]), 0, 0}, {1, 1, 200, 200}, win.getWidth(), win.getHeight());

    return 0;
}