#include "vector_math.h"
#include "math.h"
#include "GL/freeglut.h"

const Vector3 vector3_zero = {0, 0, 0};
const Vector3 vector3_ones = {1, 1, 1};

const Vector3 vector3_forward = {1, 0, 0};
const Vector3 vector3_up = {0, 1, 0};
const Vector3 vector3_left = {0, 0, 1};

// HELPERS

void vector3_to_zero(Vector3 v) {
    v[0] = 0;
    v[1] = 0;
    v[2] = 0;
}

void vector3_to_one(Vector3 v) {
    v[0] = 1;
    v[1] = 1;
    v[2] = 1;
}

void vector3_move(const Vector3 in, Vector3 out) {
    out[0] = in[0];
    out[1] = in[1];
    out[2] = in[2];
}

// SINGLE VECTOR

GLfloat vector3_norm(const Vector3 v) {
    return sqrtf(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
}

void vector3_scale(const Vector3 v, const GLfloat k, Vector3 out) {
    out[0] = v[0] * k;
    out[1] = v[1] * k;
    out[2] = v[2] * k;
}

void vector3_normalize(const Vector3 in, Vector3 out) {
    GLfloat n = vector3_norm(in);;
    n = 1/n;
    out[0] = in[0] * n;
    out[1] = in[1] * n;
    out[2] = in[2] * n;
}

// OTHER OPERATIONS

void vector3_sub(const Vector3 a, const Vector3 b, Vector3 out) {
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];
}

void vector3_affine(const Vector3 a, const GLfloat k,
        const Vector3 b, Vector3 c) {
    c[0] = a[0]*k + b[0];
    c[1] = a[1]*k + b[1];
    c[2] = a[2]*k + b[2];
}

// vectors cannot overlap
void vector3_cross(const Vector3 a, const Vector3 b, Vector3 c) {
    c[0] = a[1]*b[2]-a[2]*b[1];
    c[1] = a[2]*b[0]-a[0]*b[2];
    c[2] = a[0]*b[1]-a[1]*b[0];
}

