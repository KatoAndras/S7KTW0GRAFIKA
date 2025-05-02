#include "scene.h"

#include <GL/gl.h>

void init_scene(Scene* scene)
{
}

void update_scene(Scene* scene)
{
}

void render_scene(const Scene* scene)
{
    draw_origin();
glBegin(GL_QUADS);

glColor3f(1, 0, 0);
glVertex3f(0, 0, 0);
glVertex3f(0, 0, 1);
glVertex3f(1, 0, 1);
glVertex3f(1, 0, 0);

glColor3f(0, 1, 0);
glVertex3f(0, 0, 0);
glVertex3f(0, 0, 1);
glVertex3f(1, 0, 1);
glVertex3f(1, 0, 0);

glEnd();

//Task 3
glBegin(GL_TRIANGLES);

    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.2f, 0.0f);

    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(-0.2f, -0.2f, 0.0f);

    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(0.2f, -0.2f, 0.0f);

glEnd();

//Task 4
glColor3f(0.5f, 0.5f, 0.5f);
GLUquadric* quad;
quad = gluNewQuadric();

glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    gluSphere(quad, 0.3, 40, 40);
glPopMatrix();
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}
