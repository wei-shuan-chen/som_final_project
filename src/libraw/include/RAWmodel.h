#ifndef RAWMODEL_H
#define RAWMODEL_H

#include <vector>
#include <iostream>
#include <string>
#include <glm/gtc/matrix_transform.hpp>

#include "SurfaceVoxels.h"

using namespace std;
typedef unsigned char  BYTE;

enum voxelType{
    OUTTER,
    INNER,
    SOM,
    PSOM
};

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
    psvoxModel_t pvoxelModel;
    InfData_t infdata;
    RawData_t*** rawData; // 0 air, (255\50) bounder, 100~100+(somChioceLayerNum*10) inside
    int ***newrawData;

    // fun
    void LoadFile(const char* infFileName,const char* rawFileName, const char* o_inf);
    void LoadOutputFile(const char* o_raw);
    bool choice_psomvoxel(glm::mat3x3 m_psomInverse, glm::vec3 v_psomTranslate);
    bool choice_somvoxel(glm::mat3x3 m_psomInverse, float* f_psomTranslate, float* f_scale, bool setBlock);

    std::vector<glm::ivec3> Voxel_Position(int layer, int block);
    std::vector<glm::ivec3> pVoxel_Position();

private:
    // RawData_l* head;
    bool LoadINFfile(const char* infFileName, const char* o_inf);
    bool SetSampleType(const char* type);

    void CreateRawData();

    bool LoadRAWfile(const char*rawFileName);
    bool ReadRawFile(FILE *file);
    void GiveSpaceLocate();

    void SetBlockLocate(const char* orient, int trans, int scale);
    void SetVoxelData();

    int SetBlockNum(const char* orient, int x, int y, int z);
    void findSurfaceVoxel(int z, int y, int x, int num, int layer, int block, int voxelType);

    void checkComputerEndian();
    void setMaxbounder(int i, int j, int k, int layer, int block, int type);

    BYTE* uc_voxelData;
    BYTE* new_uc_voxelData;
    float* f_voxelData;
    float* new_f_voxelData;
    double* d_voxelData;
    double* new_d_voxelData;

    int* layervoxelnum = {0};
    glm::mat3x3 m_transform;
};
extern RAWmodel_cls rawmodel;
#endif