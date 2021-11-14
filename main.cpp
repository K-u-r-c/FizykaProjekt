#include <iostream>
#include <string>

#include "simulation.h"
#include "window.h"

namespace sim1 {
enum { ARG_NAME, ARG_PHI1, ARG_PHI2, ARG_L1, ARG_L2, ARG_M1, ARG_M2, ARG_WIDTH, ARG_HEIGHT, ARG_ARGC };
}
namespace sim2 {
enum { ARG_NAME = 0, ARG_WIDTH = 1, ARG_HEIGHT = 2, ARG_NUMBER = 3, ARG_ARGC = 4 };
}

int main(int argc, char** argv) {
    if (sim1::ARG_ARGC == argc) {
        auto win = Window(std::stoi(argv[sim1::ARG_WIDTH]), std::stoi(argv[sim1::ARG_HEIGHT]), "Double Pendulum Simulation");
        Simulation(win.getWindow(), {std::stod(argv[sim1::ARG_PHI1]), std::stod(argv[sim1::ARG_PHI2]), 0, 0},
                   {std::stod(argv[sim1::ARG_M1]), std::stod(argv[sim1::ARG_M2]), std::stod(argv[sim1::ARG_L1]), std::stod(argv[sim1::ARG_L2])},
                   win.getWidth(), win.getHeight());
    } else if (sim2::ARG_ARGC == argc) {
        auto win = Window(std::stoi(argv[sim2::ARG_WIDTH]), std::stoi(argv[sim2::ARG_HEIGHT]), "Double Pendulum Simulation");
        Simulation(win.getWindow(), std::stoi(argv[sim2::ARG_WIDTH]), std::stoi(argv[sim2::ARG_HEIGHT]), std::stoi(argv[sim2::ARG_NUMBER]));
    } else {
        std::cerr << "Wrong input values !";
    }

    return 0;
}