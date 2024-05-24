#ifndef CARVE_H
#define CARVE_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <thread>
#include <vector>

#include "SOM.h"
#include "RAWmodel.h"
#include "textureMap.h"
#include "Math.h"
enum texFilter{
    MINIFICATION,
    MAGNIFICATON
};
enum filter{
    LINEAR,
    NEAREST
};

class carve_cls{
public:
    carve_cls();
    ~carve_cls();
    bool latticeTextureFilter = LINEAR;
    bool latticeVoxelFilter = LINEAR;
    bool pcarve = true;
    void voxel_mapping(int layer, int block);
    void pvoxel_mapping();
    glm::fvec3 latticeCoord_to_textureCoord_2D(glm::fvec2 latticeCoord, const LatData_t* latticeData);
private:
    void unit_voxel_mapping(int n, int layer, int block);
    glm::ivec3 find_min_dist_pos(const LatData_t* latticeData, double v_x, double v_y, double v_z, double* minDist);
    glm::fvec2 surround_Triangles(const LatData_t* latticeData, double mid, glm::fvec3 voxelPos, glm::ivec3 minLatticeCoord);
    glm::fvec3 point_to_triangle(glm::fvec3 o, glm::fvec3 a1, glm::fvec3 a2, glm::fvec3 p, double* minDist);
    glm::fvec3 outer_projp(glm::fvec3 o, glm::fvec3 a1, glm::fvec3 a2, glm::fvec3 projp, glm::fvec3 p);
    glm::fvec3 barycentric_coord(glm::fvec3 o, glm::fvec3 a1, glm::fvec3 a2, glm::fvec3 projp, glm::fvec3 vector_n);
    glm::fvec3 mag_filter(glm::fvec2 imageRate1, int texType );
    glm::fvec3 min_filter(glm::ivec2 imageRate0, glm::ivec2 imageRate2, int texType);

    glm::fvec3 outer_tetrahedron(glm::fvec3 o, glm::fvec3 o_index, glm::fvec3 a0, glm::fvec3 a0_index, glm::fvec3 a1, glm::fvec3 a1_index, glm::fvec3 a2, glm::fvec3 a2_index, glm::fvec3 p, double* minDist);
    glm::fvec3 latticeCoord_to_textureCoord_3D(glm::fvec3 latticeCoord, const LatData_t* latticeData);
    glm::fvec3 surround_Tetrahedron(const LatData_t* latticeData, double mid, glm::fvec3 voxelPos, glm::ivec3 minLatticeCoord);

    int texfilter = MINIFICATION;

    // glm::fvec3 tetrahedronOnTriangle();
};
extern carve_cls carve;
#endif