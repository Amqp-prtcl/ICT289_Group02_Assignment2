#include "matrix.h"
#include "math.h"
#include "dbg.h"

#define THRESH 0.00001

#define I(a, b) a*3+b
//int inverse_3x3_matrix(const GLfloat *in, GLfloat *out) {
int matrix_invert(const Matrix3x3 in, Matrix3x3 out) {
    GLfloat det = in[I(0,0)] * (in[I(1,1)] * in[I(2,2)] - in[I(2,1)] * in[I(1,2)]) -
                in[I(0,1)] * (in[I(1,0)] * in[I(2,2)] - in[I(1,2)] * in[I(2,0)]) +
                in[I(0,2)] * (in[I(1,0)] * in[I(2,1)] - in[I(1,1)] * in[I(2,0)]);

#ifdef DEBUG
    if (ABS(det) <= THRESH) {
        DBG_PRINT("Matrix inverse bad determinant: %f\n", det);
        return 0;
    }
#endif

    det = 1/det;

    // normal inverse
    /*
    out[I(0,0)] = det * (in[I(1,1)] * in[I(2,2)] - in[I(2,1)] * in[I(1,2)]);
    out[I(0,1)] = det * (in[I(0,2)] * in[I(2,1)] - in[I(0,1)] * in[I(2,2)]);
    out[I(0,2)] = det * (in[I(0,1)] * in[I(1,2)] - in[I(0,2)] * in[I(1,1)]);
    out[I(1,0)] = det * (in[I(1,2)] * in[I(2,0)] - in[I(1,0)] * in[I(2,2)]);
    out[I(1,1)] = det * (in[I(0,0)] * in[I(2,2)] - in[I(0,2)] * in[I(2,0)]);
    out[I(1,2)] = det * (in[I(1,0)] * in[I(0,2)] - in[I(0,0)] * in[I(1,2)]);
    out[I(2,0)] = det * (in[I(1,0)] * in[I(2,1)] - in[I(2,0)] * in[I(1,1)]);
    out[I(2,1)] = det * (in[I(2,0)] * in[I(0,1)] - in[I(0,0)] * in[I(2,1)]);
    out[I(2,2)] = det * (in[I(0,0)] * in[I(1,1)] - in[I(1,0)] * in[I(0,1)]);
    */

    out[I(0,0)] = det * (in[I(1,1)] * in[I(2,2)] - in[I(2,1)] * in[I(1,2)]);
    out[I(0,1)] = det * (in[I(1,2)] * in[I(2,0)] - in[I(1,0)] * in[I(2,2)]);
    out[I(0,2)] = det * (in[I(1,0)] * in[I(2,1)] - in[I(2,0)] * in[I(1,1)]);
    out[I(1,0)] = det * (in[I(0,2)] * in[I(2,1)] - in[I(0,1)] * in[I(2,2)]);
    out[I(1,1)] = det * (in[I(0,0)] * in[I(2,2)] - in[I(0,2)] * in[I(2,0)]);
    out[I(1,2)] = det * (in[I(2,0)] * in[I(0,1)] - in[I(0,0)] * in[I(2,1)]);
    out[I(2,0)] = det * (in[I(0,1)] * in[I(1,2)] - in[I(0,2)] * in[I(1,1)]);
    out[I(2,1)] = det * (in[I(1,0)] * in[I(0,2)] - in[I(0,0)] * in[I(1,2)]);
    out[I(2,2)] = det * (in[I(0,0)] * in[I(1,1)] - in[I(1,0)] * in[I(0,1)]);

    return 1;
}

void matrix_vector_mul(const Matrix3x3 m, const Vector3 in, Vector3 out) {
    GLfloat t;
    for (size_t i = 0; i < 3; i++) {
        t = 0;
        for (size_t j = 0; j < 3; j++)
            t += in[j] * m[I(i, j)];
        out[i] = t;
    }
}

void matrix_rotate_vector(const Vector3 rotation, const Vector3 in,
        Vector3 out) {
    GLfloat cosa, sina, cosb, sinb, cosy, siny;
    cosa = cosf(rotation[0] * M_PI/180);
    sina = sinf(rotation[0] * M_PI/180);

    cosb = cosf(rotation[1] * M_PI/180);
    sinb = sinf(rotation[1] * M_PI/180);

    cosy = cosf(rotation[2] * M_PI/180);
    siny = sinf(rotation[2] * M_PI/180);

    /*Matrix3x3 m = {
        cosb*cosa, cosa*sinb*siny-sina*cosy, cosa*sinb*cosy+sina*siny,
        cosb*sina, sina*sinb*siny+cosa*cosy, sina*sinb*cosy-cosa*siny,
        -sinb, cosb*siny, cosb*cosy,
    };*/
    Matrix3x3 m = {
        cosb*cosy-sina*sinb*siny, -cosa*siny, sinb*cosy+sina*cosb*siny,
        cosb*sina+sina*sinb*cosy,  cosa*cosy, sinb*siny-sina*cosb*cosy,
        -cosa*sinb, sina, cosa*cosb,
    };
    matrix_vector_mul(m, in, out);
}

void matrix_rotate_vector_around_point(const Vector3 rot, const Vector3 ancor,
        const Vector3 in, Vector3 out) {
    Vector3 dir;
    vector3_sub(in, ancor, dir);

    matrix_rotate_vector(rot, dir, out);

    vector3_add(ancor, out, out);
}

void matrix_vector_get_angles(const Vector3 in, Vector3 out) {
    Vector3 a, rot = {0};
    GLfloat n, b, d, ax, ay;

    a[0] = in[0];
    a[1] = 0;
    a[2] = in[2];
    n = vector3_norm(a);
    b = vector3_dot(vector3_backward, a);
    d = vector3_dot(vector3_right, a);
    ay = (float)acos(b/n) * 180/M_PI;
    if (d <= 0.0)
        ay *= -1.0;

    rot[1] = -ay;
    matrix_rotate_vector(rot, in, out);

    a[0] = 0;
    a[1] = out[1];
    a[2] = out[2];
    n = vector3_norm(a);
    b = vector3_dot(vector3_backward, a);
    d = vector3_dot(vector3_up, a);
    ax = (float)acos(b/n) * 180/M_PI;
    if (d <= 0.0)
        ax *= -1.0;

    out[0] = ax;
    out[1] = ay;
    out[2] = 0;
}

