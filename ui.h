#pragma once

#include "GL/freeglut.h"

void ui_begin(void);
void ui_end(void);

void ui_printf(const char *fmt, ...);
void ui_draw_text(const char *text, GLfloat x, GLfloat y);

