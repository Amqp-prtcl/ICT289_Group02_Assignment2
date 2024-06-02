#pragma once

#include "GL/freeglut.h"
#include "vector.h"

typedef GLfloat Matrix3x3[3*3];

// in and out must not overlap
// Computes the transposed inverse off in
int matrix_invert(const Matrix3x3 in, Matrix3x3 out);

// in and out must not overlap
void matrix_vector_mul(const Matrix3x3 m, const Vector3 in, Vector3 out);

void matrix_rotate_vector(const Vector3 rotation, const Vector3 in,
        Vector3 out);

void matrix_rotate_vector_around_point(const Vector3 rot, const Vector3 ancor,
        const Vector3 in, Vector3 out);

void matrix_vector_get_angles(const Vector3 in, Vector3 out);

