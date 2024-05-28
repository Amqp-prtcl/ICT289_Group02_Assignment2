#pragma once

#include "GL/freeglut.h"

void ui_begin(GLfloat viewport[4]);
void ui_end();

void ui_draw_text(char text[], GLfloat x, GLfloat y, GLfloat viewport[4]);
