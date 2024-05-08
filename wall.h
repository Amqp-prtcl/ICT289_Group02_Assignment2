#pragma once

#include "vector.h"

struct wall {
    Vector3 color;
    Vector3 p1;
    Vector3 p2;
    Vector3 p3;

    Vector3 normal;
};

static void fill_normal(struct wall *w) {
    Vector3 a, b;
    vector3_sub(w->p2, w->p1, a);
    vector3_sub(w->p2, w->p3, b);
    vector3_cross(a, b, w->normal);
}

static GLfloat get_dist_from_plane(const struct wall *w, const Vector3 v) {
    Vector3 p;
    vector3_sub(v, w->p1, p);
    return vector3_dot(w->normal, p);
}

static int is_point_on_wall(const struct wall *w, const Vector3 v) {
    return v[0] >= w->p1[0] && v[0] <= w->p2[0] &&
        v[1] >= w->p1[1] && v[1] <= w->p2[1] &&
        v[2] >= w->p1[2] && v[2] <= w->p2[2];
}
