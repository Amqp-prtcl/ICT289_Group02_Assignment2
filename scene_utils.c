#include "scene_utils.h"
#include "vector.h"
#include "math.h"

void draw_circle(GLfloat cx, GLfloat cy, GLfloat r, GLfloat prec) {
    GLfloat x, y, t, inc = 1/prec;
    glBegin(GL_POLYGON);
    for (GLfloat i = 0; i < prec; i += inc) {
        t = 2.0f * 3.1415926f * i;
        x = r * cosf(t);
        y = r * sinf(t);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void draw_wire_circle(GLfloat cx, GLfloat cy, GLfloat r, GLfloat prec) {
    GLfloat x, y, t, inc = 1/prec;
    glBegin(GL_LINE_LOOP);
    for (GLfloat i = 0; i < prec; i += inc) {
        t = 2.0f * 3.1415926f * i;
        x = r * cosf(t);
        y = r * sinf(t);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}

void draw_grid(GLfloat cell_length, int grid_length) {
    GLfloat grid_size = cell_length * grid_length;
    for (int i = -grid_length; i <= grid_length; i++) {
        glBegin(GL_LINES);
        glColor3f(.3, .3, .3);
        glVertex3f(-grid_size, 0, i * cell_length);
        glVertex3f(grid_size, 0, i * cell_length);
        glEnd();

        glBegin(GL_LINES);
        glColor3f(.3, .3, .3);
        glVertex3f(i*cell_length, 0, -grid_size);
        glVertex3f(i*cell_length, 0, grid_size);
        glEnd();
    }
}

void draw_axis() {
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);
    glEnd();
}

void draw_cube() {
    Point3 verts[8] = {
        {-.5, -.5, 0.5},
        {0.5, -.5, 0.5},
        {0.5, 0.5, 0.5},
        {-.5, 0.5, 0.5},
        {-.5, -.5, -.5},
        {0.5, -.5, -.5},
        {0.5, 0.5, -.5},
        {-.5, 0.5, -.5},
    };

    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0);
    glVertex3fv(verts[0]);
    glVertex3fv(verts[1]);
    glVertex3fv(verts[2]);
    glVertex3fv(verts[3]);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 1, 0);
    glVertex3fv(verts[1]);
    glVertex3fv(verts[5]);
    glVertex3fv(verts[6]);
    glVertex3fv(verts[2]);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 0, 1);
    glVertex3fv(verts[3]);
    glVertex3fv(verts[2]);
    glVertex3fv(verts[6]);
    glVertex3fv(verts[7]);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0, 1, 1);
    glVertex3fv(verts[4]);
    glVertex3fv(verts[0]);
    glVertex3fv(verts[3]);
    glVertex3fv(verts[7]);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 0);
    glVertex3fv(verts[5]);
    glVertex3fv(verts[4]);
    glVertex3fv(verts[7]);
    glVertex3fv(verts[6]);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1, 0, 1);
    glVertex3fv(verts[0]);
    glVertex3fv(verts[4]);
    glVertex3fv(verts[5]);
    glVertex3fv(verts[1]);
    glEnd();
}

