#include "wall.h"

void wall_init(struct wall *w) {
    Matrix3x3 m;
    vector3_sub(w->p1, w->p2, m);
    vector3_sub(w->p3, w->p2, m+3);

    vector3_add(w->p3, m, w->p4);

    vector3_cross(m, m+3, w->normal);
    vector3_normalize(w->normal, w->normal);

    vector3_copy(w->normal, m+6);
    matrix_invert(m, w->m);
    //DBG_MAT(m);
    //DBG_MAT(w->m);

    w->filled = 1;
}

void draw_wall(const struct wall *w) {
    glColor3fv(w->color);
    glBegin(GL_POLYGON);
    glVertex3fv(w->p1);
    glVertex3fv(w->p2);
    glVertex3fv(w->p3);
    glVertex3fv(w->p4);
    glEnd();
}

