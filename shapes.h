#pragma once

#ifdef __APPLE__
#include <OpenGL/gl.h>
#elif
#include <GL/gl.h>
#endif

#include <cmath>

struct Color {
    Color(double r, double g, double b, int m) : rgb{r, g, b}, m{m} {}
    Color() {}
    double rgb[3];
    int m;
};

void circle(double cx, double cy, double radius, Color color = {0.3, 0.5, 1, 1}) {
    double x2, y2;

    glBegin(GL_TRIANGLE_FAN);
    glColor3d(color.rgb[0], color.rgb[1], color.rgb[2]);

    glVertex2d(cx, cy);

    for (double angle = 0; angle < 360; angle += 0.2) {
        x2 = cx + sin(angle) * radius;
        y2 = cy + cos(angle) * radius;
        glVertex2d(x2, y2);
    }

    glEnd();
}

void trail(std::vector<std::pair<double, double>> points, Color color) {
    glLineWidth(2);
    glBegin(GL_LINE_STRIP);

    for (int i = 0; i < points.size(); i++) {
        color.rgb[color.m] = i * 0.1;
        glColor3d(color.rgb[0], color.rgb[1], color.rgb[2]);
        glVertex2d(points[i].first, points[i].second);
    }

    glEnd();
}

void line(double x1, double y1, double x2, double y2) {
    glLineWidth(4);
    glBegin(GL_LINE_STRIP);
    glColor3d(0.7, 0.5, 0.3);

    glVertex2f(x1, y1);
    glVertex2f(x2, y2);

    glEnd();
}