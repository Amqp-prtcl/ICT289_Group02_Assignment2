#include "ui.h"

void ui_begin(GLfloat viewport[4]) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(viewport[0], viewport[2], viewport[1],
            viewport[3], -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void ui_end() {
    glPopMatrix();
}