#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include "camera.h"
#include "input.h"
#include "draw.h"
#include "table.h"
#include "game.h"

#include "dbg.h"

#define WIND_W 1300
#define WIND_H 700

struct ball balls[] = {
    {
        {1, 1, 1},
        {
            {.5, .03, .5},
            {0, 0, 0},
            {1, 1, 1}
        },
        {
            0.162,
            0.028575,
            {0, 0, 0}
        }
    },
    {
        {255, 0, 0},
        {
            {0, .03, 0.02},
            {0, 0, 0},
            {1, 1, 1}
        },
        {
            0.162,
            0.028575,
            {0, 0, 0}
        }
    },
    {
        {0, 255, 0},
        {
            {1, .03, -.5},
            {0, 0, 0},
            {1, 1, 1}
        },
        {
            0.162,
            .028575,
            {0, 0, 0}
        }
    },
    {
        {0, 0, 255},
        {
            {-1, .03, 0},
            {0, 0, 0},
            {1, 1, 1}
        },
        {
            0.162,
            .028575,
            {0, 0, 0}
        }
    },
};

struct cue cue = {
    {
        {0, 255, 0},
        {
            {0, 1, 0},
            {0, 0, 0},
            {1, 1, 1},
        },
        {
            .6,
            .01,
            {0, 0, 0}
        },
    },
    {0, 0, 0},
};


static void init(void) {
    init_camera();
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);

    board.balls = balls;
    //board.balls_num = 4;
    board.balls_num = sizeof(balls)/sizeof(struct ball);

    board.walls = NULL;
    board.walls_num = 0;

    init_default_table(&board.table);

    board.cue = cue;

    for (size_t i = 0; i < board.walls_num; i++)
        wall_init(board.walls + i);

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
            glutLeaveMainLoop();
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

