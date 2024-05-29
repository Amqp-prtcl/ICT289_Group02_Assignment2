#include "light.h"

#include "vector.h"

void light_init() {
    glEnable(GL_LIGHTING);

    GLfloat ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat diffuse[] = {0.8, 0.8, 0.8, 1.0};
    GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};

    GLfloat position[] = {1.0, 1.0, 1.0, 0.0};

    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
//    glLightfv(GL_LIGHT0, GL_POSITION, position);

    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();

    //GLfloat pos[] = {1, 1, 1, 0};
    //glLightfv(GL_LIGHT0, GL_POSITION, pos);
}

void apply_light() {
    GLfloat pos[] = {0, 1, 0, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
}
