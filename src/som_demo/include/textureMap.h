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
#include "SOM.h"
#include "logger.h"

using namespace std;

enum wrapType
{
    REPEAT,
    BORDER
};
typedef struct textureMap_t
{
    int anglehw = 0;
    int angledh = 0;
    int angledw = 0;
    glm::fvec3 translate = {0.0, 0.0,0.0};
    glm::fvec3 scale = {1.0, 1.0, 1.0};
    glm::fvec2 resolution_w = {0.0, 1.0};//low hight
    glm::fvec2 resolution_h = {0.0, 1.0};
    glm::fvec2 resolution_d = {0.0, 1.0};
    int wrapType = 0;
    MatrixStack texture_m;
} textureMap_t;

typedef struct imageTex_t
{
    int width, height;
    unsigned int texture;
    unsigned char *data;
    glm::ivec3 **image;
} imageTex_t;

typedef struct shadowTex_t
{
    const unsigned int width = 1024, height = 1024;
    unsigned int depthCubemap;
    unsigned int depthFBO;
} shadowTex_t;

typedef struct intensityTex_t
{
    int x, y, z;
    unsigned int texture3D;
    float *data;
} intensityTex_t;

typedef struct colormapTex_t
{
    int color = 255;
    unsigned int texture1D;
    float *data;
} colormapTex_t;

typedef struct threeDTex_t
{
    int width = 1024, height = 1024, depth = 100;
    unsigned int texture;
    float *data;
} threeDTex_t;

class texture_cls
{
public:
    texture_cls();
    ~texture_cls();
    void create_texture();
    void bind_texture(int bind);
    void updata_colorMap(vector<float> newdata);
    void update_intensityMap();
    glm::fvec3 lattice_to_texture(glm::fvec4 texCoord, int degree);

    int texTypeNum = 3;
    imageTex_t imageTex[3];
    threeDTex_t threeDTex;
    shadowTex_t shadowTex;
    intensityTex_t intensityTex;
    colormapTex_t colormapTex;

    textureMap_t texMatrix2D;
    textureMap_t texMatrix3D;

private:
    void create_img_tex();
    void create_3D_tex();
    void create_depth_tex();
    void create_ray_tex();
    const char *texName[3] = {"texture/color.png", "texture/pattern.png", "texture/tmp.png"};
    void texture1Dto2D(int nrChannels, int t);
};

extern texture_cls tex;

#endif