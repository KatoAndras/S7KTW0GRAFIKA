#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>

typedef struct 
{
    float pos[3];
    float yaw, pitch;
} Camera;

void camera_init(Camera *cam);
void camera_apply(const Camera *cam);
void camera_process_keyboard(Camera *cam, unsigned char key);
void camera_process_mouse(Camera *cam, int x, int y);

#endif