#pragma once
#include "GL/freeglut.h"

extern GLuint texture_id;

#define SIGN(a) (((a)<0)?(-1):1)
#define ABS(a) (((a)<0)?(-a):(a))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define CLAMP(x,a,b) ((x)<(a)?(a):((x)>(b)?(b):(x)))
#define MAP(x,a,b,c,d) (((x)-(a))*((d)-(c))/((b)-(a))+(c))

typedef GLfloat Vector3[3];
#define Point3 Vector3

typedef GLfloat Vector4[4];

extern const Vector3 vector3_zeros;
extern const Vector3 vector3_one;

extern const Vector3 vector3_forward;
extern const Vector3 vector3_backward;
extern const Vector3 vector3_up;
extern const Vector3 vector3_down;
extern const Vector3 vector3_right;
extern const Vector3 vector3_left;

//// HELPERS ////

void vector3_to_zero(Vector3 v);
void vector3_to_one(Vector3 v);

void vector3_copy(const Vector3 in, Vector3 out);

//// SINGLE VECTOR OPERATIONS ////

GLfloat vector3_norm(const Vector3 v);

void vector3_scale(const Vector3 v, const GLfloat k, Vector3 out);

void vector3_normalize(const Vector3 in, Vector3 out);

//// OHTER OPERATIONS ////

void vector3_add(const Vector3 a, const Vector3 b, Vector3 out);

void vector3_sub(const Vector3 a, const Vector3 b, Vector3 out);

void vector3_lerp(const Vector3 a, const Vector3 b,
        const GLfloat t, Vector3 out);

void vector3_affine(const Vector3 a, const GLfloat k, const Vector3 b,
        Vector3 c);

GLfloat vector3_dot(const Vector3 a, const Vector3 b);

// vectors cannot overlap
void vector3_cross(const Vector3 a, const Vector3 b, Vector3 c);

