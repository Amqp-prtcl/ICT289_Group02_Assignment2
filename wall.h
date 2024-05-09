#pragma once

#include "vector.h"

/*
 *  p1               p2
 *  +------ v1 ----->+
 *                   |
 *                   v2
 *                   |
 *                   \/
 *  +                +
 *  p4               p3
 *
 *
 *  Note: p4, v1, v2 and the normal vector are computed from p1, p2 and p3 (no
 *  need to fill them at structure creation)
 */


struct wall {
    Vector3 color;
    Vector3 p1;
    Vector3 p2;
    Vector3 p3;

    // should be automatically filled by CHECK_WALL()
    Vector3 p4;
    Vector3 v1;
    Vector3 v2;
    Vector3 normal;

    // if one or more of the three initial points (p1, p2 and/or p3) are
    // changed, you will probably need to set filled to false (0)
    int filled;
};

#define CHECK_WALL(w) if (!w->filled) precompute_wall(w);

static void precompute_wall(struct wall *w) {
    vector3_sub(w->p1, w->p2, w->v1);
    vector3_sub(w->p3, w->p2, w->v2);

    vector3_add(w->p3, w->v1, w->p4);

    vector3_cross(w->v1, w->v2, w->normal);
    vector3_normalize(w->normal, w->normal);


    w->filled = 1;
}

static GLfloat get_dist_from_plane(const struct wall *w, const Vector3 v) {
    Vector3 p;
    vector3_sub(v, w->p1, p);
    return vector3_dot(w->normal, p);
}

static int is_point_on_wall(const struct wall *w, const Vector3 v) {
    Vector3 dv1;
    vector3_sub(w->p1, v, dv1);


    return v[0] >= w->p1[0] && v[0] <= w->p2[0] &&
        v[1] >= w->p1[1] && v[1] <= w->p2[1] &&
        v[2] >= w->p1[2] && v[2] <= w->p2[2];
}
