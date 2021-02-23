#ifndef __VECTOR_H__
#define __VECTOR_H__

/* Includes */

#include <cmath>


/* Class */

class Vector
{
public:
    Vector() = default;
    Vector(const double x, const double y, const double z);

    /* Operators */
    friend Vector operator + (const Vector &v1, const Vector &v2);
    friend Vector operator - (const Vector &v1, const Vector &v2);
    friend Vector operator * (const Vector &v, double k);
    friend Vector operator * (double k, const Vector &v);

    double dot(const Vector &v);
    void normalize();

    Vector transformMatrixToVector(const double m[16]);

    double getX() const { return _x; }
    double getY() const { return _y; }
    double getZ() const { return _z; }

    void setX(const double x) { _x = x; }
    void setY(const double y) { _y = y; }
    void setZ(const double z) { _z = z; }

    void set(const double x, const double y, const double z);

private:
    double _x{};
    double _y{};
    double _z{};
};

#endif
