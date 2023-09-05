#ifndef MATH_H
#define MATH_H

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

class math_cls{
public:
    glm::fvec3 crossPruduct(glm::fvec3 a, glm::fvec3 b);
    float innerProduct(glm::fvec3 a, glm::fvec3 b);
    glm::mat3x3 inverseMatrix(glm::mat3x3 A);

};
extern math_cls math;

#endif