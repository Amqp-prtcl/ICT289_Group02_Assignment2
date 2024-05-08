#pragma once
#include "GL/freeglut.h"

typedef GLfloat Vector3[3];
#define Point3 Vector3

extern const Vector3 vector3_zeros;
extern const Vector3 vector3_one;

// NOTE: bad names (confusing)
extern const Vector3 vector3_forward;
extern const Vector3 vector3_up;
extern const Vector3 vector3_left;

//// HELPERS ////

void vector3_to_zero(Vector3 v);
void vector3_to_one(Vector3 v);

void vector3_copy(Vector3 out, const Vector3 in);

//// SINGLE VECTOR OPERATIONS ////

GLfloat vector3_norm(const Vector3 v);

void vector3_scale(const Vector3 v, const GLfloat k, Vector3 out);

void vector3_normalize(const Vector3 in, Vector3 out);

//// OHTER OPERATIONS ////

void vector3_add(const Vector3 a, const Vector3 b, Vector3 out);

void vector3_sub(const Vector3 a, const Vector3 b, Vector3 out);

void vector3_affine(const Vector3 a, const GLfloat k, const Vector3 b,
        Vector3 c);

GLfloat vector3_dot(const Vector3 a, const Vector3 b);

// vectors cannot overlap
void vector3_cross(const Vector3 a, const Vector3 b, Vector3 c);

