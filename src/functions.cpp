#include <cmath>
#include "functions.h"

void transformVector(double vec[3],const double m[16])
{
	double 	tx=vec[0]*m[0]+vec[1]*m[4]+vec[2]*m[8]+m[12],
			ty=vec[0]*m[1]+vec[1]*m[5]+vec[2]*m[9]+m[13],
			tz=vec[0]*m[2]+vec[1]*m[6]+vec[2]*m[10]+m[14];
	vec[0]=tx;
	vec[1]=ty;
	vec[2]=tz;
}

void invert(double inv[16],const double matrix[16])
{
	double det;
    int i;

    inv[0] = matrix[5]  * matrix[10] * matrix[15] - 
             matrix[5]  * matrix[11] * matrix[14] - 
             matrix[9]  * matrix[6]  * matrix[15] + 
             matrix[9]  * matrix[7]  * matrix[14] +
             matrix[13] * matrix[6]  * matrix[11] - 
             matrix[13] * matrix[7]  * matrix[10];

    inv[4] = -matrix[4]  * matrix[10] * matrix[15] + 
              matrix[4]  * matrix[11] * matrix[14] + 
              matrix[8]  * matrix[6]  * matrix[15] - 
              matrix[8]  * matrix[7]  * matrix[14] - 
              matrix[12] * matrix[6]  * matrix[11] + 
              matrix[12] * matrix[7]  * matrix[10];

    inv[8] = matrix[4]  * matrix[9] * matrix[15] - 
             matrix[4]  * matrix[11] * matrix[13] - 
             matrix[8]  * matrix[5] * matrix[15] + 
             matrix[8]  * matrix[7] * matrix[13] + 
             matrix[12] * matrix[5] * matrix[11] - 
             matrix[12] * matrix[7] * matrix[9];

    inv[12] = -matrix[4]  * matrix[9] * matrix[14] + 
               matrix[4]  * matrix[10] * matrix[13] +
               matrix[8]  * matrix[5] * matrix[14] - 
               matrix[8]  * matrix[6] * matrix[13] - 
               matrix[12] * matrix[5] * matrix[10] + 
               matrix[12] * matrix[6] * matrix[9];

    inv[1] = -matrix[1]  * matrix[10] * matrix[15] + 
              matrix[1]  * matrix[11] * matrix[14] + 
              matrix[9]  * matrix[2] * matrix[15] - 
              matrix[9]  * matrix[3] * matrix[14] - 
              matrix[13] * matrix[2] * matrix[11] + 
              matrix[13] * matrix[3] * matrix[10];

    inv[5] = matrix[0]  * matrix[10] * matrix[15] - 
             matrix[0]  * matrix[11] * matrix[14] - 
             matrix[8]  * matrix[2] * matrix[15] + 
             matrix[8]  * matrix[3] * matrix[14] + 
             matrix[12] * matrix[2] * matrix[11] - 
             matrix[12] * matrix[3] * matrix[10];

    inv[9] = -matrix[0]  * matrix[9] * matrix[15] + 
              matrix[0]  * matrix[11] * matrix[13] + 
              matrix[8]  * matrix[1] * matrix[15] - 
              matrix[8]  * matrix[3] * matrix[13] - 
              matrix[12] * matrix[1] * matrix[11] + 
              matrix[12] * matrix[3] * matrix[9];

    inv[13] = matrix[0]  * matrix[9] * matrix[14] - 
              matrix[0]  * matrix[10] * matrix[13] - 
              matrix[8]  * matrix[1] * matrix[14] + 
              matrix[8]  * matrix[2] * matrix[13] + 
              matrix[12] * matrix[1] * matrix[10] - 
              matrix[12] * matrix[2] * matrix[9];

    inv[2] = matrix[1]  * matrix[6] * matrix[15] - 
             matrix[1]  * matrix[7] * matrix[14] - 
             matrix[5]  * matrix[2] * matrix[15] + 
             matrix[5]  * matrix[3] * matrix[14] + 
             matrix[13] * matrix[2] * matrix[7] - 
             matrix[13] * matrix[3] * matrix[6];

    inv[6] = -matrix[0]  * matrix[6] * matrix[15] + 
              matrix[0]  * matrix[7] * matrix[14] + 
              matrix[4]  * matrix[2] * matrix[15] - 
              matrix[4]  * matrix[3] * matrix[14] - 
              matrix[12] * matrix[2] * matrix[7] + 
              matrix[12] * matrix[3] * matrix[6];

    inv[10] = matrix[0]  * matrix[5] * matrix[15] - 
              matrix[0]  * matrix[7] * matrix[13] - 
              matrix[4]  * matrix[1] * matrix[15] + 
              matrix[4]  * matrix[3] * matrix[13] + 
              matrix[12] * matrix[1] * matrix[7] - 
              matrix[12] * matrix[3] * matrix[5];

    inv[14] = -matrix[0]  * matrix[5] * matrix[14] + 
               matrix[0]  * matrix[6] * matrix[13] + 
               matrix[4]  * matrix[1] * matrix[14] - 
               matrix[4]  * matrix[2] * matrix[13] - 
               matrix[12] * matrix[1] * matrix[6] + 
               matrix[12] * matrix[2] * matrix[5];

    inv[3] = -matrix[1] * matrix[6] * matrix[11] + 
              matrix[1] * matrix[7] * matrix[10] + 
              matrix[5] * matrix[2] * matrix[11] - 
              matrix[5] * matrix[3] * matrix[10] - 
              matrix[9] * matrix[2] * matrix[7] + 
              matrix[9] * matrix[3] * matrix[6];

    inv[7] = matrix[0] * matrix[6] * matrix[11] - 
             matrix[0] * matrix[7] * matrix[10] - 
             matrix[4] * matrix[2] * matrix[11] + 
             matrix[4] * matrix[3] * matrix[10] + 
             matrix[8] * matrix[2] * matrix[7] - 
             matrix[8] * matrix[3] * matrix[6];

    inv[11] = -matrix[0] * matrix[5] * matrix[11] + 
               matrix[0] * matrix[7] * matrix[9] + 
               matrix[4] * matrix[1] * matrix[11] - 
               matrix[4] * matrix[3] * matrix[9] - 
               matrix[8] * matrix[1] * matrix[7] + 
               matrix[8] * matrix[3] * matrix[5];

    inv[15] = matrix[0] * matrix[5] * matrix[10] - 
              matrix[0] * matrix[6] * matrix[9] - 
              matrix[4] * matrix[1] * matrix[10] + 
              matrix[4] * matrix[2] * matrix[9] + 
              matrix[8] * matrix[1] * matrix[6] - 
              matrix[8] * matrix[2] * matrix[5];

    det = matrix[0] * inv[0] + matrix[1] * inv[4] + matrix[2] * inv[8] + matrix[3] * inv[12];

    det = 1.0 / det;

    for (i = 0; i < 16; i++)
        inv[i] *= det;
}

double magnitute(double r[3])
{
	return sqrt(r[0]*r[0]+r[1]*r[1]+r[2]*r[2]);
}

void normalize(double r[3])
{
	double len=magnitute(r);
	r[0]/=len;
	r[1]/=len;
	r[2]/=len;
}
void scale(double a[3],double k)
{
	a[0]*=k;
	a[1]*=k;
	a[2]*=k;
}
double dot(double a[3], double b[3])
{
	return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];
}

void vector(double a[3],double b[3],double c[3])
{
	a[0]=b[0]-c[0];
	a[1]=b[1]-c[1];
	a[2]=b[2]-c[2];
}
