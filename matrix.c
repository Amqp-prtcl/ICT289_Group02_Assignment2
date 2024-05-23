#include "matrix.h"
#include "math.h"
#include "dbg.h"

#define THRESH 0.3

#define I(a, b) a+b*3
//int inverse_3x3_matrix(const GLfloat *in, GLfloat *out) {
int matrix_invert(const Matrix3x3 in, Matrix3x3 out) {
    GLfloat det = in[I(0,0)] * (in[I(1,1)] * in[I(2,2)] - in[I(2,1)] * in[I(1,2)]) -
                in[I(0,1)] * (in[I(1,0)] * in[I(2,2)] - in[I(1,2)] * in[I(2,0)]) +
                in[I(0,2)] * (in[I(1,0)] * in[I(2,1)] - in[I(1,1)] * in[I(2,0)]);

#ifdef DEBUG
    if ((det < 0 ? -det : det) <= THRESH) {
        DBG_PRINT("Matrix inverse bad determinant: %f\n", det);
        return 0;
    }
#endif

    det = 1/det;

    /* normal inverse
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

    out[I(0,0)] =   det * (in[I(1,1)] * in[I(2,2)] - in[I(2,1)] * in[I(1,2)]);
    out[I(0,1)] = - det * (in[I(0,1)] * in[I(2,2)] - in[I(0,2)] * in[I(2,1)]);
    out[I(0,2)] =   det * (in[I(0,1)] * in[I(1,2)] - in[I(0,2)] * in[I(1,1)]);
    out[I(1,0)] = - det * (in[I(1,0)] * in[I(2,2)] - in[I(1,2)] * in[I(2,0)]);
    out[I(1,1)] =   det * (in[I(0,0)] * in[I(2,2)] - in[I(0,2)] * in[I(2,0)]);
    out[I(1,2)] = - det * (in[I(0,0)] * in[I(1,2)] - in[I(1,0)] * in[I(0,2)]);
    out[I(2,0)] =   det * (in[I(1,0)] * in[I(2,1)] - in[I(2,0)] * in[I(1,1)]);
    out[I(2,1)] = - det * (in[I(0,0)] * in[I(2,1)] - in[I(2,0)] * in[I(0,1)]);
    out[I(2,2)] =   det * (in[I(0,0)] * in[I(1,1)] - in[I(1,0)] * in[I(0,1)]);

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

void matrix_rotate_vector(const Vector3 rotation, Vector3 out) {
	GLfloat cosa, sina, cosb, sinb, cosy, siny;
	cosa = cosf(0);//rotation[0] * M_PI/180);
	sina = sinf(0);//rotation[0] * M_PI/180);

	cosb = cosf(rotation[1] * M_PI/180);
	sinb = sinf(rotation[1] * M_PI/180);

	cosy = cosf(rotation[2] * M_PI/180);
	siny = sinf(rotation[2] * M_PI/180);

	Matrix3x3 m = {
		cosb*cosa, cosa*sinb*siny-sina*cosy, cosa*sinb*cosy+sina*siny,
		cosb*sina, sina*sinb*siny+cosa*cosy, sina*sinb*cosy-cosa*siny,
		-sinb, cosb*siny, cosb*cosy,
	};
	matrix_vector_mul(m, vector3_forward, out);
}
