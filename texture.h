#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include <GL/freeglut.h>

#include <stdio.h>
#include <math.h>

GLuint LoadTex(const char*);
GLuint* LoadAllTex(char**, size_t);

void draw_texture(GLuint id);

#endif

