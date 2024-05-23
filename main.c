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
#include "cue.h"
#include "ui.h"
#include "camera.h"
#include "input.h"
#include "table.h"

#include "dbg.h"

#define DELAY 2
#define WIND_W 1300
#define WIND_H 700

#define UI_DEFAULT_X_POSITION 10.0f
#define UI_DEFAULT_Y_POSITION 20.0f

int game_started = 0;
int display_help = 1;

struct board board;

struct ball balls[10] = {
    {
        {255, 0, 0},
        {
            {0, 1, 0},
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
            {-2, .5, -.5},
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
            {8, .5, 0},
            {0, 0, 0},
            {1, 1, 1}
        },
        {
            0.162,
            .028575,
            {-8, 0, 0}
        }
    },
};

struct ball balls_2[] = {
    {
        {255, 0, 0},
        {
            {6, 0, 5},
            {0, 0, 0},
            {1, 1, 1}
        },
        {
            1,
            .5,
            {-7, 0, -7}
        }
    },
};


struct wall walls[] = {
/*    {
        {255, 255, 255},
        {0, 0, 0},
        {-1.5, 3, 0},
        {2.5, 3, -3.5},
    },
    {
        {0, 50, 50},
        {100, 0, 100},
        {-100, 0, 100},
        {-100, 0, -100},
        0, .3,
    },*/
};

struct cue cue = {
    {
        {0, 255, 0},
        {
            {0, 0, 0},
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

    board.width = 100;
    board.length = 200;

    board.balls = balls;
    board.balls_num = 1;

    board.walls = walls;
    board.walls_num = 0;

    init_default_table(&board.table);

    board.cue = cue;

    for (size_t i = 0; i < board.walls_num; i++)
        wall_init(board.walls + i);

    board.timescale = 1.0;
}

void draw_text(char text[], GLfloat x, GLfloat y, GLfloat viewport[4]) {
    glRasterPos2f(UI_DEFAULT_X_POSITION + x,
                  viewport[3] - UI_DEFAULT_Y_POSITION - y);

    while (*text != 0)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, *(text++));
}

void draw_ui() {
    GLfloat viewport[4];
    glGetFloatv(GL_VIEWPORT, viewport);

    ui_begin(viewport);
    glColor3f(1, 0, 0);
    if (display_help == 0) {
        draw_text("H - Show keyboard options", 0, 0, viewport);
        ui_end();
        return;
    }
    draw_text("Q - Quit", 0, 0, viewport);
    draw_text("H - Hide keyboard options", 0, 20, viewport);
    draw_text("< and > - Increment and decrement play field roughness",
              0, 60, viewport);
    draw_text("[ and ] - Increase and decrease mass of all balls",
              0, 80, viewport);

    if (game_started == 0) {
        draw_text("F - Toggle between triangle and rectangle ball format",
                  0, 120, viewport);
        draw_text("Enter - Start the game", 0, 140, viewport);
    } else {
        draw_text("R - Restart the game", 0, 120, viewport);
    }
    ui_end();
}

void display(void) {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    camera_apply();
    drawAxis();
    drawGrid(100/100, 100);

    for (size_t i = 0; i < board.balls_num; i++)
        draw_ball(board.balls + i);
    for (size_t i = 0; i < board.walls_num; i++)
        draw_wall(board.walls + i);

    draw_table(&board.table);
    glPopMatrix();

    draw_ui();

    //draw_cue(&board.cue);

    glutSwapBuffers();
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
        case 'h':
        case 'H':
            display_help = (display_help == 1) ? 0 : 1;
            break;
        case 13:
            game_started = 1;
            //cue_start_anim(&board.cue);
            break;
        case 'r':
        case 'R':
            game_started = 0;
            break;
        default:
            break;
    }
}

void test(int last_time) {
    int curr_time = glutGet(GLUT_ELAPSED_TIME);
    GLfloat delta = (GLfloat)(curr_time - last_time)/1000.0;
    glutTimerFunc(DELAY, test, curr_time);

	GLfloat curr, max_speed, sub_delta;
	curr = 0;

	max_speed = board_apply_forces(&board, delta);
	sub_delta = (0.028)/max_speed * board.timescale;
	if (sub_delta > delta)
		sub_delta = delta;
	while (curr < delta) {
		board_compute_next_positions(&board, sub_delta);
    	board_handle_collisions(&board, sub_delta);
		curr += sub_delta;

	}

    //max_speed = board_compute_next_positions(&board, delta * board.timescale);
    //board_handle_collisions(&board, delta * board.timescale);

    camera_handle_keyboard(delta);

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIND_W, WIND_H);
    glutInitWindowPosition(10, 10);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(camera_handle_mouse);

    glutKeyboardUpFunc(input_up_callback);
    glutKeyboardFunc(input_down_callback);
    input_press_callback = keyboard;

    glutTimerFunc(DELAY, test, glutGet(GLUT_ELAPSED_TIME));
    glutMainLoop();
    return 0;
}

