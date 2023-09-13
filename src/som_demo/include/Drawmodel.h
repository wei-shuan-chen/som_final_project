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
#include "Math.h"


class model_cls{
public:
    model_cls();
    ~model_cls();

    void Shader_Create();
    void Shader_Use(GLFWwindow *window);
    void Model_mapping();
    void Lattice_renew(int layer, int block);
    void Voxel_renew();
    void pVoxel_renew();
    void psom_axis_renew(glm::mat3x3 A, glm::vec3 t);

    Camera camera;
    glm::vec3 lightPos;
    int SCR_WIDTH = 800, SCR_HEIGHT = 600;
    float rate;

    bool showVoxel = true;
    bool showOutSomIn[3] = {true, true, true};
    bool showLatticePlane = true;
    bool showLatticeLine = true;
    bool** showEachPart;

    // texture_t texInfo;
    // MatrixStack texture_m;

private:

    void Modify_position(int x, int y, int z);
    void Shader_init(int n, bool settex);
    void ViewProjection_Create(int n);

    void Model_Floor_Create(Shader shader);
    void Model_create(Shader shader);
    void Model_bound_create(Shader shader);
    void Model_lattice_create(Shader shader);
    void Model_axis_create(Shader shader);
    void Model_lightCube_create(Shader shader);

    void rayShader_model(GLFWwindow *window);
    void depthShader_model(GLFWwindow *window);
    void shader_model();
    glm::fvec3 vector_matrix(glm::mat4 matrix, glm::fvec4 vec);

    MatrixStack model;
    MatrixStack view;
    MatrixStack projection;
    std::vector<glm::mat4> shadowTransforms;

    Shader rayShader;
    Shader shader;
    Shader depthShader;

    Item boundingbox;
    Item axis;
    Item p_axis;
    Item lightcube;
    Item ground;
    Item** somVoxel;
    Item innerVoxel;
    Item outerVoxel;
    Item psomVoxel;
    Item** s_lattice_line;
    Item** s_lattice_plane;
    Item ps_lattice_line;
    Item ps_lattice_plane;

    float near_plane = 0.01f, far_plane = 10000000.0f;
};
extern model_cls drawModel;

extern bool startSOM;
extern void createThread();
#endif