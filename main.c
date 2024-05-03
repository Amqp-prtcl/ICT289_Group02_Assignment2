#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "GL/freeglut.h"

#include "scene_utils.h"
#include "object.h"
#include "off.h"

#include "shape.h"

#include "phys.h"

#define DELAY 20
#define WIND_W 1300
#define WIND_H 700

typedef GLfloat Vector3[3];

struct object {
    struct object_trans trans;
    struct phys phys;
    struct off off;
};

struct ball {
    Vector3 color;
    struct object_trans trans;
    struct phys phys;
}

struct object *objs = NULL;
size_t objs_num = 0;

void init(void) {
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glEnable(GL_DEPTH_TEST);
}

void draw_ball(const struct ball *ball) {
    glColor3fv(ball->color);
    glPushMatrix();
    apply_trans_apply(ball->trans);
    glutWireSphere(ball->phys.size);
    lgPopMatrix();
}

void display(void) {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawGrid(100/100, 100);
    drawAxis();
    for (size_t i = 0; i < objs_num; i++) {
        draw_shape(&objs[i].trans, &objs[i].off);
    }
    glutSwapBuffers();
}

void reshape (int w, int h) {
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(90.0, (GLfloat) w/(GLfloat) h, 1.0, 200.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt (5.0, 12.0, 5.0, 0.0, 2.5, 0.0, 0.0, 1.0, 0.0);
}

void keyboard (unsigned char key, int x, int y) {
    switch (key) {
        case 27:
        case 'q':
        case 'Q':
            exit(0);
    }
}

void apply_forces(struct object *obj, GLfloat delta) {
    apply_gravity(&obj->phys, delta);
}

void test(int last_time) {
    int curr_time = glutGet(GLUT_ELAPSED_TIME);
    GLfloat delta = (GLfloat)(curr_time - last_time)/1000.0;
    glutTimerFunc(DELAY, test, curr_time);

    struct object *obj;
    for (size_t i = 0; i < objs_num; i++) {
        obj = objs + i;
        apply_forces(obj, delta);
        apply_speed(&obj->phys, &obj->trans, delta);
        apply_collision(&obj->phys, &obj->trans, delta);
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Error: you need to specify at least one file\n");
        return 1;
    }
    if ((argc-1)%2 !=0 ) {
        printf("Error: The number of arguments must be even (a filename and "
                "an initial speed\n");
        return 1;
    }

    objs = malloc(((argc-1)/2) * sizeof(struct object));
    objs_num = (argc-1)/2;
    for (size_t i = 0; i < objs_num; i++) {
        if (readOFFFile(&objs[i].off, argv[2*i+1]) != 0) {
            printf("Error: unable to parse \"%s\" as an off file\n", argv[i+1]);
            return 1;
        }
        GLfloat speed = strtof(argv[2*i+2], NULL);

        normalizeOFF(&objs[i].off);
        object_trans_reset(&objs[i].trans);
        objs[i].trans.position[1] = 10;
        phys_reset(&objs[i].phys);
        objs[i].phys.mass = 1;
        objs[i].phys.speed[0] = -speed;
        objs[i].phys.speed[2] = speed;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (WIND_W, WIND_H);
    glutInitWindowPosition (10, 10);
    glutCreateWindow (argv[0]);
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutTimerFunc(DELAY, test, glutGet(GLUT_ELAPSED_TIME));
    glutMainLoop();
    return 0;
}

