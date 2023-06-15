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
std::vector<glm::ivec3> RAWmodel_cls::Voxel_Position(int layer){

    std::vector<glm::ivec3> voxelPosition;

    for(int i = 0; i < voxelModel.num[layer]; i++){
        voxelPosition.push_back(voxelModel.somVoxel[layer][i].locate);
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
    std::cout << infdata.sampleType << std::endl;

    fgets(buffer, sizeof(buffer), file);//voxel-size=XXX:XXX:XXX
    sscanf(buffer, "voxel-size=%f:%f:%f", &infdata.voxelSize[0], &infdata.voxelSize[1], &infdata.voxelSize[2]);
    // std::cout << "voxel-size : "<<infdata.voxelSize[0] << ", " << infdata.voxelSize[1] << ", " << infdata.voxelSize[2] << std::endl;

    fgets(buffer, sizeof(buffer), file);//endian=XXX
    sscanf(buffer, "endian=%s",infdata.endian);
    // std::cout << infdata.endian << std::endl;

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
    rawData = (RawData_t***)malloc(sizeof(RawData_t**) * infdata.resolution[2]);
    for(int i = 0; i < infdata.resolution[2]; i++){
        rawData[i] = (RawData_t**)malloc(sizeof(RawData_t*) * infdata.resolution[1]);
        for(int j = 0; j < infdata.resolution[1]; j++){
            rawData[i][j] = (RawData_t*)malloc(sizeof(RawData_t) * infdata.resolution[0]);
            for(int k = 0; k < infdata.resolution[0]; k++){
                rawData[i][j][k].layer = -1;
                rawData[i][j][k].air = false;
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
    if(infdata.type == 0){
        fread(uc_voxelData, sizeof(BYTE),size, file);
        for(int i = 1; i < infdata.resolution[2]-1; i++){
            for(int j = 1; j < infdata.resolution[1]-1; j++){
                for(int k = 1; k < infdata.resolution[0]-1; k++){
                    int num = k + j*infdata.resolution[0] + i*infdata.resolution[0]* infdata.resolution[1];
                    rawData[i][j][k].layer = (short int)uc_voxelData[num];
                    // cout << (int)uc_voxelData[num] << ", ";
                    if(rawData[i][j][k].layer == voxelModel.somInitLayer){
                        layernum++;
                    }
                }
                // cout << "\n";
            }
            // cout << "\n\n";
        }
        return true;
    }else if(infdata.type == 1){
        fread(f_voxelData, sizeof(float),size, file);
        for(int i = 1; i < infdata.resolution[2]-1; i++){
            for(int j = 1; j < infdata.resolution[1]-1; j++){
                for(int k = 1; k < infdata.resolution[0]-1; k++){
                    int num = k + j*infdata.resolution[0] + i*infdata.resolution[0]* infdata.resolution[1];
                    rawData[i][j][k].layer = (short int)f_voxelData[num];
                    // cout << rawData[i][j][k].layer << ", ";
                    if(rawData[i][j][k].layer == voxelModel.somInitLayer){
                        layernum++;
                    }
                }
                // cout << "\n";
            }

        }
        return true;
    }else if(infdata.type == 2){
        fread(d_voxelData, sizeof(double),size, file);
        for(int i = 1; i < infdata.resolution[2]-1; i++){
            for(int j = 1; j < infdata.resolution[1]-1; j++){
                for(int k = 1; k < infdata.resolution[0]-1; k++){
                    int num = k + j*infdata.resolution[0] + i*infdata.resolution[0]* infdata.resolution[1];
                    rawData[i][j][k].layer = (short int)d_voxelData[num];
                    if(rawData[i][j][k].layer == voxelModel.somInitLayer){
                        layernum++;
                    }
                }
            }
        }
        return true;
    }
    return false;

}

void RAWmodel_cls::SetVoxelData(){

    GiveSpaceLocate();
    if(infdata.resolution[0] > infdata.resolution[1] && infdata.resolution[0] > infdata.resolution[2]){
        for(short int z = 0, x = 1,y = 1; z < infdata.resolution[0]; z++){
            FindOutterLayer(x, y, z);
        }
    }else if(infdata.resolution[1] > infdata.resolution[0] && infdata.resolution[1] > infdata.resolution[2]){
        for(short int x = 0, z = 1,y = 1; x < infdata.resolution[1]; x++){
            FindOutterLayer(x, y, z);
        }
    }else{
        for(short int y = 0, x = 1,z = 1; y < infdata.resolution[2]; y++){
            FindOutterLayer(x, y, z);
        }
    }

    for(int y = 1; y < infdata.resolution[2]-1; y++){
        for(int x = 1; x < infdata.resolution[1]-1; x++){

            for(int z = 1; z < infdata.resolution[0]-1; z++){
                // outer voxel type = 0
                if(rawData[y][x][z].layer == 0){
                    voxelModel.outerVoxel.push_back(USVoxData_t{{x,y,z},{}});
                    findSurfaceVoxel(y, x, z, voxelModel.outerVoxel.size()-1, 0, 0);
                }
                // inner voxel type = 1
                if(rawData[y][x][z].layer == voxelModel.somInitLayer+voxelModel.somChioceLayerNum){
                    voxelModel.innerVoxel.push_back(USVoxData_t{{x,y,z},{}});
                    findSurfaceVoxel(y, x, z, voxelModel.innerVoxel.size()-1, 0, 1);
                }
                // som voxel type = 2
                for(int layern = 0; layern < voxelModel.somChioceLayerNum; layern++){

                    if(rawData[y][x][z].layer == voxelModel.somInitLayer+layern){
                        voxelModel.somVoxel[layern][voxelModel.num[layern]].locate = {x, y, z};
                        setMaxbounder(x, y, z, layern);
                        findSurfaceVoxel(y,x,z, voxelModel.num[layern], layern, 2);
                        voxelModel.num[layern]++;
                    }
                }
            }
        }
    }
}

void RAWmodel_cls::FindOutterLayer(short int x, short int y, short int z){
    // 先用2D 測試
    if(x < 0 || x >= infdata.resolution[1]) return;
    if(y < 0 || y >= infdata.resolution[2]) return;
    if(z < 0 || z >= infdata.resolution[0]) return;

    if(rawData[y][x][z].air || rawData[y][x][z].layer == 0){
        return;
    }

    rawData[y][x][z].air = true;
    if(rawData[y][x][z].layer != -1) rawData[y][x][z].layer *= -1;


    if(infdata.resolution[0] > infdata.resolution[1] && infdata.resolution[0] > infdata.resolution[2]){
        FindOutterLayer(x+1, y, z);
        FindOutterLayer(x-1, y, z);
        FindOutterLayer(x, y+1, z);
        FindOutterLayer(x, y-1, z);
    }else if(infdata.resolution[1] > infdata.resolution[0] && infdata.resolution[1] > infdata.resolution[2]){
        FindOutterLayer(x, y, z+1);
        FindOutterLayer(x, y, z-1);
        FindOutterLayer(x, y+1, z);
        FindOutterLayer(x, y-1, z);
    }else{
        FindOutterLayer(x, y, z+1);
        FindOutterLayer(x, y, z-1);
        FindOutterLayer(x+1, y, z);
        FindOutterLayer(x-1, y, z);
    }

}
void RAWmodel_cls::GiveSpaceLocate(){
    voxelModel.num = (int*)malloc(voxelModel.somChioceLayerNum*sizeof(int));
    voxelModel.maxsize = (glm::ivec3*)malloc(voxelModel.somChioceLayerNum*sizeof(glm::ivec3));
    voxelModel.minsize = (glm::ivec3*)malloc(voxelModel.somChioceLayerNum*sizeof(glm::ivec3));

    voxelModel.somVoxel = (USVoxData_t**)malloc(voxelModel.somChioceLayerNum*sizeof(USVoxData_t*));

    for(int layer = 0; layer < voxelModel.somChioceLayerNum; layer++){
        voxelModel.somVoxel[layer] = (USVoxData_t*)malloc(layernum*sizeof(USVoxData_t));
        voxelModel.num[layer] = 0;
        voxelModel.maxsize[layer] = {0, 0, 0};
        voxelModel.minsize[layer] = {10000, 10000, 10000};
        for(int j = 0; j < layernum; j++){
            voxelModel.somVoxel[layer][j].color = {0.8, 1.0, 0.0};
            voxelModel.somVoxel[layer][j].locate = {0.0, 0.0, 0.0};
            voxelModel.somVoxel[layer][j].texcoord = {0.0, 0.0};
            voxelModel.somVoxel[layer][j].textype = 0;
        }

    }

}
void RAWmodel_cls::setMaxbounder(int i, int j, int k, int layer){
    if(voxelModel.maxsize[layer][0] < i) voxelModel.maxsize[layer][0] = i;
    if(voxelModel.minsize[layer][0] > i) voxelModel.minsize[layer][0] = i;
    if(voxelModel.maxsize[layer][1] < j) voxelModel.maxsize[layer][1] = j;
    if(voxelModel.minsize[layer][1] > j) voxelModel.minsize[layer][1] = j;
    if(voxelModel.maxsize[layer][2] < k) voxelModel.maxsize[layer][2] = k;
    if(voxelModel.minsize[layer][2] > k) voxelModel.minsize[layer][2] = k;
}
void RAWmodel_cls::findSurfaceVoxel(int y, int x, int z, int num, int layer, int voxelType){

    if(z+1 < infdata.resolution[0]){

        if(rawData[y][x][z+1].layer != layer-1){
            if(voxelType == 0){
                voxelModel.outerVoxel[num].faceAir[0] = true;
            }
            if(voxelType == 1){
                voxelModel.innerVoxel[num].faceAir[0] = true;
            }
            if(voxelType == 2){
                voxelModel.somVoxel[layer][num].faceAir[0] = true;
            }
        }

    }
    if(z-1 >= 0){
        if(rawData[y][x][z-1].layer != layer-1){
            if(voxelType == 0){
                voxelModel.outerVoxel[num].faceAir[1] = true;
            }
            if(voxelType == 1){
                voxelModel.innerVoxel[num].faceAir[1] = true;
            }
            if(voxelType == 2){
                voxelModel.somVoxel[layer][num].faceAir[1] = true;
            }
        }
    }
    if(x+1 < infdata.resolution[1]){
        if(rawData[y][x+1][z].layer != layer-1){
            if(voxelType == 0){
                voxelModel.outerVoxel[num].faceAir[2] = true;
            }
            if(voxelType == 1){
                voxelModel.innerVoxel[num].faceAir[2] = true;
            }
            if(voxelType == 2){
                voxelModel.somVoxel[layer][num].faceAir[2] = true;
            }
        }
    }
    if(x-1 >= 0){
        if(rawData[y][x-1][z].layer != layer-1){
            if(voxelType == 0){
                voxelModel.outerVoxel[num].faceAir[3] = true;
            }
            if(voxelType == 1){
                voxelModel.innerVoxel[num].faceAir[3] = true;
            }
            if(voxelType == 2){
                voxelModel.somVoxel[layer][num].faceAir[3] = true;
            }
        }
    }
    if(y+1 < infdata.resolution[2]){
        if(rawData[y+1][x][z].layer != layer-1){
            if(voxelType == 0){
                voxelModel.outerVoxel[num].faceAir[4] = true;
            }
            if(voxelType == 1){
                voxelModel.innerVoxel[num].faceAir[4] = true;
            }
            if(voxelType == 2){
                voxelModel.somVoxel[layer][num].faceAir[4] = true;
            }
        }
    }
    if(y-1 >= 0){
        if(rawData[y-1][x][z].layer != layer-1){
            if(voxelType == 0){
                voxelModel.outerVoxel[num].faceAir[5] = true;
            }
            if(voxelType == 1){
                voxelModel.innerVoxel[num].faceAir[5] = true;
            }
            if(voxelType == 2){
                voxelModel.somVoxel[layer][num].faceAir[5] = true;
            }
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