#include "camera.h"
#define _USE_MATH_DEFINES
#include <math.h>

static int lastX = 0, lastY = 0;
static int firstMouse = 1;

void camera_init(Camera *cam) 
{
    cam->pos[0] = 0; cam->pos[1] = 0; cam->pos[2] = 5;
    cam->yaw = -90.0f; cam->pitch = 0.0f;
}

void camera_apply(const Camera *cam) 
{
    //Kamerat eltolom, majd forgatim
    glTranslatef(-cam->pos[0], -cam->pos[1], -cam->pos[2]);
    glRotatef(-cam->yaw,   0,1,0);
    glRotatef(-cam->pitch, 1,0,0);
}

void camera_process_keyboard(Camera *cam, unsigned char key) 
{
    float speed = 0.2f;
    float front[3] = 
    {
        cosf(cam->yaw * M_PI/180.0f) * cosf(cam->pitch * M_PI/180.0f),
        sinf(cam->pitch * M_PI/180.0f),
        sinf(cam->yaw * M_PI/180.0f) * cosf(cam->pitch * M_PI/180.0f)
    };

    float right[3] = 
    {
        -front[2], 0, front[0]
    };

    switch(key) 
    {
      case 'w':
        for(int i=0;i<3;i++) cam->pos[i] += front[i]*speed;
        break;
      case 's':
        for(int i=0;i<3;i++) cam->pos[i] -= front[i]*speed;
        break;
      case 'a':
        for(int i=0;i<3;i++) cam->pos[i] -= right[i]*speed;
        break;
      case 'd':
        for(int i=0;i<3;i++) cam->pos[i] += right[i]*speed;
        break;
      case 'q':
        cam->pos[1] += speed;
        break;
      case 'e':
        cam->pos[1] -= speed;
        break;
    }
}

void camera_process_mouse(Camera *cam, int x, int y) 
{
    if (firstMouse) 
    { 
      lastX = x; lastY = y; firstMouse=0; 
    }
    float xoffset = x - lastX;
    float yoffset = lastY - y;
    lastX = x; lastY = y;
    float sensitivity = 0.1f;

    cam->yaw   += xoffset * sensitivity;
    cam->pitch += yoffset * sensitivity;
    if(cam->pitch > 89.0f) cam->pitch = 89.0f;
    if(cam->pitch < -89.0f) cam->pitch = -89.0f;
}