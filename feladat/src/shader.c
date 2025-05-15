#include "shader.h"
#include <stdio.h>
#include <stdlib.h>

static char* readFile(const char *path) 
{
    FILE *f = fopen(path,"rb"); 
    if(!f) 
    {
        fprintf(stderr, "A fajl nem talalhato: %s\n", path);
        exit(1);
    }
    fseek(f,0,SEEK_END); 
    long len = ftell(f); 
    fseek(f,0,SEEK_SET);
    char *buf = malloc(len+1); fread(buf,1,len,f); buf[len]=0; fclose(f);
    return buf;
}

GLuint loadShaderProgram(const char *vp, const char *fp) 
{
    char *vsrc = readFile(vp), *fsrc = readFile(fp);

    if(!vsrc||!fsrc) 
    { 
        fprintf(stderr,"Shader hiba\n"); return 0; 
    
    }
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs,1,(const char**)&vsrc,NULL);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs,1,(const char**)&fsrc,NULL);
    glCompileShader(fs);
    
    GLuint prog = glCreateProgram();
    glAttachShader(prog,vs); glAttachShader(prog,fs);
    glLinkProgram(prog);
    free(vsrc); free(fsrc);
    return prog;
}