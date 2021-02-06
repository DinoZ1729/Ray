#ifndef RAY_FUNCTIONS_H
#define RAY_FUNCTIONS_H
#include <cmath>

void transformVector(double [],const double []);
void invert(double [],const double []);
void cross(double [],double [],double []);
double magnitute(double []);
void normalize(double []);
void scale(double [],double);
double dot(double [], double []);
void vector(double [],double [],double []);
double clamp(double ,double,double);
#endif