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
float math_cls::determinant2(glm::mat2x2 A){
    return A[0][0]*A[1][1] - A[0][1]*A[1][0];
}
float math_cls::determinant3(glm::mat3x3 A){
    float detA = A[0][0]*A[1][1]*A[2][2] + A[1][0]*A[2][1]*A[0][2] + A[2][0]*A[0][1]*A[1][2];
    detA = detA - A[0][2]*A[1][1]*A[2][0] - A[1][2]*A[2][1]*A[0][0] - A[2][2]*A[0][1]*A[1][0];
    return detA;
}
glm::mat2x2 math_cls::inverseMatrix2(glm::mat2x2 A){
    float detA = determinant2(A);

    glm::mat2x2 newA;
    newA[0][0] = A[1][1]/detA;
    newA[0][1] = (-1)*A[1][0]/detA;
    newA[1][0] = (-1)*A[0][1]/detA;
    newA[1][1] = A[0][0]/detA;

    return newA;
}
glm::mat3x3 math_cls::inverseMatrix3(glm::mat3x3 A){
    float detA = determinant3(A);

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
void math_cls::simpleFraction(int* up, int* down){
    int max;
    for (int i = 1; *up >= i && *down >= i; i++)
    {
        if (*up % i == 0 && *down % i == 0)
        {
            max = i;
        }
    }
    *up = (*up)/max;
    *down = (*down)/max;
}