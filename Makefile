CC:=gcc
CFLAGS:=-I/opt/local/include -MMD -g -DDEBUG
LDFLAGS:=-L/opt/local/lib
LDLIBS:=-lglut -lGLU -lGL -lm

SRC:= main.c object.c scene_utils.c off.c shape.c vector.c board.c
OBJ:=${SRC:.c=.o}
DEPS:=${SRC:.c=.d}

all: main

main: ${OBJ}

clean:
	${RM} ${OBJ} ${DEPS} main

-include ${DEPS}
