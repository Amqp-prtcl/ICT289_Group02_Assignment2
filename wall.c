#include "wall.h"
#include "material.h"

void wall_init(struct wall *w) {
    if (w->filled)
        return;

    Matrix3x3 m;
    vector3_sub(w->p1, w->p2, m);
    vector3_sub(w->p3, w->p2, m+3);

    vector3_cross(m, m+3, m+6);
    vector3_normalize(m+6, m+6);

    vector3_copy(m+6, w->normal);
    vector3_add(w->p3, m, w->p4);
    // m is the transpose of what it should be (the change of basis matrix)
    matrix_invert(m, w->m);
    w->filled = 1;
}

void draw_wall(const struct wall *w) {
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
    glEnable(GL_LIGHTING);
    apply_material(get_mat(BALL));
    glColor4f(1, 1, 1, 1);
    glBegin(GL_QUADS);
    glVertex3fv(w->p1);
    glVertex3fv(w->p2);
    glVertex3fv(w->p3);
    glVertex3fv(w->p4);
    glEnd();
    glDisable(GL_LIGHTING);
    */
}

