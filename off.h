#pragma once

#include "GL/freeglut.h"
#include "stddef.h"

#include "vector.h"

struct off_triangle {
    size_t p1;
    size_t p2;
    size_t p3;
};

struct off {
    size_t nvert;
    size_t nfaces;

    Vector3 *vertices;
    struct off_triangle *triangles;
};

int readOFFFile(struct off *off, const char *filename);
int writeOFFFile(const struct off *off, const char *filename);

void freeOFF(struct off *off);

void normalizeOFF(struct off *off);
