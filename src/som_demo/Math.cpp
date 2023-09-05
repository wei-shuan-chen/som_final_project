#include "Math.h"


math_cls math;
glm::fvec3 math_cls::crossPruduct(glm::fvec3 a, glm::fvec3 b){
    glm::fvec3 c;
    c.x = a.y*b.z - a.z*b.y;
    c.y = -1*(a.x*b.z - a.z*b.x);
    c.z = a.x*b.y - a.y*b.x;

    return c;
}
float math_cls::innerProduct(glm::fvec3 a, glm::fvec3 b){
    return ((a.x*b.x) + (a.y*b.y) + (a.z*b.z));
}
glm::mat3x3 math_cls::inverseMatrix(glm::mat3x3 A){
    float detA = A[0][0]*A[1][1]*A[2][2] + A[1][0]*A[2][1]*A[0][2] + A[2][0]*A[0][1]*A[1][2];
    detA = detA - A[0][2]*A[1][1]*A[2][0] - A[1][2]*A[2][1]*A[0][0] - A[2][2]*A[0][1]*A[1][0];

    // for(int i = 0; i < 3; i++){
    //     for(int j = 0; j < 3; j++){
    //         cout << A[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    // cout << "\n\n";
    glm::mat3x3 newA;
    newA[0][0] = (A[1][1]*A[2][2] - A[1][2]*A[2][1])/detA;
    newA[0][1] = (-1)*(A[0][1]*A[2][2] - A[0][2]*A[2][1])/detA;
    newA[0][2] = (A[0][1]*A[1][2] - A[0][2]*A[1][1])/detA;
    newA[1][0] = (-1)*(A[1][0]*A[2][2] - A[1][2]*A[2][0])/detA;
    newA[1][1] = (A[0][0]*A[2][2] - A[0][2]*A[2][0])/detA;
    newA[1][2] = (-1)*(A[0][0]*A[1][2] - A[0][2]*A[1][0])/detA;
    newA[2][0] = (A[1][0]*A[2][1] - A[1][1]*A[2][0])/detA;
    newA[2][1] = (-1)*(A[0][0]*A[2][1] - A[0][1]*A[2][0])/detA;
    newA[2][2] = (A[0][0]*A[1][1] - A[0][1]*A[1][0])/detA;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(abs(newA[i][j]) < 0.0000001) newA[i][j] = 0;
            // cout << newA[i][j] << " ";
        }
        // cout << "\n";
    }
    // cout << "\n\n";
    return newA;
}