#include "stdio.h"
#include "matrix.h"

int main() {
    float m[9] = {
        0, 1, 0,
        1, 1, 0,
        1, 0, 1,
    };
    float n[9];

    inverse_3x3_matrix(m, n);

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3;j++) {
            printf("%f ", n[j+3*i]);
        }
        printf("\n");
    }
}
