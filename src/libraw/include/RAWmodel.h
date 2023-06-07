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
	// float min[3];
	// float max[3];
    int type; // 0 unsigned char, 1 float, 2 double
}InfData_t;

typedef struct RawData_l
{
    short int layer;
    short int x,y,z;
    bool air = false;
    RawData_l *p_x;
    RawData_l *n_x;
    RawData_l *p_y;
    RawData_l *n_y;
    RawData_l *p_z;
    RawData_l *n_z;
}RawData_l;

typedef struct RawDataY_l
{
    short int y;
    RawData_l *p_y;
    RawData_l *n_y;
}RawDataY_l;



class RAWmodel_cls{
public:
    RAWmodel_cls();
    ~RAWmodel_cls();
    // var
    SurfaceVoxModel_t voxelModel;
    InfData_t infdata;

    // fun
    void LoadFile(const char* infFileName,const char* rawFileName);
    std::vector<glm::ivec3> Voxel_Position(int layer);

private:
    int*** rawData; // 0 air, 1 bounder, 2 inside
    RawData_l* head;
    bool LoadINFfile(const char* infFileName);
    bool SetSampleType(const char* type);

    void CreateRawData();

    bool LoadRAWfile(const char*rawFileName);
    bool ReadRawFile(FILE *file);
    void GiveSpaceLocate();
    void initLinkList();
    void FindOutterLayer(RawData_l* node);

    void SetVoxelData();
    void findSurfaceVoxel(int z, int y, int x, int num, int layer, int voxelType);

    void checkComputerEndian();
    void setMaxbounder(int i, int j, int k, int layer);

    BYTE* uc_voxelData;
    float* f_voxelData;
    double* d_voxelData;

    int layernum = 0;

};
extern RAWmodel_cls rawmodel;
#endif