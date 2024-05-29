CC:=gcc
CFLAGS:=-I/opt/local/include -MMD -g -DDEBUG -Wall #-Wextra
LDFLAGS:=-L/opt/local/lib -fsanitize=address
LDLIBS:=-lglut -lGLU -lGL -lm

SRC:= main.c object.c scene_utils.c off.c shape.c vector.c board.c matrix.c\
	wall.c ui.c cue.c ball.c wall.c camera.c input.c table.c state.c game.c\
	draw.c ball_setup.c draw_cue.c
OBJ:=${SRC:.c=.o}
DEPS:=${SRC:.c=.d}

all: main

main: ${OBJ}

clean:
	${RM} ${OBJ} ${DEPS} main

-include ${DEPS}
