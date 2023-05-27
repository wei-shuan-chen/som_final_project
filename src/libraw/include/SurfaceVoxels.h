#ifndef SURFACEVOXELS_H
#define SURFACEVOXELS_H
#include <glm/glm.hpp>


typedef struct UnitSurfaceVoxData_t {

    glm::ivec3 locate = {0,0,0}; // only bounder voxel's locate(x,y,z)
    bool faceAir[6] = {true}; // 0 face air, 1 face inside
    glm::fvec3 color = {0.8, 0.0, 1.0};
    glm::fvec2 texcoord = {0.0, 0.0};

}USVoxData_t;

typedef struct SurfaceVoxModel_t {
    std::vector<USVoxData_t> voxel;
    int num = 0;
    glm::ivec3 size = {0, 0, 0};

}svoxModel_t;


#endif