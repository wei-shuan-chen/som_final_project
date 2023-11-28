#ifndef SOM_H
#define SOM_H

#include <vector>
#include <glm/glm.hpp>

#define PI 3.14159265

using namespace std;

enum latType{
    PLANE,
    CYLINDER,
    DONUT,
    BALL,
    THREED
};

typedef struct LatData_t {
    glm::fvec3*** lattice; // [5][h][w]

    int width;
    int height;
    int depth;

    int iter = 0;
    int finalIter = 120000;

    double learningRate = 0.005;
    double initLearningRate = 0.005;

    double radius = width/2.0;
    double initRadius = width/2.0;

    int type = 1;// 0 plane, 1 cylinder, 2 donut, 3 ball, 4 3Dlattice
    int typeNum[5] = {1,1,1,6,10};
}LatData_t;

typedef struct InputData_t {
    glm::fvec3 *input;
    // int dataExtraPoint[4];
    int num = 0;
}InputData_t;

class som_cls{
public:
    som_cls();
    ~som_cls();

    void SOM_Create(std::vector<glm::ivec3> voxelPos, int voxelNum, glm::ivec3 max, glm::ivec3 min, int type);
    void SOM_IterateOnce();
    void SOM_End();

    LatData_t* Lattice_get();

    void Lattice_resolution_set(int resolution, glm::ivec3 max, glm::ivec3 min);
    void Lattice_iter_set(int finalIter);
    void Lattice_radius_set(float initradius);
    void Lattice_rate_set(float initrate);
    void Lattice_type_set(int type, glm::ivec3 max, glm::ivec3 min);
    void Lattice_set(std::vector<glm::ivec3> voxelPos, int voxelNum,glm::ivec3 max, glm::ivec3 min);

private:
    LatData_t latticeData;
    InputData_t inputData;
    // glm::ivec2 bmuMove[9] = {{1, 1},{0, 1},{-1, 1},{-1, 0},{-1, -1},{0, -1},{1, -1},{1, 0},{1, 1}};
    // int ballneighber[6][4] = {{4,3,2,1},{4,0,2,5},{0,3,5,1},{4,0,2,5,},{0,3,5,1},{4,3,2,1}};

    // som init
    void som_init();
    // som create
    glm::fvec3 ***createLatticeData(int width, int height, int depth, glm::ivec3 max, glm::ivec3 min);
    glm::fvec3 *createInputDataset(std::vector<glm::ivec3> voxelPos, int voxelNum);
    // som iterate
    double computeLearningRate();
    double computeRadius();
    const glm::fvec3 getInput();
    const glm::ivec3 findBmu(glm::fvec3 nowInput);
    // void findBmuNeighbor(glm::fvec3 nowInput, const glm::ivec3 bmu);
    // void ensureNeighbor(glm::fvec3 nowInput, const glm::ivec3 bmu, glm::ivec2 move, double squaredDist);
    //     int computDelta(int edge, int tmp);
        double computeScale(double sigma, double dist);
        void updateNode(glm::fvec3 ***lattice, glm::fvec3 nowInput, glm::ivec3 update, double scale, double learningRate);

    glm::ivec3 computNeiborhood(glm::ivec3 node, glm::ivec3 bmu);
    glm::ivec3 computeHalfballDist(glm::ivec3 p0);
    bool isInradiushood(double squaredDist, double radius);
    // ~som_cls
    void destroy(int depth);
    void destroyDataset();
};

void create_mutli_som(int layer, int block);

extern som_cls** som;
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