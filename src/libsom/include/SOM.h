#ifndef SOM_H
#define SOM_H

#include <vector>
#include <iomanip>
#include <glm/glm.hpp>
#define PI 3.14159265

using namespace std;

enum latType
{
    PLANE,
    CYLINDER,
    DONUT,
    BALL,
    CUBE
};

enum texType
{
    TWODTEX,
    THREEDTEX
};

enum weightType
{
    POS,
    TEX
};

typedef struct LatData_t
{
    glm::fvec3 ***wPos; // [5][h][w]
    glm::fvec3 ***wTex;

    int width;
    int height;
    int depth;

    int iter[2] = {0, 0};
    int finalIter[2] = {120000, 120000};
    double initLearningRate[2] = {0.005, 0.005};
    double initRadius[2] = {width / 2.0, width / 2.0};

    int type = 1; // 0 plane, 1 cylinder, 2 donut, 3 ball, 4 3Dlattice,
    int typeNum[7] = {1, 1, 1, 6, 10};

    int texType = 0; // 2D, 3D
    int texTypeNum[2] = {1, 100};

    glm::ivec3 *anchorP; // 0~3 front 4~7 back  (leftdown rightdown leftup rightup)

} LatData_t;

typedef struct InputData_t
{
    glm::fvec3 *iPos;
    glm::fvec3 *iTex;
    // int dataExtraPoint[4];
    int nPos = 0;
    int nTex = 0;
} InputData_t;

class som_cls
{
public:
    som_cls();
    ~som_cls();

    void SOM_Create(std::vector<glm::ivec3> voxelPos, int voxelNum, glm::ivec3 max, glm::ivec3 min, int type, glm::ivec3 texWHD, int texType);
    void SOM_IterateOnce(int wType);
    void SOM_End();

    LatData_t *Lattice_get();

    void Lattice_resolution_set(int resolution, glm::ivec3 max, glm::ivec3 min);
    void Lattice_iter_set(int finalIter);
    void Lattice_radius_set(float initradius);
    void Lattice_rate_set(float initrate);
    void Lattice_type_set(int type, glm::ivec3 max, glm::ivec3 min);
    void Lattice_pos_set(std::vector<glm::ivec3> voxelPos, int voxelNum, glm::ivec3 max, glm::ivec3 min);
    void Lattice_tex_set(glm::ivec3 texWHD);
    void Lattice_anchor_set(glm::ivec3 *newp);

private:
    LatData_t latticeData;
    InputData_t inputData;
    int weightType = 0; // 0 POS, 1 TEX
    // som init
    void som_init();
    // som create
    glm::fvec3 ***create_weight_position(glm::ivec3 max, glm::ivec3 min);
    glm::fvec3 ***create_weight_texture(); // 0 fld, 1 frd, 2flt, 3 frt, 4 bld, 5brd, 6blt, 7brt
    glm::fvec3 ***create_weight_texture_2D(glm::fvec3 ***texWeight); // 0 fld, 1 frd, 2flt, 3 frt, 4 bld, 5brd, 6blt, 7brt
    glm::fvec3 ***create_weight_texture_3D(); // 0 fld, 1 frd, 2flt, 3 frt, 4 bld, 5brd, 6blt, 7brt
    glm::fvec3 *create_input_position(std::vector<glm::ivec3> voxelPos, int voxelNum);
    glm::fvec3 *create_input_texture(glm::ivec3 texWHD);
    // som iterate
    double compute_learningrate();
    double compute_radius();
    const glm::fvec3 get_input();
    const glm::ivec3 find_bmu(glm::fvec3 nowInput);
    double compute_scale(double sigma, double dist);
    void update_node(glm::fvec3 nowInput, glm::ivec3 update, double scale, double learningRate);

    glm::ivec3 comput_neiborhood(glm::ivec3 node, glm::ivec3 bmu);
    glm::ivec3 compute_halfball_dist(glm::ivec3 p0);
    bool inradius_neiborhood(double squaredDist, double radius);
    // ~som_cls
    void destroy_weight_position(int depth);
    void destroy_weight_texture(int depth);
    void destroy_input_position();
    void destroy_input_texturea();
};

void create_mutli_som(int layer, int block);

extern som_cls **som;
extern som_cls psom;

// enum Alphabet : int {
//     A,
//     B,
//     C,
// };

// Alphabet::A;

// class A {
// public:
//     static print();
// };
// class B {
// private:
//     B();
// public:
//     static B* Get();
//     static print();
// };

// B* b1 = B::Get();

// static int count = 0;
// void print() {
//     //static int count = 0;
//     count++;
// }

// void print2() {
//     count = 100;
// }

#endif