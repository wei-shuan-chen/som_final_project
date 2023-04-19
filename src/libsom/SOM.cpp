#include <cstdlib>
#include <ctime>
#include <iostream>

#include "SOM.h"

LatData latticedata;

glm::fvec3 *dataset;
int dataExtraPoint[4];
int datasteNum = 0;
const double fix_learning_rate = latticedata.learning_rate;
const double fix_radius = latticedata.neighbor;

glm::fvec3 ***createMap(int map_width, int map_height, int *max);
glm::fvec3 *createInputDataset(std::vector<glm::ivec3> bounderVoxelData, int bounderNum);
glm::ivec3 computNeiborhood(glm::ivec3 node, glm::ivec3 bmu);
glm::ivec3 computeHalfballDist(glm::ivec3 p0);
const glm::fvec3 getInput(glm::fvec3 *dataset, int datasteNum);
void destroy(glm::fvec3 ***arr, int width, int height);
void destroyDataset(glm::fvec3 *arr, int datasteNum);
void updateNode(glm::fvec3 ***lattice, glm::fvec3 nowInput, glm::ivec3 nodeId, double radius, double learning_rate);
double computerate(int iter, double fun);
double computeradius(int iter, double fun);
double computeScale(double sigma, double dist);
bool isInNeighborhood(double squaredDist, double radius);

void SOM_Create(std::vector<glm::ivec3> bounderVoxelData, int bounderNum, int *max)
{
    srand(time(NULL));

    // 1. Create input dataset
    dataset = createInputDataset(bounderVoxelData, bounderNum);
    // 2. Create lattice
    latticedata.lattice = createMap(latticedata.map_width, latticedata.map_height, max);
    datasteNum = bounderNum;
}

void SOM_IterateOnce()
{
    // 1. Get one input from the dataset
    // 2. Find BMU
    // 3. Update BMU and the neighbors
    latticedata.learning_rate = computerate(latticedata.iter, fix_learning_rate);
    latticedata.neighbor = computeradius(latticedata.iter, fix_radius);
    const glm::fvec3 nowInput = getInput(dataset, datasteNum);
    double minDist = -1.0;

    int shapeNum = 1;
    if (latticedata.shapeLattice == 4)
        shapeNum = 5;

    glm::ivec3 bmu;
    // compute winner point
    for (int k = 0; k < shapeNum; k++)
    {
        for (int i = 0; i < latticedata.map_height; i++)
        {
            for (int j = 0; j < latticedata.map_width; j++)
            {
                double tmp1 = 0.0;
                float dx = (latticedata.lattice[k][i][j].x - nowInput.x);
                float dy = (latticedata.lattice[k][i][j].y - nowInput.y);
                float dz = (latticedata.lattice[k][i][j].z - nowInput.z);
                tmp1 = dx * dx + dy * dy + dz * dz;
                if (minDist < 0.0)
                {
                    minDist = tmp1;
                    continue;
                }

                if (minDist > tmp1)
                {
                    minDist = tmp1;
                    bmu = {j, i, k};
                }
            }
        }
    }
    // cout << "bmu -> k, (x, y) : "<< bmu.z <<", " << bmu.x<<", " << bmu.y << endl;
    // renew winner point and neighnorhood
    for (int k = 0; k < shapeNum; k++)
    {
        for (int i = 0; i < latticedata.map_height; i++)
        {
            for (int j = 0; j < latticedata.map_width; j++)
            {
                glm::ivec3 node = glm::ivec3(j, i, k);
                glm::ivec3 diff = computNeiborhood(node, bmu); // node - bmu;
                double squaredDist = static_cast<double>(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);
                // std::cout << "Dist " <<squaredDist<<std::endl;
                if((k == 0 && i == 4 && j == 0)||(k == 4 && j == latticedata.map_height - 1 && i ==  latticedata.map_width - 4)){
                    // cout << "node -> k, (x, y) : "<< node.z <<", " << node.x<<", " << node.y << endl;
                    // cout << "diff : " << diff.x << ", "<<diff.y << "\n\n";
                }
                if (isInNeighborhood(squaredDist, latticedata.neighbor))
                {
                    double n_radius = computeScale(latticedata.neighbor, squaredDist);
                    updateNode(latticedata.lattice, nowInput, node, n_radius, latticedata.learning_rate);
                }
            }
        }
    }
    latticedata.iter++;
    // cout << iter <<endl;
}

