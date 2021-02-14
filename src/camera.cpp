#include "Camera.h"

Camera::Camera(double r, double alfa, double beta)
{
    // alfa is camera's angle along the xy plane.
    // beta is camera's angle along z axis
    // r is the distance from the camera to the origin
    double a = sin(alfa), b = cos(alfa), c = sin(beta), d = cos(beta);
    x = r * b * d;
    y = r * a * d;
    z = r * c;

    // matrix
    matrix[3] = matrix[7] = matrix[11] = 0;
    matrix[15] = 1;
    // x
    matrix[0] = -a;
    matrix[1] = b;
    matrix[2] = 0;
    // y
    matrix[4] = b * c;
    matrix[5] = a * c;
    matrix[6] = -d;
    // z
    matrix[8] = b * d;
    matrix[9] = a * d;
    matrix[10] = c;

    matrix[12] = x;
    matrix[13] = y;
    matrix[14] = z;

    // invert
    invert(inv, matrix);
}

Camera::~Camera()
{
}

double Camera::rayTrace(double origin[3], double unit[3], ball balls[],
                        int n, double altitute, double coeff, int limit)
{
    double color;
    double distanceToPlane = -(origin[2] + altitute) / unit[2]; // this is signed distance
    int index = -1;
    double distance;
    for (int i = 0; i < n; i++) {
        double diff[3];
        vector(diff, origin, balls[i].center);
        double discriminant = dot(unit, diff) * dot(unit, diff) +
            balls[i].radius * balls[i].radius - dot(diff, diff);
        if (discriminant < 0)
            continue;
        distance = -dot(unit, diff) - sqrt(discriminant);
        if (distance <= 0)
            continue;
        index = i;
        break;
    }
    if (index == -1) {
        if (unit[2] > 0) {
            return 0; // ray hit the sky
        }
        else      // ray hit the groung
        {
            double tx = origin[0] + distanceToPlane * unit[0],
                ty = origin[1] + distanceToPlane * unit[1];
            double color = std::clamp(1 / (1 + distanceToPlane / 10), 0.0, 1.0);
            double origin2[3] = { origin[0] + distanceToPlane * unit[0],
                                 origin[1] + distanceToPlane * unit[1],
                                 origin[2] + distanceToPlane * unit[2] };
            double unit2[3] = { unit[0], unit[1], -unit[2] };
            if ((int)(floor(tx) + floor(ty)) % 2 == 0)
                return (1 - coeff) * color + coeff * rayTrace(origin2, unit2, balls,
                    n, altitute, coeff,
                    limit - 1);
            else
                return 0;
        }
    }

    if (unit[2] < 0 && distance > distanceToPlane) // ray hit the groung
    {
        double tx = origin[0] + distanceToPlane * unit[0],
            ty = origin[1] + distanceToPlane * unit[1];
        return (double)((int)(floor(tx) + floor(ty)) % 2);
    }
    // ray hit a ball
    double origin2[3] = { origin[0] + unit[0] * distance,
                         origin[1] + unit[1] * distance,
                         origin[2] + unit[2] * distance };
    double normal[3];
    vector(normal, origin2, balls[index].center);
    normalize(normal);
    double k = 2 * dot(unit, normal);
    scale(normal, k);
    double unit2[3];
    vector(unit2, unit, normal);
    if (limit == 0)
        return balls[index].color;
    return (1 - balls[index].coeff) * balls[index].color +
        balls[index].coeff *
        rayTrace(origin2, unit2, balls, n, altitute, coeff, limit - 1);
}
