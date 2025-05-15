
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifdef _WIN32
  #include <windows.h>
  static void* getGLProc(const char *name) 
  {
      void *p = (void*)wglGetProcAddress(name);
      if (p == NULL) 
      {
          HMODULE module = GetModuleHandleA("opengl32.dll");
          p = (void*)GetProcAddress(module, name);
      }
      return p;
  }
#endif

#include <glad/glad.h>
#include <GL/freeglut.h>
#include <GL/glu.h>

#include "camera.h"
#include "model.h"
#include "texture.h"
#include "shader.h"

//Deklaralom a globalis vlatozokat (ne legyen sok)
Camera cam;
Model earth, moon, sun;
GLuint texEarth, texMoon, texSun;
GLuint shaderProgram;
float lightIntensity = 1.0f;

//Ablakmeret valtas 
void reshape(int w, int h) {
    if (h == 0) h = 1;
    float aspect = (float)w / (float)h;
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 0.1, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//Animacio ideje (mp)
float getTime(void) {
    return glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
}


void renderScene(void) 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    camera_apply(&cam);

    //fenyero valtoztatasa texturan
    glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glColor3f(lightIntensity, lightIntensity, lightIntensity);

    float t = getTime();


    glPushMatrix();
      glRotatef(t * 5.0f, 0,1,0);
      drawModel(&sun, texSun);
    glPopMatrix();


    glPushMatrix();
      glRotatef(t * 20.0f, 0,1,0);
      glTranslatef(8,0,0);
      glRotatef(t * 50.0f, 0,1,0);
      drawModel(&earth, texEarth);
    glPopMatrix();


    glPushMatrix();
      glRotatef(t * 20.0f, 0,1,0);
      glTranslatef(8,0,0);
      glRotatef(t * 50.0f, 0,1,0);
      glRotatef(t * 80.0f, 0,1,0);
      glTranslatef(2,0,0);
      glRotatef(t * 100.0f, 0,1,0);
      drawModel(&moon, texMoon);
    glPopMatrix();

    glutSwapBuffers();

}


void keyboard(unsigned char key, int x, int y) 
{
    if (key=='+' || key=='=') 
    {
        lightIntensity = fminf(lightIntensity + 0.1f, 2.0f);
    }
    if (key=='-') 
    {
        lightIntensity = fmaxf(lightIntensity - 0.1f, 0.0f);
    }
    if (key==27) exit(0);

    camera_process_keyboard(&cam, key);
}

void special(int key, int x, int y) 
{
    switch(key) 
    {
        case GLUT_KEY_LEFT:  camera_process_keyboard(&cam,'a'); break;
        case GLUT_KEY_RIGHT: camera_process_keyboard(&cam,'d'); break;
        case GLUT_KEY_UP:    camera_process_keyboard(&cam,'w'); break;
        case GLUT_KEY_DOWN:  camera_process_keyboard(&cam,'s'); break;
        case GLUT_KEY_F1:
            MessageBoxA(
                NULL,
                "  W:   elore\n"
                "  A:   balra\n"
                "  S:   hatra\n"
                "  D:   jobbra\n"
                "  Q:   fel\n"
                "  E:   le\n"
                "  Nyilak:  mozgas\n"
                "  Eger:    nezelodes\n"
                "  + / - :  fenyero novelese/csokkentese\n"
                "  F1:  sugo megjelenitese\n"
                "  Esc: kilepes",
                "Space Sugo",
                MB_OK | MB_ICONINFORMATION
            );
            break;
    }
}

void mouseMotion(int x, int y) 
{
    camera_process_mouse(&cam, x, y);
}


void initScene(void) 
{
    glClearColor(0.0f, 0.0f, 0.05f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    {
        GLfloat amb[] = { 0.1f, 0.1f, 0.1f, 1.0f };
        GLfloat diff[] = { lightIntensity, lightIntensity, lightIntensity, 1.0f };
        GLfloat pos[] = { 0.0f, 5.0f, 5.0f, 1.0f };
        glLightfv(GL_LIGHT0, GL_AMBIENT,  amb);
        glLightfv(GL_LIGHT0, GL_DIFFUSE,  diff);
        glLightfv(GL_LIGHT0, GL_POSITION, pos);
    }

    shaderProgram = loadShaderProgram("shaders/vertex.glsl", "shaders/fragment.glsl");
    if (!shaderProgram) 
    {
        fprintf(stderr, "Shader letrehozasi hiba!\n");
        exit(1);
    }

    loadOBJ("models/earth.obj", &earth);
    loadOBJ("models/moon.obj", &moon);
    loadOBJ("models/sun.obj", &sun);

    texEarth = loadTexture("textures/earth.jpg");
    texMoon  = loadTexture("textures/moon.jpg");
    texSun   = loadTexture("textures/sun.jpg");
}

int main(int argc, char **argv) 
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Space");

    glutReshapeFunc(reshape);

    #ifdef _WIN32
      if (!gladLoadGLLoader(getGLProc)) 
      {
        #else
        if (!gladLoadGLLoader((GLADloadproc)glutGetProcAddress)) 
        {
        #endif
        fprintf(stderr, "GLAD init FAILED\n");
        return -1;
    }

    reshape(800, 600);

    camera_init(&cam);
    initScene();

    glutDisplayFunc(renderScene);
    glutIdleFunc(renderScene);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutPassiveMotionFunc(mouseMotion);

    glutMainLoop();

    return 0;
    
}

