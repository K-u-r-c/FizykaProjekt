#include <iostream>
#include <utility>

template <typename... Args>
void print_l(Args&&... args) {
    (std::cout << ... << args) << std::endl;
}

template <typename... Args>
void print(Args&&... args) {
    (std::cout << ... << args);
}