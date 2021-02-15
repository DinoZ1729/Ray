#include "vector.h"

Vector::Vector() : _x(0.0f), _y(0.0f), _z(0.0f)
{
}

Vector::Vector(double x, double y, double z) : _x(x), _y(y), _z(z)
{
}

Vector::~Vector()
{
}

Vector operator+(const Vector &v1, const Vector &v2)
{
    return Vector(v1._x + v2._x, v1._y + v2._y, v1._z + v2._z);
}

Vector operator-(const Vector &v1, const Vector &v2)
{
    return Vector(v1._x - v2._x, v1._y - v2._y, v1._z - v2._z);
}

Vector operator*(const Vector &v, double k)
{
    return Vector(v._x * k, v._y * k, v._z * k);
}

Vector operator*(double k, const Vector &v)
{
    return Vector(v._x * k, v._y * k, v._z * k);
}

double Vector::dot(const Vector &v)
{
    return _x * v._x + _y * v._y + _z * v._z;
}

void Vector::normalize()
{
    double len = sqrt(_x * _x + _y * _y + _z * _z);
    if (len != 0)
    {
        _x /= len;
        _y /= len;
        _z /= len;
    }
}

Vector Vector::transformMatrixToVector(const double m[16])
{
    Vector ret( _x * m[0] + _y * m[4] + _z * m[8] + m[12],
                _x * m[1] + _y * m[5] + _z * m[9] + m[13],
                _x * m[2] + _y * m[6] + _z * m[10] + m[14]);
    return ret;
}

void Vector::set(double x, double y, double z)
{
    _x = x;
    _y = y;
    _z = z;
}
