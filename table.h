#pragma once

#include "vector.h"
#include "object.h"
#include "wall.h"

#define TABLE_LENGTH 2.9
#define TABLE_WIDTH 1.63

#define PLAYFIELD_LENGTH 2.54
#define PLAYFIELD_WIDTH 1.27

#define TABLE_HEIGHT 0.06

#define HOLE_RADIUS 0.06

#define x_wall(l, h, x, z) {\
    {1, 0, 0},\
    {x, 0, -(l)/2.0 + z},\
    {x, 0, (l)/2.0 + z},\
    {x, h, (l)/2.0 + z},\
}

#define z_wall(l, h, z, x) {\
    {1, 0, 0},\
    {-(l)/2.0 + x, 0, z},\
    {(l)/2.0 + x, 0, z},\
    {(l)/2.0 + x, h, z},\
}

#define side_pocket(dx, dz)\
    {\
        {0, 0, 1},\
        {(dx)*HOLE_RADIUS, 0.0         , (dz)*PLAYFIELD_WIDTH/2.0},\
        { 0.00           , 0.0         , (dz)*TABLE_WIDTH/2.0},\
        { 0.00           , TABLE_HEIGHT, (dz)*TABLE_WIDTH/2.0},\
    },\
    {\
        {0, 0, 1},\
        {-(dx)*HOLE_RADIUS, 0.0         , (dz)*PLAYFIELD_WIDTH/2.0},\
        { 0.00            , 0.0         , (dz)*TABLE_WIDTH/2.0},\
        { 0.00            , TABLE_HEIGHT, (dz)*TABLE_WIDTH/2.0},\
    },\
    {\
        {0, 1, 1},\
        { (dx)*2*HOLE_RADIUS, 0.0         , (dz)*PLAYFIELD_WIDTH/2.0},\
        {-(dx)*2*HOLE_RADIUS, 0.0         , (dz)*TABLE_WIDTH/2.0},\
        {-(dx)*2*HOLE_RADIUS, TABLE_HEIGHT, (dz)*TABLE_WIDTH/2.0},\
    },\
    {\
        {0, 1, 1},\
        {-(dx)*2*HOLE_RADIUS, 0.0         , (dz)*PLAYFIELD_WIDTH/2.0},\
        { (dx)*2*HOLE_RADIUS, 0.0         , (dz)*TABLE_WIDTH/2.0},\
        { (dx)*2*HOLE_RADIUS, TABLE_HEIGHT, (dz)*TABLE_WIDTH/2.0},\
    },

#define corner(dx, dz)\
    {\
        {0, 0, 1},\
        {(dx)*(PLAYFIELD_LENGTH/2.0 - HOLE_RADIUS), 0.0         , (dz)*(PLAYFIELD_WIDTH/2.0)},\
        {(dx)*(TABLE_LENGTH/2.0 - HOLE_RADIUS)    , 0.0         , (dz)*(TABLE_WIDTH/2.0)},\
        {(dx)*(TABLE_LENGTH/2.0 - HOLE_RADIUS)    , TABLE_HEIGHT, (dz)*(TABLE_WIDTH/2.0)},\
    },\
    {\
        {0, 0, 1},\
        {(dx)*(PLAYFIELD_LENGTH/2.0), 0.0         , (dz)*(PLAYFIELD_WIDTH/2.0 - HOLE_RADIUS)},\
        {(dx)*(TABLE_LENGTH/2.0)    , 0.0         , (dz)*(TABLE_WIDTH/2.0 - HOLE_RADIUS)},\
        {(dx)*(TABLE_LENGTH/2.0)    , TABLE_HEIGHT, (dz)*(TABLE_WIDTH/2.0 - HOLE_RADIUS)},\
    },\
    {\
        {1, 1, 1},\
        {(dx)*((PLAYFIELD_LENGTH + TABLE_LENGTH)/4.0), 0.0         , (dz)*(PLAYFIELD_WIDTH/2.0)},\
        {(dx)*(PLAYFIELD_LENGTH/2.0)                 , 0.0         , (dz)*((PLAYFIELD_WIDTH+TABLE_WIDTH)/4.0)},\
        {(dx)*(PLAYFIELD_LENGTH/2.0)                 , TABLE_HEIGHT, (dz)*((PLAYFIELD_WIDTH+TABLE_WIDTH)/4.0)},\
    },\
    {\
        {0, 1, 1},\
        {(dx)*(PLAYFIELD_LENGTH/2.0 + HOLE_RADIUS), 0.0         , (dz)*(PLAYFIELD_WIDTH/2.0 - HOLE_RADIUS)},\
        {(dx)*(PLAYFIELD_LENGTH/2.0 + HOLE_RADIUS), 0.0         , (dz)*((PLAYFIELD_WIDTH+TABLE_WIDTH)/4.0)},\
        {(dx)*(PLAYFIELD_LENGTH/2.0 + HOLE_RADIUS), TABLE_HEIGHT, (dz)*((PLAYFIELD_WIDTH+TABLE_WIDTH)/4.0)},\
    },\
    {\
        {0, 1, 1},\
        {(dx)*(PLAYFIELD_LENGTH/2.0 - HOLE_RADIUS) , 0.0         , (dz)*(PLAYFIELD_WIDTH/2.0 + HOLE_RADIUS)},\
        {(dx)*((PLAYFIELD_LENGTH+TABLE_LENGTH)/4.0), 0.0         , (dz)*(PLAYFIELD_WIDTH/2.0 + HOLE_RADIUS)},\
        {(dx)*((PLAYFIELD_LENGTH+TABLE_LENGTH)/4.0), TABLE_HEIGHT, (dz)*(PLAYFIELD_WIDTH/2.0 + HOLE_RADIUS)},\
    },

struct table {
    struct object_trans trans;
    struct wall *walls;
    size_t walls_num;
    int filled;
};

void draw_table(const struct table *table);

void table_load_clipping_planes(void);
void table_enable_clipping_planes(void);
void table_disable_clipping_planes(void);

