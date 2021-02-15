#include "Camera.h"

Camera::Camera(double r, double alfa, double beta)
{
    double a = sin(alfa), b = cos(alfa);    /* alfa is camera's angle along the xy plane */
    double c = sin(beta), d = cos(beta);    /* beta is camera's angle along z axis */
                                            /* r is the distance from the camera to the origin */

    x = r * b * d;
    y = r * a * d;
    z = r * c;

    /* matrix */
    matrix[3] = 0;
    matrix[7] = 0;
    matrix[11] = 0;
    matrix[15] = 1;

    /* x */
    matrix[0] = -a;
    matrix[1] = b;
    matrix[2] = 0;

    /* y */
    matrix[4] = b * c;
    matrix[5] = a * c;
    matrix[6] = -d;

    /* z */
    matrix[8] = b * d;
    matrix[9] = a * d;
    matrix[10] = c;

    matrix[12] = x;
    matrix[13] = y;
    matrix[14] = z;

    /* invert */
    invert(inv, matrix);
}

Camera::~Camera()
{
}

double Camera::rayTrace(Vector &origin, Vector &unit, ball balls[], int n, double altitute, double coeff, int limit)
{
    double color;
    double distanceToPlane = -(origin.getZ() + altitute) / unit.getZ(); /* this is signed distance */
    int index = -1;
    double distance;
    for (int i = 0; i < n; i++)
    {
        Vector diff = origin - balls[i].center;
        double discriminant = unit.dot(diff) * unit.dot(diff) + balls[i].radius * balls[i].radius - diff.dot(diff);

        if (discriminant < 0)
        {
            continue;
        }

        distance = -unit.dot(diff) - sqrt(discriminant);

        if (distance <= 0)
        {
            continue;
        }
        index = i;
        break;
    }
    if (index == -1)
    {
        if (unit.getZ() > 0)
        {
            return 0;   /* ray hit the sky */
        }
        else            /* ray hit the ground */
        {
            double tx = origin.getX() + distanceToPlane * unit.getX();
            double ty = origin.getY() + distanceToPlane * unit.getY();

            double color = std::clamp(1 / (1 + distanceToPlane / 10), 0.0, 1.0);

            Vector origin2( origin.getX() + distanceToPlane * unit.getX(),
                            origin.getY() + distanceToPlane * unit.getY(),
                            origin.getZ() + distanceToPlane * unit.getZ());

            Vector unit2(   unit.getX(),
                            unit.getY(),
                            -unit.getZ());

            if ((int)(floor(tx) + floor(ty)) % 2 == 0)
            {
                return (1 - coeff) * color + coeff * rayTrace(origin2, unit2, balls, n, altitute, coeff, limit - 1);
            }
            else
            {
                return 0;
            }
        }
    }

    if (unit.getZ() < 0 && distance > distanceToPlane)  /* ray hit the ground */
    {
        double tx = origin.getX() + distanceToPlane * unit.getX();
        double ty = origin.getY() + distanceToPlane * unit.getY();

        return (double)((int)(floor(tx) + floor(ty)) % 2);
    }

    /* ray hit a ball */
    Vector origin2( origin.getX() + unit.getX() * distance,
                    origin.getY() + unit.getY() * distance,
                    origin.getZ() + unit.getZ() * distance);

    Vector normal = origin2 - balls[index].center;
    normal.normalize();

    double k = 2 * unit.dot(normal);
    normal = normal * k;

    Vector unit2 = unit - normal;

    if (limit == 0)
    {
        return balls[index].color;
    }
    return (1 - balls[index].coeff) * balls[index].color + balls[index].coeff *
            rayTrace(origin2, unit2, balls, n, altitute, coeff, limit - 1);
}
