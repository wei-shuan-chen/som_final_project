#ifndef BOUNDINGVOXELS_H
#define BOUNDINGVOXELS_H
#include <glm/glm.hpp>


typedef struct VoxData_b {
    
    glm::ivec3 bounderVoxelLocate = {0,0,0}; // only bounder voxel's locate(x,y,z)
    int bounderVoxelFaceAir[6] = {0}; // 0 face air, 1 face inside 
    int show = 1;
    glm::fvec3 bounderVoxelColor = {1.0, 0.0, 0.0};

}VoxData_b;

 

#endif