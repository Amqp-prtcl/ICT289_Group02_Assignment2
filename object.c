#include "object.h"

void object_trans_reset(struct object_trans *obj) {
    vector3_to_zero(obj->position);
    vector3_to_zero(obj->rotation);
    vector3_to_one(obj->scale);
}

void object_trans_apply(const struct object_trans *obj) {
    glTranslatef(obj->position[0], obj->position[1], obj->position[2]);

    glRotatef(obj->rotation[0], 1, 0, 0);
    glRotatef(obj->rotation[1], 0, 1, 0);
    glRotatef(obj->rotation[2], 0, 0, 1);

    glScalef(obj->scale[0], obj->scale[1], obj->scale[2]);
}

#define SCALE_DELTA 0.1
#define MOV_DELTA 0.1
#define ROT_DELTA 30

// returns a TRUE if something has changed
int object_trans_process_key(struct object_trans *obj,
        const unsigned char key) {
    int ret = TRUE;
    switch (key) {
        case '+':
            obj->scale[0] += SCALE_DELTA;
            obj->scale[1] += SCALE_DELTA;
            obj->scale[2] += SCALE_DELTA;
            break;
        case '-':
            obj->scale[0] -= SCALE_DELTA;
            obj->scale[1] -= SCALE_DELTA;
            obj->scale[2] -= SCALE_DELTA;
            break;

        case 'a':
            obj->position[0] += MOV_DELTA;
            break;
        case 'd':
            obj->position[0] -= MOV_DELTA;
            break;
        case 'w':
            obj->position[1] += MOV_DELTA;
            break;
        case 's':
            obj->position[1] -= MOV_DELTA;
            break;
        case 'u':
            obj->position[2] += MOV_DELTA;
            break;
        case 'U':
            obj->position[2] -= MOV_DELTA;
            break;

        default:
            ret = FALSE;
            break;
    }
    return ret;
}

int object_trans_process_special_key(struct object_trans *obj,
        const unsigned char key) {
    int ret = TRUE;
    switch (key) {
        case GLUT_KEY_LEFT:
            obj->rotation[0] += ROT_DELTA;
            break;
        case GLUT_KEY_RIGHT:
            obj->rotation[0] -= ROT_DELTA;
            break;
        case GLUT_KEY_UP:
            obj->rotation[1] += ROT_DELTA;
            break;
        case GLUT_KEY_DOWN:
            obj->rotation[1] -= ROT_DELTA;
            break;
        default:
            ret = FALSE;
            break;
    }
    return ret;
}
