#ifndef SOM_H
#define SOM_H

#include <vector>
#include <glm/glm.hpp>


#define PI 3.14159265

using namespace std;

typedef struct LatData {
    glm::fvec3*** lattice; // [5][h][w]

    int map_width = 30;
    int map_height = 30;
    const int max_iter = 120000;
    int iter = 0;
    double learning_rate = 0.005;
    double neighbor = map_width/2.0;
    int shapeLattice = 4;// 0 random cylinder, 1 cylinder, 2 random flat, 3 flat, 4 halfball, 5 donut
}LatData;


LatData* Lattice_Struct_Use();
void SOM_Create(std::vector<glm::ivec3>  bounderVoxelData, int bounderNum, glm::ivec3 max);
void SOM_IterateOnce();
void SOM_Destroy();
void SOM_Again();

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