#pragma once
//declaration

#include <cmath>

typedef struct Ball {
    double center[3];
    double radius;
    double color; // on the interval from 0 (dark) to 1 (light)
    double coeff; // on the scale from 0 to 1 how much does the ball reflect light
                  // (1 means it's the perfect mirror)
} ball;

void transformVector(double vec[3],const double m[16]);
void invert(double inv[16],const double matrix[16]);
double magnitute(double r[3]);
void normalize(double r[3]);
void scale(double a[3],double k);
double dot(double a[3], double b[3]);
void vector(double a[3],double b[3],double c[3]);
