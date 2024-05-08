#pragma once

#ifdef DEBUG

#include "stdio.h"

#define D1(a) #a
#define D2(a) D1(a)
#define _line_prefix __FILE__":" D2(__LINE__) " "

#define DBG(a, fmt) printf(_line_prefix #a" = "fmt"\n", __LINE__, a);
#define DBG_PRINT(...) printf(_line_prefix); printf(__VA_ARGS__);

#else

#define DBG(a, fmt)
#define DBG_PRINT(...)

#endif

#define DBGI(a) DBG(a, "%i")
#define DBGU(a) DBG(a, "%u")
#define DBGZU(a) DBG(a, "%zu")
#define DBGZI(a) DBG(a, "%zi")
#define DBGF(a) DBG(a, "%f")
#define DBGD(a) DBG(a, "%d")
#define DBGSTR(a) DBG(a, "%s")

#define DBG_VEC(v) DBG_PRINT(#v" = {x: %f, y: %f, z: %f}\n", v[0], v[1], v[2])

#define DBG_BALL(b) DBG_PRINT(#b" = {"\
    "color: {%03.0f, %03.0f, %03.0f}, "\
    "pos: {%03.3f, %03.3f, %03.3f}, "\
    "speed: {%03.3f, %03.3f, %03.3f}}\n",\
            b->color[0], b->color[1], b->color[2],\
            b->trans.position[0],\
            b->trans.position[1],\
            b->trans.position[2],\
            b->phys.speed[0], b->phys.speed[1], b->phys.speed[2])

