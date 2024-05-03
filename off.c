#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "off.h"

#include "float.h"


// fills the struct off from a file
// returns non-zero value on error
int readOFFFile(struct off *off, const char *filename) {
    if (off == NULL || filename == NULL)
        return EXIT_FAILURE;

    char magic[7];
    size_t nvert, nfaces, nedges;
    Vector3 *vertices;
    struct off_triangle *triangles;

    size_t i;

    FILE *f = fopen(filename, "rb");
    if (f == NULL)
        return EXIT_FAILURE;

    if (fgets(magic, 7, f) == NULL) {
        goto err;
    }

    magic[3] = 0; // to trim \r\n
    if (strcmp(magic, "OFF") != 0) {
        goto err;
    }

    if (fscanf(f, "%zu %zu %zu\n", &nvert, &nfaces, &nedges) != 3)
        goto err;

    vertices = malloc(nvert * sizeof(Vector3));
    if (vertices == NULL)
        goto err;

    for (i = 0; i < nvert; i++) {
        if (fscanf(f, "%f %f %f", *(vertices+i), *(vertices+i)+1,
                    *(vertices+i)+2) != 3)
            goto err_vert;
    }

    triangles = malloc(nfaces * sizeof(struct off_triangle));
    if (triangles == NULL)
        goto err_vert;

    for (i = 0; i < nfaces; i++) {
        if (fscanf(f, "%*d %zu %zu %zu", &(triangles[i].p1),
                    &(triangles[i].p2), &(triangles[i].p3)) != 3)

            goto err_faces;
    }

    off->vertices = vertices;
    off->triangles = triangles;
    off->nvert = nvert;
    off->nfaces = nfaces;
    //off->nedges = nedges;

    fclose(f);
    return EXIT_SUCCESS;

err_faces:
    free(triangles);
err_vert:
    free(vertices);
err:
    fclose(f);
    return EXIT_FAILURE;
}

int writeOFFFile(const struct off *off, const char *filename) {
    (void)off;
    (void)filename;
    return 0;
}
/*
int writeOFFFile(const struct off *off, const char *filename) {
    if (off == NULL || filename == NULL ||
            off->vertices == NULL || off->triangles == NULL)
        return 1;

    FILE *f = fopen(filename, "wb");
    if (f == NULL)
        return 2;

    if (fprintf(f, "OFF\n%zu %zu %zu\n", off->nvert, off->nfaces,
                0 off->nedges*//*) < 0) {
        fclose(f);
        return 3;
    }

    struct vector *vect;
    for (size_t i = 0; i < off->nvert; i++) {
        vect = off->vertices + i;
        if (fprintf(f, "%.*f %.*f %.*f\n", DBL_DIG, vect->x, DBL_DIG, vect->y,
                    DBL_DIG, vect->z) < 0) {
            fclose(f);
            return 4;
        }
    }

    struct off_triangle *tria;
    for (size_t i = 0; i < off->nfaces; i++) {
        tria = off->triangles + i;
        if (fprintf(f, "3 %zu %zu %zu\n", tria->p1, tria->p2, tria->p3) < 0) {
            fclose(f);
            return 5;
        }
    }

    fclose(f);
    return 0;
}
*/

void freeOFF(struct off *off) {
    if (off == NULL)
        return;

    off->nvert = 0;
    off->nfaces = 0;
    //off->nedges = 0;

    if (off->vertices != NULL) {
        free(off->vertices);
        off->vertices = NULL;
    }

    if (off->triangles != NULL) {
        free(off->triangles);
        off->triangles = NULL;
    }
}

//#include "stdio.h"
static void get_centerOFF(const struct off *off, Vector3 out) {
    vector3_to_zero(out);
    for (size_t i = 0; i < off->nvert; i++) {
        out[0] += off->vertices[i][0];
        out[1] += off->vertices[i][1];
        out[2] += off->vertices[i][2];
        //printf("out = {%f, %f, %f}\n", out[0], out[1], out[2]);
    }
    //printf("k = %f\n", 1/off->nvert);
    vector3_scale(out, 1.0/off->nvert, out);
}

static GLfloat get_radiusOFF(const struct off *off, const Vector3 center) {
    GLfloat n = 0;

    GLfloat nv;
    Vector3 v;
    for (size_t i = 0; i < off->nvert; i++) {
        vector3_sub(off->vertices[i], center, v);
        nv = vector3_norm(v);

        if (n < nv)
            n = nv;
    }
    return n;
}

static void alignOFF(struct off *off, const Vector3 center) {
    Vector3 *v = off->vertices;
    for (size_t i = 0; i < off->nvert; i++) {
        vector3_sub(v[i], center, v[i]);
    }
}

static void scaleOFF(struct off *off, const GLfloat factor) {
    Vector3 *v = off->vertices;
    for (size_t i = 0; i < off->nvert; i++) {
        vector3_scale(v[i], factor, v[i]);
    }
}

//#include "stdio.h"
void normalizeOFF(struct off *off) {
    Vector3 c;
    GLfloat r;

    get_centerOFF(off, c);
    r = get_radiusOFF(off, c);

    //printf("center = %f, %f, %f\n", c[0], c[1], c[2]);
    //printf("radius = %f (factor = %f)\n", r, 1/r);

    alignOFF(off, c);
    scaleOFF(off, 1/r);
}
