#ifndef TEXTUREMAP_H
#define TEXTUREMAP_H
#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>
#include <cstring>
#include <omp.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "matrixStack.h"
#include "RAWmodel.h"
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

typedef struct intensityTex_t{
    int x,y,z;
    unsigned int texture3D;
    float *data;
}intensityTex_t;

typedef struct colormapTex_t
{
    int color = 255;
    unsigned int texture1D;
    float *data;
}colormapTex_t;

typedef struct threeDTex_t{
    int width = 10, height = 10, depth = 10;
    unsigned int texture;
    float *data;
}threeDTex_t;

class texture_cls{
public:
    texture_cls();
    ~texture_cls();
    void create_texture();
    void bindTexture(int bind);
    void updataColorMap(vector<float> newdata);
    void updateIntensityMap();
    glm::fvec3 compute_voxel_texture(MatrixStack tex, glm::fvec4 texCoord);

    imageTex_t imageTex[3];
    threeDTex_t threeDTex;
    shadowTex_t shadowTex;
    intensityTex_t intensityTex;
    colormapTex_t colormapTex;

private:
    void create_img_tex();
    void create_3D_tex();
    void create_depth_tex();
    void create_ray_tex();
    const char* texName[3] = {"texture/stru.png", "texture/pattern.png", "texture/wwb.png"};
    void texture1Dto2D(int nrChannels, int t);
};

extern texture_cls tex;

#endif