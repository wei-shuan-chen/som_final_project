#ifndef RAWMODEL_H
#define RAWMODEL_H

#include <vector>
#include <iostream>
#include <string>

#include "BoundingVoxels.h"
using namespace std;
typedef unsigned char  BYTE;

typedef struct InfData_t {
	int resolution[3];//inf size
	char sampleType[15];
	float voxelSize[3];
	char endian[10];
	float min[3];
	float max[3];
    int type; // 0 unsigned char, 1 float, 2 double
}InfData_t;

class RAWmodel{
public:
    RAWmodel();
    ~RAWmodel();
    void LoadFile(const char* infFileName,const char* rawFileName);
    std::vector<glm::ivec3> Voxel_Position();

    InfData_t infdata;
    std::vector<VoxData_b> bounderVoxelData;
    int bounderMaxLocate[3] = {0, 0, 0};
    int*** voxelData; // 0 air, 1 bounder, 2 inside
    int bounderNum;

private:
    bool LoadINFfile(const char* infFileName);
    void CreateVoxel();
    bool LoadRAWfile(const char*rawFileName);
    bool SetSampleType(const char* type);
    bool ReadRawFile(FILE *file);
    void SetVoxelData();
    void CreateBounderVoxelLocate();
    void SetbounderVoxelFaceAir(int i, int j, int k, int num);
    void checkComputerEndian();
    void setMaxbounder(int i, int j, int k);

    BYTE* uc_voxelData;
    float* f_voxelData;
    double* d_voxelData;

};

#endif