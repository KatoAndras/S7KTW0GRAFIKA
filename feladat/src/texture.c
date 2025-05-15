#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "texture.h"
#include <stdio.h>

GLuint loadTexture(const char *path) 
{
    int w,h,n;
    unsigned char *data = stbi_load(path, &w, &h, &n, 4);
    if (!data) 
    { 
        fprintf(stderr,"Betoltes sikertelen: %s\n",path); return 0; 
    }

    GLuint tex; glGenTextures(1,&tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,w,h,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

    stbi_image_free(data);

    return tex;
}