#include <math.h>

#include <iostream>
#include <utility>

namespace sim {

double g = 9.81;
double dt = 0.005;

struct sphere_ss {
    std::pair<double, double> mass;
    std::pair<double, double> length;
};

/*
std::pair<double, double> operator+(const std::pair<double, double>& p1, const std::pair<double, double>& p2) {
    return {p1.first + p2.first, p1.second + p2.second};
}

std::pair<double, double> operator*(const double d, const std::pair<double, double>& p) { return {d * p.first, d * p.second}; }

angles_st operator+(const angles_st& s1, const angles_st& s2) { return {s1.theta + s2.theta, s1.theta_dot + s2.theta_dot}; }
angles_st operator*(const double d, const angles_st& s) { return {d * s.theta, d * s.theta_dot}; }
*/
struct angles_st {
    std::pair<double, double> theta;
    std::pair<double, double> theta_dot;
};

angles_st update(const angles_st& st, const sphere_ss& ss, double time) {
    angles_st ust = st;
    double mi = ss.mass.second / (ss.mass.first + ss.mass.second);
    double lambda = ss.length.first / ss.length.second;

    double theta1_2_dot =
        (mi / lambda * st.theta_dot.second * sin(st.theta.first - st.theta.second) + g / ss.length.first * sin(st.theta.first) +
         1. / 2 * mi * sin(2 * (st.theta.first - st.theta.second)) * pow(st.theta_dot.first, 2) -
         mi * g / ss.length.first * sin(st.theta.second) * cos(st.theta.first - st.theta.second)) /
        (mi * pow(cos(st.theta.first - st.theta.second), 2) - 1);

    double theta2_2_dot = (1. / 2 * mi * sin(2 * (st.theta.first - st.theta.second)) * pow(st.theta_dot.second, 2) +
                           g / ss.length.second * sin(st.theta.first) * cos(st.theta.first - st.theta.second) +
                           lambda * pow(st.theta_dot.first, 2) * sin(st.theta.first - st.theta.second) -
                           g / ss.length.second * sin(st.theta.second)) /
                          (1 - mi * pow(cos(st.theta.first - st.theta.second), 2));

    std::cout << lambda << "\t";
    std::cout << mi << "\n";

    // mamy predkosci kul + w gore - w dol theta.dot - prredkosc; a* t = delta v v = v0 + a * delta t
    ust.theta_dot.first += theta1_2_dot * time;
    ust.theta_dot.first += theta2_2_dot * time;
    // czas wyliczyć przemieszczenie
    double s1 = ust.theta_dot.first * time;
    double s2 = ust.theta_dot.second * time;

    // miara łukowa
    double dl_okregu_1 = 2 * M_PI * ss.length.first;
    double dl_okregu_2 = 2 * M_PI * ss.length.second;
    double fi_1 = s1 / dl_okregu_1 * 2 * M_PI;  // wiemy jaka część okręgu * 2pi
    // std::cout << fi_1 << "\n";
    double fi_2 = s2 / dl_okregu_2 * 2 * M_PI;
    // std::cout << ust.theta.first << "\t";
    ust.theta.first = std::fmod(st.theta.first + fi_1, 2 * M_PI);
    // std::cout << ust.theta.first << "\t";
    ust.theta.second = std::fmod(st.theta.second + fi_2, 2 * M_PI);

    return ust;
}

}  // namespace sim
