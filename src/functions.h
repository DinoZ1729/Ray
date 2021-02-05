#pragma once
//declaration

void transformVector(double vec[3],const double m[16]);
void invert(double inv[16],const double matrix[16]);
void cross(double r[3],double a[3],double b[3]);
double magnitute(double r[3]);
void normalize(double r[3]);
void scale(double a[3],double k);
double dot(double a[3], double b[3]);
void vector(double a[3],double b[3],double c[3]);
double clamp(double x,double min,double max);
