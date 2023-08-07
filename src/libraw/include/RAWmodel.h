#ifndef RAWMODEL_H
#define RAWMODEL_H

#include <vector>
#include <iostream>
#include <string>

#include "SurfaceVoxels.h"

using namespace std;
typedef unsigned char  BYTE;

typedef struct InfData_t {
	glm::ivec3 resolution;//inf size
	char sampleType[15];
	float voxelSize[3];
	char endian[10];
	// float min[3];
	// float max[3];
    int type; // 0 unsigned char, 1 float, 2 double
}InfData_t;

// typedef struct RawData_l
// {
//     short int layer;
//     bool air = false;
//     RawData_l *p_x;
//     RawData_l *n_x;
//     RawData_l *p_y;
//     RawData_l *n_y;
//     RawData_l *p_z;
//     RawData_l *n_z;
// }RawData_l;

// typedef struct RawDataY_l
// {
//     short int y;
//     RawData_l *p_y;
//     RawData_l *n_y;
// }RawDataY_l;

typedef struct RawData_t
{
    short int layer;
    bool air;
}RawData_t;


class RAWmodel_cls{
public:
    RAWmodel_cls();
    ~RAWmodel_cls();
    // var
    svoxModel_t voxelModel;
    InfData_t infdata;
    RawData_t*** rawData; // 0 air, (255\50) bounder, 100~100+(somChioceLayerNum*10) inside

    // fun
    void LoadFile(const char* infFileName,const char* rawFileName);
    void Voxel_block_set();
    std::vector<glm::ivec3> Voxel_Position(int layer, int block);

private:
    // RawData_l* head;
    bool LoadINFfile(const char* infFileName);
    bool SetSampleType(const char* type);

    void CreateRawData();

    bool LoadRAWfile(const char*rawFileName);
    bool ReadRawFile(FILE *file);
    void GiveSpaceLocate();
    void FindOutterLayer(short int x, short int y, short int z);

    void SetInitBlockLocate(const char* orient);
    void SetVoxelData();
    int SetBlockNum(const char* orient, int x, int y, int z);
    void findSurfaceVoxel(int z, int y, int x, int num, int layer, int block, int voxelType);

    void checkComputerEndian();
    void setMaxbounder(int i, int j, int k, int layer, int block);

    BYTE* uc_voxelData;
    float* f_voxelData;
    double* d_voxelData;

    int* layervoxelnum = {0};

};
extern RAWmodel_cls rawmodel;
#endif