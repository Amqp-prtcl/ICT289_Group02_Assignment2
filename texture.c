#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "lib/stb_image.h"

#include "dbg.h"

GLuint LoadTex(const char* path)
{
    GLuint id;

    int width, height, nrChannels;
    unsigned char *image = stbi_load(path, &width, &height, &nrChannels, 0);
    if(!image) {
        printf("échec du chargement");
        return 999;
    }

    glGenTextures(1,&id);
    glBindTexture(GL_TEXTURE_2D, id);//textureId);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


    GLenum format = GL_RGB;
    if(nrChannels == 1)
        format = GL_RED;
    else if(nrChannels == 4)
        format = GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D,0,format,(GLsizei) width,(GLsizei) height,
            0,format,GL_UNSIGNED_BYTE,image);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//GL_CLAMP_TO_BORDER
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    stbi_image_free(image);

    return id;
}

/*
void draw_texture(GLuint id) {
    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, id);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0);
    glTexCoord2f(1, 0.0);
    glVertex3f(2.0, 0.0, 0.0);
    glTexCoord2f(1, 1);
    glVertex3f(2, 2.0, 0.0);
    glTexCoord2f(0.0, 1);
    glVertex3f(0.0, 2.0, 0.0);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}
*/

GLuint* LoadAllTex(const char** paths, size_t n)
{
    GLuint* TexTable = malloc(n*sizeof(GLuint));
    for(size_t i = 0; i<n;i++)
    {
        TexTable[i] = LoadTex(paths[i]);
    }
    return TexTable;
}
