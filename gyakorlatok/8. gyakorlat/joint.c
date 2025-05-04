#include "joint.h"
#include <math.h>
#include <cstddef>

#define PI 3.14
#define MAX_ANGLE (30.0 * PI / 180.0)
#define PERIOD 3.0

void init_joint(Joint* joint) 
{
    joint->translation[0] = 0;
    joint->translation[1] = 0;
    joint->translation[2] = 0;

    joint->rotation[0] = 0;
    joint->rotation[1] = 0;
    joint->rotation[2] = 0;

    joint->scale[0] = 1;
    joint->scale[1] = 1;
    joint->scale[2] = 1;

    joint->children = NULL;
    joint->n_children = 0;
}

void animate_joint(Joint* joint, double time) 
{
    double angle = MAX_ANGLE * sin(PI * time / PERIOD);
    
    joint->rotation[0] = angle; 
}
