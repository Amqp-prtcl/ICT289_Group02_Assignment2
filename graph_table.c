#include "graph_table.h"

enum graph_type {
    TRIANGLE,
    RECTANGLE,
    POLYGON,
    BEZIER3,
};

struct graph_wall {
    Vector3 color;
    enum graph_type type;
    Vector3 p1;
    Vector3 p2;
    Vector3 p3;
    Vector3 p4;
};

static struct graph_wall walls[] = {
    {
        {1, 1, 1},
        BEZIER3,
        {0, 0, 0},
        {0, 1, 0},
        {0, 1, 1},
        {0.2, 1, 1,},
    },
};

static void check_graph_wall(struct graph_wall *w) {
    if (w->type != RECTANGLE)
        return;
    Vector3 a;
    vector3_sub(w->p2, w->p1, a);
    vector3_add(w->p3, a, w->p4);
}

void graph_table_init(struct graph_table *table) {
    object_trans_reset(&table->trans);
    table->walls = walls;
    table->walls_num = sizeof(walls) / sizeof(struct graph_wall);
    for (size_t i = 0; i < table->walls_num; i++)
        check_graph_wall(walls + i);
}

#define BEZIER_PREC 20.0
static void draw_graph_wall(const struct graph_wall *w) {
    Vector3 v, v1, d;
    glColor3fv(w->color);
    switch (w->type) {
        case TRIANGLE:
            glBegin(GL_TRIANGLES);
            glVertex3fv(w->p1);
            glVertex3fv(w->p2);
            glVertex3fv(w->p3);
            glEnd();
            break;
        case RECTANGLE:
        case POLYGON:
            glBegin(GL_POLYGON);
            glVertex3fv(w->p1);
            glVertex3fv(w->p2);
            glVertex3fv(w->p3);
            glVertex3fv(w->p4);
            glEnd();
            break;
        case BEZIER3:
            vector3_sub(w->p3, w->p4, d);
            glBegin(GL_QUAD_STRIP);
            glVertex3fv(w->p1);
            vector3_add(w->p1, d, v);
            glVertex3fv(v);
            for (GLfloat t = 0; t < 1.0; t += 1/BEZIER_PREC) {
                vector3_lerp(w->p1, w->p2, t, v);
                vector3_lerp(w->p2, w->p3, t, v1);
                vector3_lerp(v, v1, t, v);
                glVertex3fv(v);
                vector3_add(v, d, v);
                glVertex3fv(v);
            }
            glVertex3fv(w->p3);
            vector3_add(w->p3, d, v);
            glVertex3fv(v);
            glEnd();
            break;
        default:
            return;
    }
}

void draw_graph_table(const struct graph_table *table) {
    glPushMatrix();
    object_trans_apply(&table->trans);
    for (size_t i = 0; i < table->walls_num; i++)
        draw_graph_wall(table->walls + i);
    glPopMatrix();
}

