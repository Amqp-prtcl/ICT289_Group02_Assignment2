#include "input.h"
#include "dbg.h"

int input_states[256] = { 0 };
void (*input_press_callback) (unsigned char key, int x, int y);

void input_up_callback(unsigned char key, int x, int y) {
    //DBG_PRINT("[INPUT] key release: %c (%hhi)\n", key, key);
    input_states[key] = 0;
}

void input_down_callback(unsigned char key, int x, int y) {
    //DBG_PRINT("[INPUT] key press: %c (%hhi)\n", key, key);
    input_states[key] = 1;
    input_press_callback(key, x, y);
}
