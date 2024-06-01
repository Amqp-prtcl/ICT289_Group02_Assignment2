#include "vector.h"
#include "math.h"
#include "GL/freeglut.h"
#include "dbg.h"

const Vector3 vector3_zero = {0, 0, 0};
const Vector3 vector3_one = {1, 1, 1};

const Vector3 vector3_forward = {0, 0, -1};
const Vector3 vector3_backward = {0, 0, 1};
const Vector3 vector3_up = {0, 1, 0};
const Vector3 vector3_down = {0, -1, 0};
const Vector3 vector3_right = {1, 0, 0};
const Vector3 vector3_left = {-1, 0, 0};

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

void vector3_copy(const Vector3 in, Vector3 out) {
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
    if (n != 0) {
        n = 1/n;
        vector3_copy(in, out);
    }
    vector3_scale(in, n, out);
}

// OTHER OPERATIONS

void vector3_add(const Vector3 a, const Vector3 b, Vector3 out) {
    out[0] = a[0] + b[0];
    out[1] = a[1] + b[1];
    out[2] = a[2] + b[2];
}

void vector3_sub(const Vector3 a, const Vector3 b, Vector3 out) {
    out[0] = a[0] - b[0];
    out[1] = a[1] - b[1];
    out[2] = a[2] - b[2];
}

void vector3_lerp(const Vector3 a, const Vector3 b,
        const GLfloat t, Vector3 out) {
    out[0] = (1.0-t)*a[0] + t*b[0];
    out[1] = (1.0-t)*a[1] + t*b[1];
    out[2] = (1.0-t)*a[2] + t*b[2];
}

void vector3_affine(const Vector3 a, const GLfloat k,
        const Vector3 b, Vector3 c) {
    c[0] = a[0]*k + b[0];
    c[1] = a[1]*k + b[1];
    c[2] = a[2]*k + b[2];
}

GLfloat vector3_dot(const Vector3 a, const Vector3 b) {
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

// vectors cannot overlap
void vector3_cross(const Vector3 a, const Vector3 b, Vector3 c) {
    c[0] = a[1]*b[2]-a[2]*b[1];
    c[1] = a[2]*b[0]-a[0]*b[2];
    c[2] = a[0]*b[1]-a[1]*b[0];
}

