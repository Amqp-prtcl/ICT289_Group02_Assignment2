#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

//#include <GL/glew.h>
#include <GL/freeglut.h>

#include <stdio.h>
#include <math.h>

//GLuint initShader(GLuint);
GLuint LoadTex(const char*);
//char* readShaderSource(const char*);
//GLuint loadShader(GLenum, const char*);
GLuint* LoadAllTex(char**, size_t); 

void draw_texture(GLuint id);

#endif

