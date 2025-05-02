#ifndef TEXTURE_H
#define TEXTURE_H
#include <GL/gl.h>

unsigned int load_texture(const char* filename);
unsigned int create_checker_texture();

typedef GLubyte Pixel[3];

/**
 * Load texture from file and returns with the texture name.
 */
GLuint load_texture(char* filename);

#endif /* TEXTURE_H */
