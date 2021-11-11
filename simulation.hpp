#include <cmath>
#include <utility>

namespace sim {

double g = 9.81;
double dt = 0.001;

struct state {
    std::pair<double, double> theta;
    std::pair<double, double> theta_dot;
};

struct system {
    std::pair<double, double> mass;
    std::pair<double, double> length;
};

struct initialValues {
    double theta1, theta2;
    double length1, length2;
    double mass1, mass2;
};

std::pair<double, double> operator+(const std::pair<double, double>& p1, const std::pair<double, double>& p2) noexcept {
    return {p1.first + p2.first, p1.second + p2.second};
}

std::pair<double, double> operator*(const double d, const std::pair<double, double>& p) noexcept { return {d * p.first, d * p.second}; }

state operator+(const state& s1, const state& s2) noexcept { return {s1.theta + s2.theta, s1.theta_dot + s2.theta_dot}; }

state operator*(const double d, const state& s) noexcept { return {d * s.theta, d * s.theta_dot}; }

state derive(const state& st, const system& ss) {
    const double delta = st.theta.second - st.theta.first;
    const double mass = ss.mass.first + ss.mass.second;

    double sinus = sin(delta);
    double cosinus = cos(delta);

    double denominator = mass * ss.length.first - ss.mass.second * ss.length.first * cosinus * cosinus;

    state derivative{{st.theta_dot.first, st.theta_dot.second}, {0, 0}};
    derivative.theta_dot.first = ss.mass.second * ss.length.first * st.theta_dot.first * st.theta_dot.first * sinus * cosinus +
                                 ss.mass.second * g * sin(st.theta.second) * cosinus +
                                 ss.mass.second * ss.length.second * st.theta_dot.second * st.theta_dot.second * sinus -
                                 mass * g * sin(st.theta.first);

    derivative.theta_dot.first /= denominator;

    denominator *= ss.length.second / ss.length.first;

    derivative.theta_dot.second = -ss.mass.second * ss.length.second * st.theta_dot.second * st.theta_dot.second * sinus * cosinus +
                                  mass * g * sin(st.theta.first) * cosinus -
                                  mass * ss.length.first * st.theta_dot.first * st.theta_dot.first * sinus - mass * g * sin(st.theta.second);

    derivative.theta_dot.second /= denominator;

    return derivative;
}

state rungeKutta4(const state& st, const system& ss) {
    state dydx = derive(st, ss);
    state k1 = dt * dydx;
    state yt = st + 0.5 * k1;

    dydx = derive(yt, ss);
    state k2 = dt * dydx;
    yt = st + 0.5 * k2;

    dydx = derive(yt, ss);
    state k3 = dt * dydx;
    yt = st + k3;

    dydx = derive(yt, ss);
    state k4 = dt * dydx;

    return st + (1.0 / 6) * k1 + (1.0 / 3) * k2 + (1.0 / 3) * k3 + (1.0 / 6) * k4;
}

state update(const state& st, const system& ss, double time) {
    double passed = 0.0;

    state ust = st;

    do {
        ust = rungeKutta4(ust, ss);
        passed += dt;
    } while (passed < time);

    return ust;
}

}  // namespace sim