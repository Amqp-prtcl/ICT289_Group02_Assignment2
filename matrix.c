#include "matrix.h"
#include "dbg.h"

#define THRESH 0.3

#define I(a, b) a+3*b
int inverse_3x3_matrix(const GLfloat *in, GLfloat *out) {
    GLfloat det = in[I(0,0)] * (I(1,1) * in[I(2,2)] - in[I(2,1)] * in[I(1,2)]) -
                in[I(0,1)] * (in[I(1,0)] * in[I(2,2)] - in[I(1,2)] * in[I(2,0)]) +
                in[I(0,2)] * (in[I(1,0)] * in[I(2,1)] - in[I(1,1)] * in[I(2,0)]);

#ifdef DEBUG
    if ((det < 0 ? -det : det) <= THRESH) {
        DBG_PRINT("Matrix inverse bad determinant: %f\n", det);
        return 0;
    }
#endif

    det = 1/det;

    out[I(0,0)] = det * (in[I(1,1)] * in[I(2,2)] - in[I(2,1)] * in[I(1,2)]);
    out[I(0,1)] = det * (in[I(0,2)] * in[I(2,1)] - in[I(0,1)] * in[I(2,2)]);
    out[I(0,2)] = det * (in[I(0,1)] * in[I(1,2)] - in[I(0,2)] * in[I(1,1)]);
    out[I(1,0)] = det * (in[I(1,2)] * in[I(2,0)] - in[I(1,0)] * in[I(2,2)]);
    out[I(1,1)] = det * (in[I(0,0)] * in[I(2,2)] - in[I(0,2)] * in[I(2,0)]);
    out[I(1,2)] = det * (in[I(1,0)] * in[I(0,2)] - in[I(0,0)] * in[I(1,2)]);
    out[I(2,0)] = det * (in[I(1,0)] * in[I(2,1)] - in[I(2,0)] * in[I(1,1)]);
    out[I(2,1)] = det * (in[I(2,0)] * in[I(0,1)] - in[I(0,0)] * in[I(2,1)]);
    out[I(2,2)] = det * (in[I(0,0)] * in[I(1,1)] - in[I(1,0)] * in[I(0,1)]);

    return 1;
}
