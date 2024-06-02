#include "graph_table.h"

enum graph_type {
    TRIANGLE,
    RECTANGLE,
    POLYGON,
    BEZIER3,
    B,
};

struct graph_wall {
    Vector3 color;
    enum graph_type type;
    Vector3 p1;
    Vector3 p2;
    Vector3 p3;
    Vector3 p4;
};

// {0.5, 0.25, 0}, --> Brown

static struct graph_wall walls[] = {
        // Table ground
    {
        {0, 1, 0},
        RECTANGLE,
        {PLAYFIELD_LENGTH/2+HOLE_RADIUS, 0, -PLAYFIELD_WIDTH/2-HOLE_RADIUS},
        {PLAYFIELD_LENGTH/2+HOLE_RADIUS, 0, PLAYFIELD_WIDTH/2+HOLE_RADIUS},
        {-PLAYFIELD_LENGTH/2-HOLE_RADIUS, 0, PLAYFIELD_WIDTH/2+HOLE_RADIUS},
    },
        // Table INSIDE sides
    // Side width
    {
        {0, 0, 1},
        RECTANGLE,
        {PLAYFIELD_LENGTH/2+HOLE_RADIUS/2, 0, -PLAYFIELD_WIDTH/2+HOLE_RADIUS},
        {PLAYFIELD_LENGTH/2+HOLE_RADIUS/2, 0, PLAYFIELD_WIDTH/2-HOLE_RADIUS},
        {PLAYFIELD_LENGTH/2, TABLE_HEIGHT-0.005, PLAYFIELD_WIDTH/2-HOLE_RADIUS},
    },
    {
        {1, 0, 1},
        RECTANGLE,
        {PLAYFIELD_LENGTH/2, TABLE_HEIGHT-0.005, -PLAYFIELD_WIDTH/2+HOLE_RADIUS},
        {PLAYFIELD_LENGTH/2, TABLE_HEIGHT-0.005, PLAYFIELD_WIDTH/2-HOLE_RADIUS},
        {PLAYFIELD_LENGTH/2, TABLE_HEIGHT, PLAYFIELD_WIDTH/2-HOLE_RADIUS},
    },
    // Side length
    // 1/2
    {
        {0, 0, 1},
        RECTANGLE,
        {PLAYFIELD_LENGTH/2-HOLE_RADIUS, 0, PLAYFIELD_WIDTH/2+HOLE_RADIUS/2},
        {HOLE_RADIUS, 0, PLAYFIELD_WIDTH/2+HOLE_RADIUS/2},
        {HOLE_RADIUS, TABLE_HEIGHT-0.005, PLAYFIELD_WIDTH/2},
    },
    {
        {1, 0, 1},
        RECTANGLE,
        {PLAYFIELD_LENGTH/2-HOLE_RADIUS, TABLE_HEIGHT-0.005, PLAYFIELD_WIDTH/2},
        {HOLE_RADIUS, TABLE_HEIGHT-0.005, PLAYFIELD_WIDTH/2},
        {HOLE_RADIUS, TABLE_HEIGHT, PLAYFIELD_WIDTH/2},
    },
    // 2/2
        {
        {0, 0, 1},
        RECTANGLE,
        {-HOLE_RADIUS, 0, PLAYFIELD_WIDTH/2+HOLE_RADIUS/2},
        {-PLAYFIELD_LENGTH/2+HOLE_RADIUS, 0, PLAYFIELD_WIDTH/2+HOLE_RADIUS/2},
        {-PLAYFIELD_LENGTH/2+HOLE_RADIUS, TABLE_HEIGHT-0.005, PLAYFIELD_WIDTH/2},
    },
    {
        {1, 0, 1},
        RECTANGLE,
        {-HOLE_RADIUS, TABLE_HEIGHT-0.005, PLAYFIELD_WIDTH/2},
        {-PLAYFIELD_LENGTH/2+HOLE_RADIUS, TABLE_HEIGHT-0.005, PLAYFIELD_WIDTH/2},
        {-PLAYFIELD_LENGTH/2+HOLE_RADIUS, TABLE_HEIGHT, PLAYFIELD_WIDTH/2},
    },
    // Side width
    {
        {0, 0, 1},
        RECTANGLE,
        {-PLAYFIELD_LENGTH/2-HOLE_RADIUS/2, 0, PLAYFIELD_WIDTH/2-HOLE_RADIUS},
        {-PLAYFIELD_LENGTH/2-HOLE_RADIUS/2, 0, -PLAYFIELD_WIDTH/2+HOLE_RADIUS},
        {-PLAYFIELD_LENGTH/2, TABLE_HEIGHT-0.005, -PLAYFIELD_WIDTH/2+HOLE_RADIUS},
    },
    {
        {1, 0, 1},
        RECTANGLE,
        {-PLAYFIELD_LENGTH/2, TABLE_HEIGHT-0.005, PLAYFIELD_WIDTH/2-HOLE_RADIUS},
        {-PLAYFIELD_LENGTH/2, TABLE_HEIGHT-0.005, -PLAYFIELD_WIDTH/2+HOLE_RADIUS},
        {-PLAYFIELD_LENGTH/2, TABLE_HEIGHT, -PLAYFIELD_WIDTH/2+HOLE_RADIUS},
    },
    // Side length
    // 1/2
    {
        {0, 0, 1},
        RECTANGLE,
        {-PLAYFIELD_LENGTH/2+HOLE_RADIUS, 0, -PLAYFIELD_WIDTH/2-HOLE_RADIUS/2},
        {-HOLE_RADIUS, 0, -PLAYFIELD_WIDTH/2-HOLE_RADIUS/2},
        {-HOLE_RADIUS, TABLE_HEIGHT-0.005, -PLAYFIELD_WIDTH/2},
    },
    {
        {1, 0, 1},
        RECTANGLE,
        {-PLAYFIELD_LENGTH/2+HOLE_RADIUS, TABLE_HEIGHT-0.005, -PLAYFIELD_WIDTH/2},
        {-HOLE_RADIUS, TABLE_HEIGHT-0.005, -PLAYFIELD_WIDTH/2},
        {-HOLE_RADIUS, TABLE_HEIGHT, -PLAYFIELD_WIDTH/2},
    },
    // 2/2
        {
        {0, 0, 1},
        RECTANGLE,
        {HOLE_RADIUS, 0, -PLAYFIELD_WIDTH/2-HOLE_RADIUS/2},
        {PLAYFIELD_LENGTH/2-HOLE_RADIUS, 0, -PLAYFIELD_WIDTH/2-HOLE_RADIUS/2},
        {PLAYFIELD_LENGTH/2-HOLE_RADIUS, TABLE_HEIGHT-0.005, -PLAYFIELD_WIDTH/2},
    },
    {
        {1, 0, 1},
        RECTANGLE,
        {HOLE_RADIUS, TABLE_HEIGHT-0.005, -PLAYFIELD_WIDTH/2},
        {PLAYFIELD_LENGTH/2-HOLE_RADIUS, TABLE_HEIGHT-0.005, -PLAYFIELD_WIDTH/2},
        {PLAYFIELD_LENGTH/2-HOLE_RADIUS, TABLE_HEIGHT, -PLAYFIELD_WIDTH/2},
    },
        // Table OUTSIDE sides
    {
        {0,1,0},
        RECTANGLE,
        {TABLE_LENGTH/2, 0, -TABLE_WIDTH/2+TABLE_HEIGHT},
        {TABLE_LENGTH/2, 0, TABLE_WIDTH/2-TABLE_HEIGHT},
        {TABLE_LENGTH/2, TABLE_HEIGHT, TABLE_WIDTH/2-TABLE_HEIGHT},
    },
    {
        {0,1,0},
        RECTANGLE,
        {TABLE_LENGTH/2-HOLE_RADIUS, 0, TABLE_WIDTH/2},
        {-TABLE_LENGTH/2+HOLE_RADIUS, 0, TABLE_WIDTH/2},
        {-TABLE_LENGTH/2+HOLE_RADIUS, TABLE_HEIGHT, TABLE_WIDTH/2},
    },
    {
        {0,1,0},
        RECTANGLE,
        {-TABLE_LENGTH/2, 0, TABLE_WIDTH/2-HOLE_RADIUS},
        {-TABLE_LENGTH/2, 0, -TABLE_WIDTH/2+HOLE_RADIUS},
        {-TABLE_LENGTH/2, TABLE_HEIGHT, -TABLE_WIDTH/2+HOLE_RADIUS},
    },
    {
        {0,1,0},
        RECTANGLE,
        {-TABLE_LENGTH/2+HOLE_RADIUS, 0, -TABLE_WIDTH/2},
        {TABLE_LENGTH/2-HOLE_RADIUS, 0, -TABLE_WIDTH/2},
        {TABLE_LENGTH/2-HOLE_RADIUS, TABLE_HEIGHT, -TABLE_WIDTH/2},
    },
        // Corner table EXTERIOR
    {
        {1, 0, 0},
        BEZIER3,
        {TABLE_LENGTH/2, 0, TABLE_WIDTH/2-HOLE_RADIUS},
        {TABLE_LENGTH/2, 0, TABLE_WIDTH/2},
        {TABLE_LENGTH/2-HOLE_RADIUS, 0, TABLE_WIDTH/2},
        {TABLE_LENGTH/2-HOLE_RADIUS, -TABLE_HEIGHT, TABLE_WIDTH/2},
    },
    {
        {1, 0, 0},
        BEZIER3,
        {-TABLE_LENGTH/2+HOLE_RADIUS, 0, TABLE_WIDTH/2},
        {-TABLE_LENGTH/2, 0, TABLE_WIDTH/2},
        {-TABLE_LENGTH/2, 0, TABLE_WIDTH/2-HOLE_RADIUS},
        {-TABLE_LENGTH/2, -TABLE_HEIGHT, TABLE_WIDTH/2-HOLE_RADIUS},
    },
    {
        {1, 0, 0},
        BEZIER3,
        {-TABLE_LENGTH/2, 0, -TABLE_WIDTH/2+HOLE_RADIUS},
        {-TABLE_LENGTH/2, 0, -TABLE_WIDTH/2},
        {-TABLE_LENGTH/2+HOLE_RADIUS, 0, -TABLE_WIDTH/2},
        {-TABLE_LENGTH/2+HOLE_RADIUS, -TABLE_HEIGHT, -TABLE_WIDTH/2},
    },
    {
        {1, 0, 0},
        BEZIER3,
        {TABLE_LENGTH/2-HOLE_RADIUS, 0, -TABLE_WIDTH/2},
        {TABLE_LENGTH/2, 0, -TABLE_WIDTH/2},
        {TABLE_LENGTH/2, 0, -TABLE_WIDTH/2+HOLE_RADIUS},
        {TABLE_LENGTH/2, -TABLE_HEIGHT, -TABLE_WIDTH/2+HOLE_RADIUS},
    },
        // Corner table INTERIOR
    {
        {0.5, 0.5, 0.5},
        BEZIER3,
        {PLAYFIELD_LENGTH/2+HOLE_RADIUS, 0, PLAYFIELD_WIDTH/2},
        {PLAYFIELD_LENGTH/2+HOLE_RADIUS, 0, PLAYFIELD_WIDTH/2+HOLE_RADIUS},
        {PLAYFIELD_LENGTH/2, 0, PLAYFIELD_WIDTH/2+HOLE_RADIUS},
        {PLAYFIELD_LENGTH/2, -TABLE_HEIGHT, PLAYFIELD_WIDTH/2+HOLE_RADIUS},
    },
    {
        {0.5, 0.5, 0.5},
        BEZIER3,
        {-PLAYFIELD_LENGTH/2-HOLE_RADIUS, 0, PLAYFIELD_WIDTH/2},
        {-PLAYFIELD_LENGTH/2-HOLE_RADIUS, 0, PLAYFIELD_WIDTH/2+HOLE_RADIUS},
        {-PLAYFIELD_LENGTH/2, 0, PLAYFIELD_WIDTH/2+HOLE_RADIUS},
        {-PLAYFIELD_LENGTH/2, -TABLE_HEIGHT, PLAYFIELD_WIDTH/2+HOLE_RADIUS},
    },
    {
        {0.5, 0.5, 0.5},
        BEZIER3,
        {-PLAYFIELD_LENGTH/2-HOLE_RADIUS, 0, -PLAYFIELD_WIDTH/2},
        {-PLAYFIELD_LENGTH/2-HOLE_RADIUS, 0, -PLAYFIELD_WIDTH/2-HOLE_RADIUS},
        {-PLAYFIELD_LENGTH/2, 0, -PLAYFIELD_WIDTH/2-HOLE_RADIUS},
        {-PLAYFIELD_LENGTH/2, -TABLE_HEIGHT, -PLAYFIELD_WIDTH/2-HOLE_RADIUS},
    },
    {
        {0.5, 0.5, 0.5},
        BEZIER3,
        {PLAYFIELD_LENGTH/2+HOLE_RADIUS, 0, -PLAYFIELD_WIDTH/2},
        {PLAYFIELD_LENGTH/2+HOLE_RADIUS, 0, -PLAYFIELD_WIDTH/2-HOLE_RADIUS},
        {PLAYFIELD_LENGTH/2, 0, -PLAYFIELD_WIDTH/2-HOLE_RADIUS},
        {PLAYFIELD_LENGTH/2, -TABLE_HEIGHT, -PLAYFIELD_WIDTH/2-HOLE_RADIUS},
    },
        // Corner table LINK
    {
        {0.5, 0.5, 0.5},
        B,
        {TABLE_LENGTH/2, TABLE_HEIGHT, TABLE_WIDTH/2-HOLE_RADIUS},
        {TABLE_LENGTH/2, TABLE_HEIGHT, TABLE_WIDTH/2},
        {TABLE_LENGTH/2-HOLE_RADIUS, TABLE_HEIGHT, TABLE_WIDTH/2},
        {PLAYFIELD_LENGTH/2, TABLE_HEIGHT, PLAYFIELD_WIDTH/2+HOLE_RADIUS},
    },
    {
        {0.5, 0.5, 0.5},
        B,
        {-TABLE_LENGTH/2+HOLE_RADIUS, TABLE_HEIGHT, TABLE_WIDTH/2},
        {-TABLE_LENGTH/2, TABLE_HEIGHT, TABLE_WIDTH/2},
        {-TABLE_LENGTH/2, TABLE_HEIGHT, TABLE_WIDTH/2-HOLE_RADIUS},
        {-PLAYFIELD_LENGTH/2-HOLE_RADIUS, TABLE_HEIGHT, PLAYFIELD_WIDTH/2},
    },
    {
        {0.5, 0.5, 0.5},
        B,
        {-TABLE_LENGTH/2, TABLE_HEIGHT, -TABLE_WIDTH/2+HOLE_RADIUS},
        {-TABLE_LENGTH/2, TABLE_HEIGHT, -TABLE_WIDTH/2},
        {-TABLE_LENGTH/2+HOLE_RADIUS, TABLE_HEIGHT, -TABLE_WIDTH/2},
        {-PLAYFIELD_LENGTH/2, TABLE_HEIGHT, -PLAYFIELD_WIDTH/2-HOLE_RADIUS},
    },
    {
        {0.5, 0.5, 0.5},
        B,
        {TABLE_LENGTH/2-HOLE_RADIUS, TABLE_HEIGHT, -TABLE_WIDTH/2},
        {TABLE_LENGTH/2, TABLE_HEIGHT, -TABLE_WIDTH/2},
        {TABLE_LENGTH/2, TABLE_HEIGHT, -TABLE_WIDTH/2+HOLE_RADIUS},
        {PLAYFIELD_LENGTH/2+HOLE_RADIUS, TABLE_HEIGHT, -PLAYFIELD_WIDTH/2},
    },
        // Corner table MIDDLE
    {
        {0.5, 0.5, 0.5},
        BEZIER3,
        {HOLE_RADIUS, 0, PLAYFIELD_WIDTH/2+HOLE_RADIUS/2},
        {0, 0, PLAYFIELD_WIDTH/2+(TABLE_WIDTH-PLAYFIELD_WIDTH)/2},
        {-HOLE_RADIUS, 0, PLAYFIELD_WIDTH/2+HOLE_RADIUS/2},
        {-HOLE_RADIUS, -TABLE_HEIGHT, PLAYFIELD_WIDTH/2+HOLE_RADIUS/2},
    },
    {
        {0.5, 0.5, 0.5},
        BEZIER3,
        {HOLE_RADIUS, 0, -PLAYFIELD_WIDTH/2-HOLE_RADIUS/2},
        {0, 0, -PLAYFIELD_WIDTH/2-(TABLE_WIDTH-PLAYFIELD_WIDTH)/2},
        {-HOLE_RADIUS, 0, -PLAYFIELD_WIDTH/2-HOLE_RADIUS/2},
        {-HOLE_RADIUS, -TABLE_HEIGHT, -PLAYFIELD_WIDTH/2-HOLE_RADIUS/2},
    },
        // Corner table Ling MIDDLE
    {
        {0.5, 0.5, 0.5},
        B,
        {HOLE_RADIUS, TABLE_HEIGHT, PLAYFIELD_WIDTH/2+2*HOLE_RADIUS},
        {0, TABLE_HEIGHT, PLAYFIELD_WIDTH/2+HOLE_RADIUS+(TABLE_WIDTH-PLAYFIELD_WIDTH)/2},
        {-HOLE_RADIUS, TABLE_HEIGHT, PLAYFIELD_WIDTH/2+2*HOLE_RADIUS},
        {-HOLE_RADIUS, TABLE_HEIGHT, PLAYFIELD_WIDTH/2+HOLE_RADIUS/2},
    },
    {
        {0.5, 0.5, 0.5},
        B,
        {HOLE_RADIUS, TABLE_HEIGHT, -PLAYFIELD_WIDTH/2-2*HOLE_RADIUS},
        {0, TABLE_HEIGHT, -PLAYFIELD_WIDTH/2-HOLE_RADIUS-(TABLE_WIDTH-PLAYFIELD_WIDTH)/2},
        {-HOLE_RADIUS, TABLE_HEIGHT, -PLAYFIELD_WIDTH/2-2*HOLE_RADIUS},
        {-HOLE_RADIUS, TABLE_HEIGHT, -PLAYFIELD_WIDTH/2-HOLE_RADIUS/2},
    },
        // Width fill TOP
    // width
    {
        {0.5, 0.25, 0},
        POLYGON,
        {TABLE_LENGTH/2, TABLE_HEIGHT, TABLE_WIDTH/2-HOLE_RADIUS},
        {PLAYFIELD_LENGTH/2, TABLE_HEIGHT, PLAYFIELD_WIDTH/2-HOLE_RADIUS},
        {PLAYFIELD_LENGTH/2, TABLE_HEIGHT, -PLAYFIELD_WIDTH/2+HOLE_RADIUS},
        {TABLE_LENGTH/2, TABLE_HEIGHT, -TABLE_WIDTH/2+HOLE_RADIUS},
    },
    {
        {0.5, 0.25, 0},
        POLYGON,
        {-TABLE_LENGTH/2, TABLE_HEIGHT, -TABLE_WIDTH/2+HOLE_RADIUS},
        {-PLAYFIELD_LENGTH/2, TABLE_HEIGHT, -PLAYFIELD_WIDTH/2+HOLE_RADIUS},
        {-PLAYFIELD_LENGTH/2, TABLE_HEIGHT, PLAYFIELD_WIDTH/2-HOLE_RADIUS},
        {-TABLE_LENGTH/2, TABLE_HEIGHT, TABLE_WIDTH/2-HOLE_RADIUS},
    },
    // length
    {
        {0.5, 0.25, 0},
        POLYGON,
        {TABLE_LENGTH/2-HOLE_RADIUS, TABLE_HEIGHT, TABLE_WIDTH/2},
        {PLAYFIELD_LENGTH/2-HOLE_RADIUS, TABLE_HEIGHT, PLAYFIELD_WIDTH/2},
        {HOLE_RADIUS, TABLE_HEIGHT, PLAYFIELD_WIDTH/2},
        {0, TABLE_HEIGHT, TABLE_WIDTH/2},
    },
    {
        {0.5, 0.25, 0},
        POLYGON,
        {-TABLE_LENGTH/2+HOLE_RADIUS, TABLE_HEIGHT, TABLE_WIDTH/2},
        {-PLAYFIELD_LENGTH/2+HOLE_RADIUS, TABLE_HEIGHT, PLAYFIELD_WIDTH/2},
        {-HOLE_RADIUS, TABLE_HEIGHT, PLAYFIELD_WIDTH/2},
        {0, TABLE_HEIGHT, TABLE_WIDTH/2},
    },
    {
        {0.5, 0.25, 0},
        POLYGON,
        {TABLE_LENGTH/2-HOLE_RADIUS, TABLE_HEIGHT, -TABLE_WIDTH/2},
        {PLAYFIELD_LENGTH/2-HOLE_RADIUS, TABLE_HEIGHT, -PLAYFIELD_WIDTH/2},
        {HOLE_RADIUS, TABLE_HEIGHT, -PLAYFIELD_WIDTH/2},
        {0, TABLE_HEIGHT, -TABLE_WIDTH/2},
    },
    {
        {0.5, 0.25, 0},
        POLYGON,
        {-TABLE_LENGTH/2+HOLE_RADIUS, TABLE_HEIGHT, -TABLE_WIDTH/2},
        {-PLAYFIELD_LENGTH/2+HOLE_RADIUS, TABLE_HEIGHT, -PLAYFIELD_WIDTH/2},
        {-HOLE_RADIUS, TABLE_HEIGHT, -PLAYFIELD_WIDTH/2},
        {0, TABLE_HEIGHT, -TABLE_WIDTH/2},
    }
};

static void check_graph_wall(struct graph_wall *w) {
    if (w->type != RECTANGLE)
        return;
    Vector3 a;
    vector3_sub(w->p1, w->p2, a);
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
        case B:
            vector3_sub(w->p4, w->p3, d);
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

