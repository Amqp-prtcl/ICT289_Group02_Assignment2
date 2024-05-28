#include "stddef.h"
#include "input.h"
#include "GL/freeglut.h"
#include "dbg.h"

int input_states[256] = { 0 };
static void (*input_press_callback) (unsigned char key, int x, int y);

static void input_up_callback(unsigned char key, int x, int y) {
    (void)x;
    (void)y;
    //DBG_PRINT("[INPUT] key release: %c (%hhi)\n", key, key);
    input_states[key] = 0;
}

static void input_down_callback(unsigned char key, int x, int y) {
    //DBG_PRINT("[INPUT] key press: %c (%hhi)\n", key, key);
    input_states[key] = 1;
    if (input_press_callback != NULL)
        input_press_callback(key, x, y);
}

void input_setup(void(*event_handler)(unsigned char key, int x, int y)) {
    glutKeyboardUpFunc(input_up_callback);
    glutKeyboardFunc(input_down_callback);
    input_press_callback = event_handler;
}

