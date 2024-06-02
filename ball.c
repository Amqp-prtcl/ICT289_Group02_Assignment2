#include "ball.h"
#include "dbg.h"

#include "light.h"
#include "material.h"

#include "math.h"

void drawTexturedSphere(float radius, int slices, int stacks) {
    for (int i = 1; i <= stacks; ++i) {
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / stacks);
        double z0  = sin(lat0);
        double zr0 =  cos(lat0);

        double lat1 = M_PI * (-0.5 + (double) i / stacks);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= slices; ++j) {
            double lng = 2 * M_PI * (double) (j - 1) / slices;
            double x = cos(lng);
            double y = sin(lng);

            double u = (double)(j) / slices;
            double v0 = (double)(i - 1) / stacks;
            double v1 = (double)i / stacks;

            glTexCoord2f(u, v0);
            glNormal3f(x * zr0, y * zr0, z0);
            glVertex3f(x * zr0 * radius, y * zr0 * radius, z0 * radius);

            glTexCoord2f(u, v1);
            glNormal3f(x * zr1, y * zr1, z1);
            glVertex3f(x * zr1 * radius, y * zr1 * radius, z1 * radius);
        }
        glEnd();
    }
}

void draw_ball(const struct ball *ball) {
    if (ball->off)
        return;
    glPushMatrix();
    //glColor3fv(ball->color);
    glColor3f(1,1,1);
    glBindTexture(GL_TEXTURE_2D,ball->texture);
    object_trans_apply(&ball->trans);
    //glutWireSphere(ball_get_radius(ball), 30, 30);

    apply_material(get_mat(BALL));

    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    drawTexturedSphere(ball_get_radius(ball), 30, 30);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void ball_ball_collision(struct ball *b1, struct ball *b2) {
    Vector3 dist, vr;
    GLfloat d, impulse;

    vector3_sub(b2->trans.position, b1->trans.position, dist);
    d = vector3_norm(dist);

    if (d > ball_get_radius(b1) + ball_get_radius(b2))
        return;

    // normalize dist
    vector3_scale(dist, 1/d, dist);
    vector3_sub(b2->phys.speed, b1->phys.speed, vr);
    impulse = vector3_dot(dist, vr)*(b1->phys.mass + b2->phys.mass)/2.0;

    //impulse
    vector3_affine(dist, impulse/b1->phys.mass,
            b1->phys.speed, b1->phys.speed);
    vector3_affine(dist, -impulse/b2->phys.mass,
            b2->phys.speed, b2->phys.speed);

    vector3_affine(dist, -ball_get_radius(b1)-ball_get_radius(b2)+d,
            b1->trans.position, b1->trans.position);
}

