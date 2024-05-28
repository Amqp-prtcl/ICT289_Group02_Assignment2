#pragma once

#define is_key_up(a) !input_states[a]
#define is_key_down(a) input_states[a]

extern int input_states[256];
//extern void (*input_press_callback) (unsigned char key, int x, int y);

void input_setup(void(*event_handler)(unsigned char key, int x, int y));
//void input_up_callback(unsigned char key, int x, int y);
//void input_down_callback(unsigned char key, int x, int y);

