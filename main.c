#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "camera.h"
#include "input.h"
#include "draw.h"
#include "game.h"
#include "state.h"

#include "texture.h"

#include "dbg.h"

#define WIND_W 1300
#define WIND_H 700

static void init(void) {
    init_camera();
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_TEXTURE_2D);

    /*
    glEnable(GL_LIGHTING);

    GLfloat ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat diffuse[] = {0.8, 0.8, 0.8, 1.0};
    GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat position[] = {1.0, 1.0, 1.0, 0.0};

    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    GLfloat pos[] = {1, 1, 1, 0};
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    */

    texture_id = LoadTex("data/texture/Ball4.jpg");
    DBGU(texture_id);

    game_init();
}

void reshape (int w, int h) {
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(80.0, (GLfloat) w/(GLfloat) h, 0.01, 3000.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   //gluLookAt (4.0, 4.0, 4.0, 0.0, .5, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
        case 'q':
        case 'Q':
            //glutLeaveMainLoop();
            game_set_state(QUIT);
            break;
        default:
            game_keyboard_event(key);
            break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIND_W, WIND_H);
    glutInitWindowPosition(10, 10);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(draw_scene);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(camera_handle_mouse);

    input_setup(keyboard);

    start_game();
    glutMainLoop();
    return 0;
}

