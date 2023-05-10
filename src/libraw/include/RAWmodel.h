#ifndef RAWMODEL_H
#define RAWMODEL_H

#include <vector>
#include <iostream>
#include <string>

#include "SurfaceVoxels.h"

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

class RAWmodel_cls{
public:
    RAWmodel_cls();
    ~RAWmodel_cls();
    // var
    SurfaceVoxModel_t voxelModel;
    InfData_t infdata;

    // fun
    void LoadFile(const char* infFileName,const char* rawFileName);
    std::vector<glm::ivec3> Voxel_Position();



private:
    int*** rawData; // 0 air, 1 bounder, 2 inside
    bool LoadINFfile(const char* infFileName);
    bool SetSampleType(const char* type);

    void CreateRawData();

    bool LoadRAWfile(const char*rawFileName);
    bool ReadRawFile(FILE *file);


    void SetVoxelData();
    void findSurfaceVoxel(int z, int y, int x, int num);

    void checkComputerEndian();
    void setMaxbounder(int i, int j, int k);

    BYTE* uc_voxelData;
    float* f_voxelData;
    double* d_voxelData;

};
extern RAWmodel_cls rawmodel;
#endif