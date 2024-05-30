#include "ui.h"

#define UI_DEFAULT_X_POSITION 10.0f
#define UI_DEFAULT_Y_POSITION 20.0f

void ui_draw_text(char text[], GLfloat x, GLfloat y, GLfloat viewport[4]) {
    glRasterPos2f(UI_DEFAULT_X_POSITION + x,
                  viewport[3] - UI_DEFAULT_Y_POSITION - y);

    while (*text != 0)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *(text++));
}

void ui_draw_stroke(char *text, GLfloat x, GLfloat y, GLfloat *viewport) {
    glRasterPos2f(UI_DEFAULT_X_POSITION + x,
                  viewport[3] - UI_DEFAULT_Y_POSITION - y);

    while (*text != 0)
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *(text++));
}

void ui_begin(GLfloat viewport[4]) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(viewport[0], viewport[2], viewport[1],
            viewport[3], -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
}

void ui_end() {
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}
