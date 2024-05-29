#include "wall.h"

void wall_init(struct wall *w) {
    if (w->filled)
        return;

    Matrix3x3 m;
    vector3_sub(w->p1, w->p2, m);
    vector3_sub(w->p3, w->p2, m+3);

    vector3_add(w->p3, m, w->p4);

    vector3_cross(m, m+3, w->normal);
    vector3_normalize(w->normal, w->normal);

    vector3_copy(w->normal, m+6);
    // m is the transpose of what it should be (the change of basis matrix)
    matrix_invert(m, w->m);
    //DBG_MAT(m);
    //DBG_MAT(w->m);
    w->filled = 1;
}

void draw_wall(const struct wall *w) {
    //glPushMatrix();
    glColor3fv(w->color);

    glBegin(GL_LINES);
    glVertex3fv(w->p1);
    glVertex3fv(w->p2);
    glVertex3fv(w->p2);
    glVertex3fv(w->p3);
    glVertex3fv(w->p3);
    glVertex3fv(w->p4);
    glVertex3fv(w->p4);
    glVertex3fv(w->p1);
    glVertex3fv(w->p1);
    glVertex3fv(w->p3);
    glVertex3fv(w->p2);
    glVertex3fv(w->p4);
    glEnd();
    /*
    glBegin(GL_POLYGON);
    glVertex3fv(w->p1);
    glVertex3fv(w->p2);
    glVertex3fv(w->p3);
    glVertex3fv(w->p4);
    glEnd();

    glScalef(1, 1, 1);
    glWire*/
    //glPopMatrix();
}

