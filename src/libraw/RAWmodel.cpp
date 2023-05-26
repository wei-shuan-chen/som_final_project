#include <stdio.h>
#include <iostream>
#include <assert.h>
#include <string.h>
// #include <GLFW/glfw3.h>
#include <iomanip>
#include "RAWmodel.h"
RAWmodel_cls rawmodel;

RAWmodel_cls::RAWmodel_cls(){

}

RAWmodel_cls::~RAWmodel_cls(){
    // free(bounderVoxelData);
    for(int i = 0; i < infdata.resolution[2]; i++){
        for(int j = 0; j < infdata.resolution[1]; j++){
            free(rawData[i][j]);
        }
    }
    for(int i = 0; i < infdata.resolution[2]; i++){
        free(rawData[i]);
    }
    free(rawData);
}
void RAWmodel_cls::LoadFile(const char* infFileName,const char* rawFileName){
    LoadINFfile(infFileName);
    CreateRawData();
    LoadRAWfile(rawFileName);

}
std::vector<glm::ivec3> RAWmodel_cls::Voxel_Position(){

    std::vector<glm::ivec3> voxelPosition;

    for(int i = 0; i < voxelModel.voxel.size(); i++){
        voxelPosition.push_back(voxelModel.voxel[i].locate);
    }

    return voxelPosition;
}

bool RAWmodel_cls::LoadINFfile(const char* infFileName){
    FILE *file = NULL;
    errno_t err;                    //record error
    file = fopen(infFileName, "r"); // err = 0 success, err != fail
    if(file == NULL){
        std::cout << "Failed to open rawfile" << std::endl;
        return false;
    }


    char buffer[133];
    int lineno = 0; // record line number // total 12 line
    char c[10];
    // start reading
    fgets(buffer, sizeof(buffer), file); // raw-file=XXX.raw
    lineno++;
    fgets(buffer, sizeof(buffer), file);// resolution=XX*XX*XX
    sscanf(buffer, "resolution=%dx%dx%d", &infdata.resolution[0], &infdata.resolution[1], &infdata.resolution[2]);
    std::cout <<  "resolution : "<<infdata.resolution[0] << ", " << infdata.resolution[1] << ", " << infdata.resolution[2] << std::endl;

    fgets(buffer, sizeof(buffer), file);// sample-type=XXXXXX
    sscanf(buffer, "sample-type=%s", c);
    if(SetSampleType(c) == false){
        std::cout << "Failed to set sample type" << std::endl;
        return false;;
    }
    // std::cout << infdata.sampleType << std::endl;

    fgets(buffer, sizeof(buffer), file);//voxel-size=XXX:XXX:XXX
    sscanf(buffer, "voxel-size=%f:%f:%f", &infdata.voxelSize[0], &infdata.voxelSize[1], &infdata.voxelSize[2]);
    // std::cout << "voxel-size : "<<infdata.voxelSize[0] << ", " << infdata.voxelSize[1] << ", " << infdata.voxelSize[2] << std::endl;

    fgets(buffer, sizeof(buffer), file);//endian=XXX
    sscanf(buffer, "endian=%s",infdata.endian);
    // std::cout << infdata.endian << std::endl;

    fgets(buffer, sizeof(buffer), file);//Min=XXX:XXX:XXX
    sscanf(buffer, "Min=%f:%f:%f",&infdata.min[0],&infdata.min[1],&infdata.min[2]);
    std::cout << "min : "<<infdata.min[0] << ", " << infdata.min[1] << ", " << infdata.min[2] << std::endl;

    fgets(buffer, sizeof(buffer), file);//Max=XXX:XXX:XXX
    sscanf(buffer, "Max=%f:%f:%f",&infdata.max[0],&infdata.max[1],&infdata.max[2]);
    std::cout <<"max : "<< infdata.max[0] << ", " << infdata.max[1] << ", " << infdata.max[2] << std::endl;


    if (feof(file))
    {
        std::cout << "End of file reached!" << std::endl;
    }
    else if (ferror(file))
    {
        std::cout << "Encountered an error while reading the file!" << std::endl;
    }

    fclose(file);

    return true;

}

void RAWmodel_cls::CreateRawData(){
    int rawSize = infdata.resolution[0] * infdata.resolution[1] * infdata.resolution[2];
    if(infdata.type == 0){
        uc_voxelData = (BYTE*)malloc(sizeof(BYTE) * rawSize);
    }else if(infdata.type == 1){
        f_voxelData = (float*)malloc(sizeof(float)* rawSize);
    }else if(infdata.type == 2){
        d_voxelData = (double*)malloc(sizeof(double)* rawSize);
    }

    rawData = (int***)malloc(sizeof(int**) * infdata.resolution[2]);
    for(int i = 0; i < infdata.resolution[2]; i++){
        rawData[i] = (int**)malloc(sizeof(int*) * infdata.resolution[1]);
        for(int j = 0; j < infdata.resolution[1]; j++){
            rawData[i][j] = (int*)malloc(sizeof(int) * infdata.resolution[0]);
            for(int k = 0; k < infdata.resolution[0]; k++){
                rawData[i][j][k] = 0;
            }
        }
    }
}

