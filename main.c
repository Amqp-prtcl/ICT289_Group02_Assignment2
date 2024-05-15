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
#include "ui.h"

#include "dbg.h"

#define DELAY 10
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
            {0, 0, 0},
            {0, 0, 0},
            {1, 1, 1}
        },
        {
            1,
            .5,
            {0, 0, 0}
        }
    },
    {
        {0, 255, 0},
        {
            {-2, 0, -.5},
            {0, 0, 0},
            {1, 1, 1}
        },
        {
            1,
            .5,
            {0, 0, 0}
        }
    },
    {
        {0, 0, 255},
        {
            {8, 0, 0},
            {0, 0, 0},
            {1, 1, 1}
        },
        {
            1.5,
            .5,
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
    {
        {255, 255, 255},
        {-.8, 0, 0},
        {-.8, 3, 0},
        {2.5, 3, -2.5},
    },
    {
        {0, 50, 50},
        {100, -0.5, 100},
        {-100, -0.5, 100},
        {-100, -0.5, -100},
        0, .3,
    },
};

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);

    board.width = 100;
    board.length = 200;

    board.balls = balls;
    board.balls_num = 3;

    board.walls = walls+1;
    board.walls_num = 1;

    for (size_t i = 0; i < board.walls_num; i++)
        wall_init(board.walls + i);

    board.timescale = 1.0;
}

void draw_wall(const struct wall *w) {
    glColor3fv(w->color);
    glBegin(GL_POLYGON);
    glVertex3fv(w->p1);
    glVertex3fv(w->p2);
    glVertex3fv(w->p3);
    glVertex3fv(w->p4);
    glEnd();
}

void draw_ball(const struct ball *ball) {
    //DBG_BALL(ball);
    glColor3fv(ball->color);
    glPushMatrix();
    object_trans_apply(&ball->trans);
    glutWireSphere(ball_get_radius(ball), 30, 30);
    glPopMatrix();
}


void draw_text(char text[], GLfloat x, GLfloat y, GLfloat viewport[4]) {
    glRasterPos2f(UI_DEFAULT_X_POSITION + x,
                  viewport[3] - UI_DEFAULT_Y_POSITION - y);

    for (int i = 0; i < strlen(text); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
    }
}

void draw_ui() {
    // Get viewport
    GLfloat viewport[4];
    glGetFloatv(GL_VIEWPORT, viewport);

    // Begin UI
    ui_begin(viewport);

    // Set text colour
    glColor3f(1, 0, 0);

    // Display UI options //
    if (display_help == 0) {
        draw_text("H - Show keyboard options",
                  0, 0, viewport);

        // End UI early since keyboard options are hidden
        ui_end();
        return;
    }

    // Options that are always displayed in the keyboard options
    draw_text("Q - Quit",
              0, 0, viewport);
    draw_text("H - Hide keyboard options",
              0, 20, viewport);
    draw_text("< and > - Increment and decrement play field roughness",
              0, 60, viewport);
    draw_text("[ and ] - Increase and decrease mass of all balls",
              0, 80, viewport);

    // Options displayed if the game has not started
    if (game_started == 0) {
        draw_text("F - Toggle between triangle and rectangle ball format",
                  0, 120, viewport);
        draw_text("Enter - Start the game",
                  0, 140, viewport);

        // Options displayed if the game is in progress
    } else {
        draw_text("R - Restart the game",
                  0, 120, viewport);
    }

    // End UI
    ui_end();
}

void set_viewport(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, (GLfloat) w/(GLfloat) h, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5.0, 12.0, 5.0, 0.0, 2.5, 0.0, 0.0, 1.0, 0.0);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //drawGrid(100/100, 100);
    //drawAxis();

    for (size_t i = 0; i < board.balls_num; i++)
        draw_ball(board.balls + i);
    for (size_t i = 0; i < board.walls_num; i++)
        draw_wall(board.walls + i);

    draw_ui();

    set_viewport(WIND_W, WIND_H);

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, (GLfloat) w/(GLfloat) h, 1.0, 200.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5.0, 12.0, 5.0, 0.0, 2.5, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        // Esc & Q - quit the program
        case 27:
        case 'q':
        case 'Q':
            glutLeaveMainLoop();
            break;

        // H = toggle help menu
        case 'h':
        case 'H':
            display_help = (display_help == 1) ? 0 : 1;
            break;

        // Enter - start the game
        case 13:
            game_started = 1;
            break;

        // R - restart the game
        case 'r':
        case 'R':
            game_started = 0;
            break;

        // Default - nothing
        default: {
            break;
        }
    }
}

void test(int last_time) {
    int curr_time = glutGet(GLUT_ELAPSED_TIME);
    GLfloat delta = (GLfloat)(curr_time - last_time)/1000.0;
    glutTimerFunc(DELAY, test, curr_time);

    board_compute_next_positions(&board, delta * board.timescale);
    board_handle_collisions(&board, delta * board.timescale);

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
    glutKeyboardFunc(keyboard);

    glutTimerFunc(DELAY, test, glutGet(GLUT_ELAPSED_TIME));
    glutMainLoop();
    return 0;
}

