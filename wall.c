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
}

#define is_not_bound(a) a < 0.0 || a > 1.0
void wall_ball_collision(struct wall *w, struct ball *b,
        const Vector3 gravity, const GLfloat delta) {
    Vector3 v1, v2;
    GLfloat imp;

    vector3_sub(b->trans.position, w->p2, v1);
    matrix_vector_mul(w->m, v1, v2);

    if (v2[2] < -ball_get_radius(b) || v2[2] > ball_get_radius(b) ||
            is_not_bound(v2[0]) || is_not_bound(v2[1]))
        return;

    if (w->on_trigger != NULL) {
        DBG_PRINT("wall trigger\n");
        w->on_trigger(w, b);
    }
    if (w->is_trigger_only)
        return;

    vector3_affine(w->normal, SIGN(v2[2])*(ball_get_radius(b)-ABS(v2[2])),
            b->trans.position, b->trans.position);

    GLfloat frict_thresh = vector3_dot(gravity, w->normal);

    imp = vector3_dot(b->phys.speed, w->normal);
    if (imp <= frict_thresh + 0.01 && imp >= -frict_thresh - 0.01) {
        //DBG_PRINT("friction\n");
        vector3_affine(b->phys.speed, -w->friction_coef*delta,
                b->phys.speed, b->phys.speed);
        vector3_affine(w->normal, -imp,
                b->phys.speed, b->phys.speed);
        return;
    }

    //DBG_PRINT("collision\n");
    vector3_affine(w->normal, -2*imp, b->phys.speed, b->phys.speed);
    vector3_affine(b->phys.speed, -w->collision_coef,
            b->phys.speed, b->phys.speed);
}

