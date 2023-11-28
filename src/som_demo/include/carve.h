#ifndef CARVE_H
#define CARVE_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "SOM.h"
#include "RAWmodel.h"
#include "textureMap.h"
#include "Math.h"
enum texFilter{
    MINIFICATION,
    MAGNIFICATON
};
class carve_cls{
public:
    carve_cls();
    ~carve_cls();
    bool filter = false;
    bool pcarve = true;
    void voxel_mapping(int layer, int block);
    void pvoxel_mapping();
private:
    glm::ivec3 findMinDistPos(const LatData_t* latticeData, double v_x, double v_y, double v_z, double* minDist);
    glm::fvec2 surround8Triangles(const LatData_t* latticeData, double mid, glm::fvec3 voxelPos, glm::ivec3 minLatticeCoord);
    glm::fvec3 surround32Tetrahedron(const LatData_t* latticeData, double mid, glm::fvec3 voxelPos, glm::ivec3 minLatticeCoord);
    glm::fvec3 pointToTriangle(glm::fvec3 o, glm::fvec3 a1, glm::fvec3 a2, glm::fvec3 p, double* minDist);
    glm::fvec3 outerProjp(glm::fvec3 o, glm::fvec3 a1, glm::fvec3 a2, glm::fvec3 projp, glm::fvec3 p);
    glm::fvec3 barycentricTriCoord(glm::fvec3 o, glm::fvec3 a1, glm::fvec3 a2, glm::fvec3 projp, glm::fvec3 vector_n);
    glm::fvec3 outerTetrahedron(glm::fvec3 o, glm::fvec3 o_index, glm::fvec3 a0, glm::fvec3 a0_index, glm::fvec3 a1, glm::fvec3 a1_index, glm::fvec3 a2, glm::fvec3 a2_index, glm::fvec3 p, double* minDist);
    glm::fvec3 magFilter(glm::fvec2 imageRate1, int texType );
    glm::fvec3 minFilter(glm::ivec2 imageRate0, glm::ivec2 imageRate2, int texType);


    // glm::fvec3 tetrahedronOnTriangle();
};
extern carve_cls carve;
#endif