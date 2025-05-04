#ifndef JOINT_H
#define JOINT_H

typedef struct Joint 
{
    double translation[3];
    double rotation[3];
    double scale[3];
    struct Joint* children;
    int n_children;

} Joint;

void init_joint(Joint* joint);
void animate_joint(Joint* joint, double time);

#endif