void SOM_Destroy()
{
    // 1. Destroy lattice
    destroy(latticedata.lattice, latticedata.map_width, latticedata.map_height);
    // 2. Destroy input dataset
    destroyDataset(dataset, datasteNum);
}
void SOM_Again()
{
    // destroy(lattice, map_width, map_height);

    // is_som_finished = false;
    // map_width;
    // map_height;
    // datasteNum = 0;
    // iter = 0;
    // learning_rate = 0.1;
    // radius = 5;
    // learning_rate = 0.1;
    // neighbor = 5;
    // lattice = createMap(map_width, map_height, max_lattice_range);
}
LatData *Lattice_Struct_Use()
{
    return &latticedata;
}
glm::fvec3 *createInputDataset(std::vector<glm::ivec3> bounderVoxelData, int bounderNum)
{
    glm::fvec3 *dataset = (glm::fvec3 *)malloc(sizeof(glm::fvec3) * bounderNum);

    glm::fvec3 maxPos, minPos, leftPos, rightPos, topPos, bottomPos;
    maxPos = minPos = leftPos = rightPos = topPos = bottomPos = {0.0, 0.0, 0.0};
    for (int i = 0; i < bounderNum; i++)
    {
        dataset[i] = bounderVoxelData[i];
        // find extra data point
        // if()

    }


    return dataset;
}
glm::fvec3 ***createMap(int map_width, int map_height, int *max)
{
    double val = PI / 180;

    glm::fvec3 ***lattice = (glm::fvec3 ***)malloc(sizeof(glm::fvec3 **) * 5);
    for (int j = 0; j < 5; j++)
    {
        lattice[j] = (glm::fvec3 **)malloc(sizeof(glm::fvec3 *) * map_height);
        for (int i = 0; i < map_height; i++)
        {
            lattice[j][i] = (glm::fvec3 *)malloc(sizeof(glm::fvec3) * map_width);
        }
    }
    switch (latticedata.shapeLattice)
    {
    case 0: // random cylinder
        for (int i = 0; i < map_height; i++)
        {
            for (int j = 0; j < map_width; j++)
            {
                double i0, j0, k0;

                i0 = (rand() % abs(max[0] - 1)) * (-1);
                j0 = rand() % max[1];
                k0 = rand() % max[2];
                // std::cout << i0 << ", " << max[0]<<std::endl;
                lattice[0][i][j] = {i0, j0, k0};
            }
        }
        break;
    case 1: // cylinder

        for (int i = 0; i < map_height; i++)
        {
            double theta = 360.0 / (double)(map_height - 1);
            for (int j = 0; j < map_width; j++)
            {
                double i0, j0, k0;

                i0 = (max[0] / 2) * cos(i * theta * val) + (max[0] / 2);
                j0 = (max[1] / map_width) * j;
                k0 = (max[2] / 2) * sin(i * theta * val) + (max[2] / 2);
                // std::cout << i0 << ", " << max[0]<<std::endl;
                lattice[0][i][j] = {i0, j0, k0};
            }
        }
        break;
    case 2: // random flat
        for (int i = 0; i < map_height; i++)
        {
            for (int j = 0; j < map_width; j++)
            {
                double i0, j0, k0;

                i0 = (rand() % abs(max[0] - 1)) * (-1);
                j0 = rand() % max[1];
                k0 = rand() % max[2];
                // std::cout << i0 << ", " << max[0]<<std::endl;
                lattice[0][i][j] = {i0, j0, k0};
            }
        }
        break;
    case 3: // flat
    {       // We need curly brackets because there are variable declarations
        double ratio_x = (double)max[0] / (double)(map_height - 1);
        double ratio_z = (double)max[2] / (double)(map_width - 1);
        for (int i = 0; i < map_height; i++)
        {
            for (int j = 0; j < map_width; j++)
            {
                double i0, j0, k0;

                i0 = j * ratio_x;
                j0 = max[1];
                k0 = i * ratio_z;

                lattice[0][i][j] = {i0, j0, k0};
            }
        }
    }
    break;
    case 4: // half ball (only square)
        //   1          back
        // 2 0 4   left  top  right
        //   3          front
        { // We need curly brackets because there are variable declarations
            double ratio_x = (double)max[0] / (double)(map_height - 1);
            double ratio_y = (double)max[1] / (double)(map_height - 1);
            double ratio_z = (double)max[2] / (double)(map_height - 1);
            double i0, j0, k0;
            for (int i = 0; i < map_height; i++)
            {
                for (int j = 0; j < map_width; j++)
                {
                    // 0 x-z plane
                    i0 = (map_width - 1 - j) * ratio_x;
                    j0 = max[1];
                    k0 = i * ratio_z;
                    lattice[0][i][j] = {i0, j0, k0};

                    // 1 x-y plane
                    i0 = (map_width - 1 - j) * ratio_x;
                    j0 = i * ratio_y;
                    k0 = 0;
                    lattice[1][i][j] = {i0, j0, k0};

                    // 2 y-z plane
                    i0 = max[0];
                    j0 = j * ratio_y;
                    k0 = i * ratio_z;
                    lattice[2][i][j] = {i0, j0, k0};

                    // 3 y-z plane
                    i0 = (map_width - 1 - j) * ratio_x;
                    j0 = i * ratio_y;
                    k0 = max[2];
                    lattice[3][i][j] = {i0, j0, k0};

                    // 4 x-y plane
                    i0 = 0;
                    j0 = j * ratio_y;
                    k0 = i * ratio_z;
                    lattice[4][i][j] = {i0, j0, k0};
                }
            }
        }
        break;
    case 5:
        {

            float R = (max[2] + max[1]) / 4;
            float r = R / 5.0;
            double rad = 360.0/(double)(map_width-1);
            for (int i = 0; i < map_width; i++)
            {
                for (int j = 0; j < map_height; j++)
                {
                    double fi = (double)i*rad *PI/180.0;
                    double theta = (double)j*rad *PI/180.0;

                    double i0 = r * cos(theta)-0.2 + max[0]/2;
                    double j0 =  cos(fi)* ( R + r*sin(theta)) + max[1]/2;
                    double k0 = sin(fi)* ( R + r*sin(theta)) + max[2]/2;
                    lattice[0][i][j] = {i0, j0, k0};
                }
            }
        }
        break;
    default:
        cout << "error initLattic num" << endl;
        break;
    }

    return lattice;
}
glm::ivec3 computNeiborhood(glm::ivec3 node, glm::ivec3 bmu)
{

    glm::ivec3 diff = {0, 0, 0};

    if (latticedata.shapeLattice == 0 || latticedata.shapeLattice == 1)
    { // cylinder
        int half = (latticedata.map_width - 1) / 2;
        if (bmu.y <= half)
        {
            if (node.y >= half + bmu.y)
                diff.y = bmu.y + ((latticedata.map_width - 1) - node.y);
            else
                diff.y = node.y - bmu.y;
        }
        else if (bmu.y > half)
        {
            if (node.y >= bmu.y - half)
                diff.y = bmu.y - node.y;
            else
                diff.y = node.y + ((latticedata.map_width - 1) - bmu.y);
        }
        diff.x = node.x - bmu.x;
    }
    else if (latticedata.shapeLattice == 2 || latticedata.shapeLattice == 3)
    { // plane
        diff = node - bmu;
    }
    else if (latticedata.shapeLattice == 4)
    { // half ball
        //   1          back
        // 2 0 4   left  top  right
        //   3          front
        diff = computeHalfballDist(node)-computeHalfballDist(bmu);
    }
    else if(latticedata.shapeLattice == 5){
        int half = (latticedata.map_width-1)/2;
        if(bmu.x <= half){
            if(node.x >= half+bmu.x){
                diff.x = bmu.x+((latticedata.map_width-1) - node.x); 
            }else{
                diff.x = node.x - bmu.x;
            }
        }else if(bmu.x > half){
            if(node.x >= bmu.x - half){
                diff.x = bmu.x - node.x;
            }else{
                diff.x = node.x + ((latticedata.map_width-1) - bmu.x);
            }
        }

        half = (latticedata.map_height-1)/2;
        if(bmu.y <= half){
            if(node.y >= half+bmu.y){
                diff.y = bmu.y+((latticedata.map_height-1) - node.y); 
            }else{
                diff.y = node.y - bmu.y;
            }
        }else if(bmu.y > half){
            if(node.y >= bmu.y - half){
                diff.y = bmu.y - node.y;
            }else{
                diff.y = node.y + ((latticedata.map_height-1) - bmu.y);
            }
        }
    }
    return diff;
}
glm::ivec3 computeHalfballDist(glm::ivec3 p0){

    glm::ivec3 a = {0, 0, 0};
    int w = latticedata.map_width - 1;
    if(p0.z == 0) a = {p0.x, w, p0.y};
    else if(p0.z == 1) a = {p0.x, p0.y, 0};
    else if(p0.z == 2) a = {0, p0.x, p0.y};
    else if(p0.z == 3) a = {p0.x, p0.y, w};
    else if(p0.z == 4) a = {w, p0.x, p0.y};
 
    return a;
}
void destroy(glm::fvec3 ***arr, int width, int height)
{

    for (int j = 0; j < 5; j++)
    {

        for (int i = 0; i < height; i++)
        {
            free(arr[j][i]);
        }
        free(arr[j]);
    }
}
void destroyDataset(glm::fvec3 *arr, int datasteNum)
{
    free(arr);
}
double computeradius(int iter, double fun)
{
    double lamda = ((double)(latticedata.max_iter)) / log(fun);
    double sigma = fun * exp(-1 * ((double)iter) / lamda);

    return sigma;
}
double computerate(int iter, double fun)
{
    double sigma = fun * exp(-1 * ((double)iter) / ((double)(latticedata.max_iter)));
    return sigma;
}

