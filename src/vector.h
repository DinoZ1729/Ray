#ifndef __VECTOR_H__
#define __VECTOR_H__

/* Includes */

#include <cmath>


/* Class */

class Vector
{
public:
    Vector();
    Vector(double x, double y, double z);
    ~Vector();

    /* Operators */
    friend Vector operator + (const Vector &v1, const Vector &v2);
    friend Vector operator - (const Vector &v1, const Vector &v2);
    friend Vector operator * (const Vector &v, double k);
    friend Vector operator * (double k, const Vector &v);

    double dot(const Vector &v);
    void normalize();

    Vector transformMatrixToVector(const double m[16]);

    double getX() { return _x; }
    double getY() { return _y; }
    double getZ() { return _z; }

    double setX(double x) { _x = x; }
    double setY(double y) { _y = y; }
    double setZ(double z) { _z = z; }

    void set(double x, double y, double z);

private:
    double _x;
    double _y;
    double _z;
};

#endif
