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

class carve_cls{
public:
    carve_cls();
    ~carve_cls();

    void voxel_mapping(int layer, int block, MatrixStack texture_m);
private:
    glm::fvec2 findMinDistPrecisePos(const LatData_t* latticeData, double mid, glm::fvec3 voxelPos, glm::ivec3 minLatticeCoord, int de);
    glm::fvec3 outerProjp(glm::fvec3 o, glm::fvec3 a1, glm::fvec3 a2, glm::fvec3 projp, glm::fvec3 p);
    glm::fvec3 pointTotriangle(glm::fvec3 o, glm::fvec3 a1, glm::fvec3 a2, glm::fvec3 projp, glm::fvec3 vector_n);


};
extern carve_cls carve;
#endif