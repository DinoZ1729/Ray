#pragma once

#include "functions.h"

#include <algorithm>
#include <cmath>

class Camera
{
public:
    Camera(double r, double alfa, double beta);
    ~Camera();

    double rayTrace(double origin[3], double unit[3], ball balls[], int n, double altitute, double coeff, int limit);

    double x, y, z;
    double matrix[16], inv[16];
};
