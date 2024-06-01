#include "table.h"

void draw_table(const struct table *table) {
    glPushMatrix();
    object_trans_apply(&table->trans);
    if (table->filled)
        for (size_t i = 0; i < table->walls_num; i++)
            draw_wall_filled(table->walls + i);
    else
        for (size_t i = 0; i < table->walls_num; i++)
            draw_wall(table->walls + i);

    glPopMatrix();
}

static void set_clip_plane(const size_t plane, const struct wall *w,
        const GLdouble a, const GLdouble b) {
    const GLdouble p[] = {a*w->normal[0], a*w->normal[1], a*w->normal[2],
        b * vector3_dot(w->p2, w->normal)};

    glClipPlane(GL_CLIP_PLANE0 + plane, p);
}

void table_load_clipping_planes() {
    /*
    set_clip_plane(0, walls + 2, 1, -1);
    set_clip_plane(1, walls + 4, -1, 1);
    set_clip_plane(2, walls + 6, 1, 1);
    set_clip_plane(3, walls + 7, -1, -1);
    */
}

void table_enable_clipping_planes() {
    glEnable(GL_CLIP_PLANE0);
    glEnable(GL_CLIP_PLANE1);
    glEnable(GL_CLIP_PLANE2);
    glEnable(GL_CLIP_PLANE3);
}

void table_disable_clipping_planes() {
    glDisable(GL_CLIP_PLANE0);
    glDisable(GL_CLIP_PLANE1);
    glDisable(GL_CLIP_PLANE2);
    glDisable(GL_CLIP_PLANE3);
}

