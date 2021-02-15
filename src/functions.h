#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

/* Includes */

#include "vector.h"


/* Defines */

typedef struct Ball
{
    Vector center;
    double radius;
    double color;   /* Interval between 0 (dark) to 1 (light) */
    double coeff;   /* Interval between 0 and 1 how much the ball reflect light (1 means it's the perfect mirror) */
} ball;


/* Functions */

void invert(double inv[16],const double matrix[16]);

#endif
