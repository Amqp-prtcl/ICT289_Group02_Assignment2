#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "GL/freeglut.h"

#include "scene_utils.h"
#include "object.h"
#include "off.h"
#include "shape.h"
#include "phys.h"
#include "board.h"

#define DELAY 20
#define WIND_W 1300
#define WIND_H 700

struct board board;

struct ball balls[10] = {
    {
        {255, 0, 0},
        {
            {-3, 0, 0},
            {0, 0, 0},
            {1, 1, 1}
        },
        {
            1,
            1,
            {.5, 0, 0}
        }
    },
    {
        {0, 255, 0},
        {
            {6, 0, 0},
            {0, 0, 0},
            {1, 1, 1}
        },
        {
            1,
            1,
            {-1.5, 0, 0}
        }
    },
    {
        {255, 0, 0},
        {
            {0, 0, 0},
            {0, 0, 0},
            {1, 1, 1}
        },
        {
            1,
            1,
            {1, 0, 1}
        }
    },
};

void init(void) {
   glClearColor (0.0, 0.0, 0.0, 0.0);
   glEnable(GL_DEPTH_TEST);

   board.width = 100;
   board.length = 200;

   board.balls = balls;
   board.balls_num = 2;
}

void draw_ball(const struct ball *ball) {
    printf("color: {%f, %f, %f}, pos = {%f, %f, %f}, speed = {%f, %f, %f}\n",
            ball->color[0], ball->color[1], ball->color[2],
            ball->trans.position[0],
            ball->trans.position[1],
            ball->trans.position[2],
            ball->phys.speed[0], ball->phys.speed[1], ball->phys.speed[2]);
    glColor3fv(ball->color);
    glPushMatrix();
    object_trans_apply(&ball->trans);
    glutWireSphere(get_ball_radius(ball), 30, 30);
    glPopMatrix();
}

void display(void) {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    drawGrid(100/100, 100);
    drawAxis();

    for (size_t i = 0; i < board.balls_num; i++)
        draw_ball(board.balls + i);

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

void test(int last_time) {
    int curr_time = glutGet(GLUT_ELAPSED_TIME);
    GLfloat delta = (GLfloat)(curr_time - last_time)/1000.0;
    glutTimerFunc(DELAY, test, curr_time);

    compute_next_pos(&board, delta);
    apply_collisions(&board, delta);

    glutPostRedisplay();
}

int main(int argc, char** argv) {
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

