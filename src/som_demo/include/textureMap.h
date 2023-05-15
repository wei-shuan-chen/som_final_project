#ifndef TEXTUREMAP_H
#define TEXTUREMAP_H
#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>
#include <cstring>
#include <omp.h>
#include <glm/glm.hpp>

#include "logger.h"

using namespace std;

typedef struct imageTex_t{
    int width, height;
    unsigned int texture;
    unsigned char *data;
    glm::ivec3** image;
}imageTex_t;

typedef struct shadowTex_t{
    const unsigned int width = 1024, height = 1024;
    unsigned int depthCubemap;
    unsigned int depthFBO;
}shadowTex_t;


class texture_cls{
public:
    texture_cls();
    ~texture_cls();
    void createTexture();
    void createdepthTexture();
    void bindTexture(int act, int bind);
    imageTex_t imageTex;
    shadowTex_t shadowTex;
private:
    void texture1Dto2D(int nrChannels);
};

extern texture_cls tex;

#endif