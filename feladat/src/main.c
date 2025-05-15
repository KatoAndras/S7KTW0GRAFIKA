
#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

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
#include <SDL.h>
#include <SDL_opengl.h>
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
void reshape(int w, int h) 
{
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
float getTime(void) 
{
    return SDL_GetTicks() / 1000.0f;
}


void renderScene(void) 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    camera_apply(&cam);

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
}


void handleKeyboard(SDL_Keysym keysym) 
{
    unsigned char key = (unsigned char)keysym.sym;
    if (keysym.sym == SDLK_PLUS || keysym.sym == SDLK_EQUALS) 
    {
        lightIntensity = fminf(lightIntensity + 0.1f, 2.0f);
    }
    else if (keysym.sym == SDLK_MINUS) 
    {
        lightIntensity = fmaxf(lightIntensity - 0.1f, 0.0f);
    }
    else if (keysym.sym == SDLK_ESCAPE) 
    {
        SDL_Event ev; ev.type = SDL_QUIT;
        SDL_PushEvent(&ev);
    }
    else 
    {
        camera_process_keyboard(&cam, key);
    }
}

void handleSpecial(SDL_Keysym keysym) 
{
    switch (keysym.sym) {
        case SDLK_LEFT:   camera_process_keyboard(&cam, 'a'); break;
        case SDLK_RIGHT:  camera_process_keyboard(&cam, 'd'); break;
        case SDLK_UP:     camera_process_keyboard(&cam, 'w'); break;
        case SDLK_DOWN:   camera_process_keyboard(&cam, 's'); break;
        case SDLK_F1:
            SDL_ShowSimpleMessageBox(
              SDL_MESSAGEBOX_INFORMATION,
              "Space Sugo",
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
              NULL
            );
            break;
        default: break;
    }
}


void handleMouseMotion(int x, int y) 
{
    camera_process_mouse(&cam, x, y);
}


void initScene(void) 
{
    glClearColor(0.0f,0.0f,0.05f,1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    {
        GLfloat amb[]  = {0.1f,0.1f,0.1f,1.0f};
        GLfloat diff[] = {lightIntensity,lightIntensity,lightIntensity,1.0f};
        GLfloat pos[]  = {0.0f,5.0f,5.0f,1.0f};
        glLightfv(GL_LIGHT0, GL_AMBIENT,  amb);
        glLightfv(GL_LIGHT0, GL_DIFFUSE,  diff);
        glLightfv(GL_LIGHT0, GL_POSITION, pos);
    }

    shaderProgram = loadShaderProgram("shaders/vertex.glsl","shaders/fragment.glsl");
    if (!shaderProgram) 
    {
        fprintf(stderr,"Shader létrehozási hiba!\n");
        exit(1);
    }

    loadOBJ("models/earth.obj",&earth);
    loadOBJ("models/moon.obj",&moon);
    loadOBJ("models/sun.obj",&sun);

    texEarth = loadTexture("textures/earth.jpg");
    texMoon  = loadTexture("textures/moon.jpg");
    texSun   = loadTexture("textures/sun.jpg");
}

int main(int argc, char **argv) 
{
    SDL_SetMainReady();
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) 
    {
        fprintf(stderr,"SDL init hiba: %s\n",SDL_GetError());
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);

    SDL_Window *win = SDL_CreateWindow(
        "Space SDL2",
        SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
        800,600,
        SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE
    );
    
    if (!win) 
    {
        fprintf(stderr,"Ablak hiba: %s\n",SDL_GetError());
        return -1;
    }
    SDL_GLContext glc = SDL_GL_CreateContext(win);
    if (!glc) 
    {
        fprintf(stderr,"GL kontextus hiba: %s\n",SDL_GetError());
        return -1;
    }

    #ifdef _WIN32
      if (!gladLoadGLLoader(getGLProc)) 
      {
    #else
      if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) 
      {
    #endif
        fprintf(stderr,"GLAD init FAILED\n");
        return -1;
    }


    int w,h;
    SDL_GetWindowSize(win,&w,&h);
    reshape(w,h);
    camera_init(&cam);
    initScene();


    bool running = true;
    SDL_Event ev;
    while (running) 
    {
        while (SDL_PollEvent(&ev)) 
        {
            switch (ev.type) 
            {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_WINDOWEVENT:
                    if (ev.window.event == SDL_WINDOWEVENT_RESIZED)
                        reshape(ev.window.data1,ev.window.data2);
                    break;
                case SDL_KEYDOWN:
                    handleKeyboard(ev.key.keysym);
                    handleSpecial(ev.key.keysym);
                    break;
                case SDL_MOUSEMOTION:
                    handleMouseMotion(ev.motion.x, ev.motion.y);
                    break;
            }
        }
        renderScene();
        SDL_GL_SwapWindow(win);
    }

    SDL_GL_DeleteContext(glc);
    SDL_DestroyWindow(win);

    SDL_Quit();

    return 0;
}