bool RAWmodel_cls::LoadRAWfile(const char* rawFileName){
    FILE *file = NULL;
    errno_t err;                    //record error
    file = fopen(rawFileName, "r"); // err = 0 success, err != fail
    if(file == NULL){
        std::cout << "Failed to open rawfile" << std::endl;
        return false;
    }

    //read raw to 3Darray
    if(!ReadRawFile(file)){
        std::cout << "Failed to read raw file" << std::endl;
    }
    //set 0 air, 1 bounder, 2 inside
    SetVoxelData();

    // error detect
    if (feof(file))
        std::cout << "End of file reached!" << std::endl;
    else if (ferror(file))
        std::cout << "Encountered an error while reading the file!" << std::endl;

    fclose(file);

    return true;
}

bool RAWmodel_cls::ReadRawFile(FILE *file){
    int size = infdata.resolution[0] * infdata.resolution[1] * infdata.resolution[2];
    voxelModel.num = 0;
    if(infdata.type == 0){
        fread(uc_voxelData, sizeof(BYTE),size, file);
        for(int i = 0; i < infdata.resolution[2]; i++){
            for(int j = 0; j < infdata.resolution[1]; j++){
                for(int k = 0; k < infdata.resolution[0]; k++){
                    int num = k + j*infdata.resolution[0] + i*infdata.resolution[0]* infdata.resolution[1];
                    rawData[i][j][k] = uc_voxelData[num];
                    if(rawData[i][j][k] == 255){
                        voxelModel.num++;
                    }
                }
            }
        }
        return true;
    }else if(infdata.type == 1){
        fread(f_voxelData, sizeof(float),size, file);
        for(int i = 0; i < infdata.resolution[2]; i++){
            for(int j = 0; j < infdata.resolution[1]; j++){
                for(int k = 0; k < infdata.resolution[0]; k++){
                    int num = k + j*infdata.resolution[0] + i*infdata.resolution[0]* infdata.resolution[1];
                    rawData[i][j][k] = f_voxelData[num];
                    if(rawData[i][j][k] == 255){
                        voxelModel.num++;
                    }
                }
            }
        }
        return true;
    }else if(infdata.type == 2){
        fread(d_voxelData, sizeof(double),size, file);
        for(int i = 0; i < infdata.resolution[2]; i++){
            for(int j = 0; j < infdata.resolution[1]; j++){
                for(int k = 0; k < infdata.resolution[0]; k++){
                    int num = k + j*infdata.resolution[0] + i*infdata.resolution[0]* infdata.resolution[1];
                    rawData[i][j][k] = d_voxelData[num];
                    if(rawData[i][j][k] == 255){
                        voxelModel.num++;
                    }
                }
            }
        }
        return true;
    }
    return false;

}

void RAWmodel_cls::SetVoxelData(){

    int num = 0;
    for(int y = 0; y < infdata.resolution[2]; y++){
        for(int x = 0; x < infdata.resolution[1]; x++){
            for(int z = 0; z < infdata.resolution[0]; z++){
                if(rawData[y][x][z] == 255){
                    voxelModel.voxel.push_back(USVoxData_t{{x,y,z},{}});
                    setMaxbounder(x, y, z);
                    findSurfaceVoxel(y,x,z, num);
                    num++;
                }
            }
        }
    }
    // std::cout << bounderMaxLocate[0] << ", " << bounderMaxLocate[1] << ", " << bounderMaxLocate[2] << std::endl;
}
void RAWmodel_cls::setMaxbounder(int i, int j, int k){
    if(voxelModel.size[0] < i) voxelModel.size[0] = i;
    if(voxelModel.size[1] < j) voxelModel.size[1] = j;
    if(voxelModel.size[2] < k) voxelModel.size[2] = k;
}
void RAWmodel_cls::findSurfaceVoxel(int y, int x, int z, int num){

    if(z+1 < infdata.resolution[0]){
        if(rawData[y][x][z+1] != 0){
            voxelModel.voxel[num].faceAir[0] = true;
        }
    }
    if(z-1 >= 0){
        if(rawData[y][x][z-1] != 0){
            voxelModel.voxel[num].faceAir[1] = true;
        }
    }
    if(x+1 < infdata.resolution[1]){
        if(rawData[y][x+1][z] != 0){
            voxelModel.voxel[num].faceAir[2] = true;
        }
    }
    if(x-1 >= 0){
        if(rawData[y][x-1][z] != 0){
            voxelModel.voxel[num].faceAir[3] = true;
        }
    }
    if(y+1 < infdata.resolution[2]){
        if(rawData[y+1][x][z] != 0){
            voxelModel.voxel[num].faceAir[4] = true;
        }
    }
    if(y-1 >= 0){
        if(rawData[y-1][x][z] != 0){
            voxelModel.voxel[num].faceAir[5] = true;
        }
    }

}
bool RAWmodel_cls::SetSampleType(const char* type){
    if (!strcmp(type, "unsigned")){
        memset(infdata.sampleType, '\0', sizeof(infdata.sampleType));
		strcat(infdata.sampleType, "unsigned char");
        infdata.type = 0;
        return true;
    }else if(!strcmp(type, "float")){
        memset(infdata.sampleType, '\0', sizeof(infdata.sampleType));
		strcat(infdata.sampleType, "float");
        infdata.type = 1;
        return true;
    }else if(!strcmp(type, "double")){
        memset(infdata.sampleType, '\0', sizeof(infdata.sampleType));
		strcat(infdata.sampleType, "double");
        infdata.type = 2;
        return true;
    }
    return false;
}


void RAWmodel_cls::checkComputerEndian(){
    short int a = 0x1234;
    char *p = (char *)&a;

    printf("p=%#hhx\n",*p);

    if(*p == 0x34)
        printf("Little endian \n");
    else if(*p == 0x12)
        printf("Big endian \n");
    else
        printf("Unknow endian \n");

}