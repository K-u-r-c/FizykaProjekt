#pragma once

#ifdef __APPLE__
#include <OpenGL/gl.h>
#elif
#include <GL/gl.h>
#endif

#include <cmath>

void circle(double cx, double cy, double radius) {
    double x2, y2;

    glBegin(GL_TRIANGLE_FAN);
    glColor3d(1, 1, 1);

    glVertex2d(cx, cy);

    for (double angle = 0; angle < 360; angle += 0.2) {
        x2 = cx + sin(angle) * radius;
        y2 = cy + cos(angle) * radius;
        glVertex2d(x2, y2);
    }

    glEnd();
}

void line(double x1, double y1, double x2, double y2) {
    glBegin(GL_LINE_STRIP);
    glColor3d(0.7, 0.7, 0.3);

    glVertex2f(x1, y1);
    glVertex2f(x2, y2);

    glEnd();
}