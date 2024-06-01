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

