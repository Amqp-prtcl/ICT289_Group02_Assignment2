#include "ui.h"
#include "vector.h"

#include "stdio.h"

#define UI_DEFAULT_X_POSITION 10.0f
#define UI_DEFAULT_Y_POSITION 20.0f

#define LINE_HEIGHT 20.0

static int y_offset;
static Vector4 viewport;

void ui_printf(const char *fmt, ...) {
    char *d;

    va_list v;
    va_start(v, fmt);
    vasprintf(&d, fmt, v);
    va_end(v);

    ui_draw_text(d, 0, y_offset);
    free(d);

    y_offset += LINE_HEIGHT;
}

void ui_draw_text(const char *text, GLfloat x, GLfloat y) {
    glRasterPos2f(UI_DEFAULT_X_POSITION + x,
                  viewport[3] - UI_DEFAULT_Y_POSITION - y);

    while (*text != 0)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *(text++));
}

void ui_begin() {
    y_offset = 0;
    glGetFloatv(GL_VIEWPORT, viewport);

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
