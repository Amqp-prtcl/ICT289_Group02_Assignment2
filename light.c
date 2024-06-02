#include "light.h"

#include "vector.h"

void light_init() {
    //glEnable(GL_LIGHTING);

    GLfloat ambient[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};

    GLfloat pos[] = {0.0, 1.0, 0.0, 1.0};
    glLightfv(GL_LIGHT0, GL_POSITION, pos);

    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
}

void apply_light() {
    GLfloat pos[] = {0, 1, 0, 0};
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
}
