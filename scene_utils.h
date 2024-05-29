#pragma once

#include "GL/freeglut.h"

void drawGrid(GLfloat cell_length, int grid_length);

void drawAxis(void);

void drawcube(void);

void draw_wire_circle(GLfloat cx, GLfloat cy, GLfloat r, GLfloat prec);
void draw_circle(GLfloat cx, GLfloat cy, GLfloat r, GLfloat prec);

