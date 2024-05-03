#include "shape.h"

void draw_off(const struct off *off) {
    struct off_triangle *triangles = off->triangles;
    Vector3 *vertices = off->vertices;

    struct off_triangle face;
    for (size_t i = 0; i < off->nfaces; i++) {
        face = triangles[i];

        glBegin(GL_POLYGON);
        glColor3f(0.5, 0.5, 0.5);
        glVertex3fv(vertices[face.p1]);
        glVertex3fv(vertices[face.p2]);
        glVertex3fv(vertices[face.p3]);
        glEnd();
    }
}

void draw_shape(const struct object_trans *trans,
        const struct off *off) {
    glPushMatrix();

    object_trans_apply(trans);

    draw_off(off);

    glPopMatrix();
}

