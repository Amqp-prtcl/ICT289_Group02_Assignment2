#include "camera.h"
#include "input.h"
#include "draw.h"
#include "game.h"
#include "state.h"

#include "light.h"
#include "texture.h"

#include "dbg.h"

#define WIND_W 1300
#define WIND_H 700

static const char* TexPaths[] = { "data/texture/BallCue.jpg",
     "data/texture/Ball1.jpg",
     "data/texture/Ball2.jpg",
     "data/texture/Ball3.jpg",
     "data/texture/Ball8.jpg",
     "data/texture/Ball4.jpg",
     "data/texture/Ball5.jpg",
     "data/texture/Ball6.jpg",
     "data/texture/Ball7.jpg",
     "data/texture/Ball9.jpg",
     "data/texture/Ball10.jpg",
     "data/texture/Ball11.jpg",
     "data/texture/Ball12.jpg",
     "data/texture/Ball13.jpg",
     "data/texture/Ball14.jpg",
     "data/texture/Ball15.jpg"
};

static void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);

    light_init();

    GLuint *textures = LoadAllTex(TexPaths,
            sizeof(TexPaths)/sizeof(char *));

    game_init(textures);
}

static void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
}

static void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
        case 'q':
        case 'Q':
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

