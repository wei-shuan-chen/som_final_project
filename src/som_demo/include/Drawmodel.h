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
#include "carve.h"

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
    bool showOutSomIn[3] = {true, true, true};
    bool showLatticePlane = true;
    bool showLatticeLine = true;
    bool* showEachLayer;


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

    MatrixStack model;
    MatrixStack view;
    MatrixStack projection;
    std::vector<glm::mat4> shadowTransforms;

    Shader ourShader;
    Shader lightShader;
    Shader depthShader;

    Item cube;
    Item axis;
    Item lightcube;
    Item ground;
    Item* somVoxel;
    Item innerVoxel;
    Item outerVoxel;
    Item* lattice_line;
    Item* lattice_plane;

    float near_plane = 0.01f, far_plane = 10000000.0f;
};
extern model_cls drawModel;

extern bool startSOM;
extern void createThread();
#endif