const glm::fvec3 getInput(glm::fvec3 *dataset, int datasteNum)
{
    int num, i;
    num = (datasteNum / RAND_MAX) + 1;
    i = (rand() * num) % datasteNum + rand() % num;
    while (i >= datasteNum)
    {
        i = (rand() * num) % datasteNum + rand() % num;
    }

    return dataset[i];
}

bool isInNeighborhood(double squaredDist, double radius)
{
    if (squaredDist <= (radius * radius))
    {
        // std::cout << "dist : " << squaredDist << " radius : " << radius*radius << std::endl;
        return true;
    }
    return false;
}

double computeScale(double sigma, double dist)
{
    double theta = exp((-1 * dist) / (2 * pow(sigma, 2)));

    return theta;
}

void updateNode(glm::fvec3 ***lattice, glm::fvec3 nowInput, glm::ivec3 nodeId, double radius, double learning_rate)
{
    lattice[nodeId.z][nodeId.y][nodeId.x].x = lattice[nodeId.z][nodeId.y][nodeId.x].x + radius * learning_rate * (nowInput.x - lattice[nodeId.z][nodeId.y][nodeId.x].x);
    lattice[nodeId.z][nodeId.y][nodeId.x].y = lattice[nodeId.z][nodeId.y][nodeId.x].y + radius * learning_rate * (nowInput.y - lattice[nodeId.z][nodeId.y][nodeId.x].y);
    lattice[nodeId.z][nodeId.y][nodeId.x].z = lattice[nodeId.z][nodeId.y][nodeId.x].z + radius * learning_rate * (nowInput.z - lattice[nodeId.z][nodeId.y][nodeId.x].z);
}