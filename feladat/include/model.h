#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>

//adatok, indexek, indexek szamara egyedi kontruktor letrehozasa
typedef struct 
{
    GLuint vao;
    GLuint vbo;
    GLuint ebo;
    int indexCount;
} Model;

//.obj betoltee
int loadOBJ(const char *path, Model *outModel);

//model rajozolasa
void drawModel(const Model *m, GLuint tex);

#endif
