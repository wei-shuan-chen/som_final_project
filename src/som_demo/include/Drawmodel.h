#ifndef DRAWMODEL_H
#define DRAWMODEL_H
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <thread>

#include "SOM.h"
#include "RAWmodel.h"
#include "matrixStack.h"
#include "shader.h"
#include "textureMap.h"
#include "Item.h"
#include "world.h"
#include "logger.h"
#include "camera.h"
#include "Gui.h"

typedef struct matrix_t{

}matrix_t;


class model_cls{
public:
    model_cls();
    ~model_cls();

    void Shader_Create();
    void Shader_Use();
    void Model_mapping();


    Camera camera;
    glm::vec3 lightPos;
    const unsigned int SCR_WIDTH = 800, SCR_HEIGHT = 600;
    float rate;
    bool showVoxel = true;
    bool showLatticePlane = true;
    bool showLatticeLine = true;


private:
    void Modify_position(int x, int y, int z);
    void Shader_init(int n, bool settex);
    void ViewProjection_Create(int n);

    void Model_Floor_Create(Shader shader);
    void Model_create(Shader shader);
    void Model_create_noshadow(Shader shader);
    void Model_lightCube_create(Shader shader);

    void ourShader_model();
    void depthShader_model();
    void lightShader_model();

    glm::fvec2 findMinDistPrecisePos(const LatData_t* latticeData, double mid, glm::fvec3 voxelPos, glm::ivec3 minLatticeCoord, int de);
    glm::fvec3 pointTotriangle(glm::fvec3 o, glm::fvec3 a1, glm::fvec3 a2, glm::fvec3 projp, glm::fvec3 vector_n);

    glm::fvec3 crossPruduct(glm::fvec3 a, glm::fvec3 b);
    float innerProduct(glm::fvec3 a, glm::fvec3 b);

    MatrixStack model;
    MatrixStack view;
    MatrixStack projection;
    std::vector<glm::mat4> shadowTransforms;

    Shader ourShader;
    Shader lightShader;
    Shader depthShader;

    Item cube;
    Item lightcube;
    Item ground;
    Item voxel;
    Item lattice_line;
    Item lattice_plane;

    float near_plane = 0.01f, far_plane = 10000000.0f;
};
extern model_cls drawModel;

extern bool startSOM;
extern void createThread();
#endif