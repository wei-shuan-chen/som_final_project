#include <cstdlib>
#include <ctime>
#include <iostream>

#include "SOM.h"
som_cls som;

som_cls::som_cls(){}

som_cls::~som_cls(){
    // 1. Destroy lattice
    destroy(latticeData.lattice, latticeData.width, latticeData.height);
    // 2. Destroy input dataset
    destroyDataset(inputData.input, inputData.num);
}


void som_cls::SOM_Create(std::vector<glm::ivec3> voxelPos, int voxelNum, glm::ivec3 size)
{
    srand(time(NULL));
    // 1. Create input dataset
    inputData.input = createInputDataset(voxelPos, voxelNum);
    // 2. Create lattice
    latticeData.lattice = createLatticeData(latticeData.width, latticeData.height, size);
    inputData.num = voxelNum;
}

void som_cls::SOM_IterateOnce()
{
    // 1. Get one input from the dataset
    // 2. Find BMU
    // 3. Update BMU and the radius
    latticeData.learningRate = computerate(latticeData.iter, latticeData.initLearningRate);
    latticeData.radius = computeradius(latticeData.iter, latticeData.initRadius);
    const glm::fvec3 nowInput = getInput(inputData.input, inputData.num);
    double minDist = -1.0;

    int shapeNum = 1;
    if (latticeData.type == BALL)
        shapeNum = 5;

    glm::ivec3 bmu;
    // compute winner point
    for (int k = 0; k < shapeNum; k++)
    {
        for (int i = 0; i < latticeData.height; i++)
        {
            for (int j = 0; j < latticeData.width; j++)
            {
                double tmp1 = 0.0;
                float dx = (latticeData.lattice[k][i][j].x - nowInput.x);
                float dy = (latticeData.lattice[k][i][j].y - nowInput.y);
                float dz = (latticeData.lattice[k][i][j].z - nowInput.z);
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
        for (int i = 0; i < latticeData.height; i++)
        {
            for (int j = 0; j < latticeData.width; j++)
            {
                glm::ivec3 node = glm::ivec3(j, i, k);
                glm::ivec3 diff = computNeiborhood(node, bmu); // node - bmu;
                double squaredDist = static_cast<double>(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);
                // std::cout << "Dist " <<squaredDist<<std::endl;
                if((k == 0 && i == 4 && j == 0)||(k == 4 && j == latticeData.height - 1 && i ==  latticeData.width - 4)){
                    // cout << "node -> k, (x, y) : "<< node.z <<", " << node.x<<", " << node.y << endl;
                    // cout << "diff : " << diff.x << ", "<<diff.y << "\n\n";
                }
                if (isInradiushood(squaredDist, latticeData.radius))
                {
                    double n_radius = computeScale(latticeData.radius, squaredDist);
                    updateNode(latticeData.lattice, nowInput, node, n_radius, latticeData.learningRate);
                }
            }
        }
    }
    latticeData.iter++;
    // cout << iter <<endl;
}


void som_cls::SOM_Again()
{
    // destroy(lattice, width, height);

    // is_som_finished = false;
    // width;
    // height;
    // datasteNum = 0;
    // iter = 0;
    // learningRate = 0.1;
    // radius = 5;
    // learningRate = 0.1;
    // radius = 5;
    // lattice = createLatticeData(width, height, max_lattice_range);
}
LatData_t * som_cls::Lattice_get()
{
    return &latticeData;
}
glm::fvec3 * som_cls::createInputDataset(std::vector<glm::ivec3> voxelPos, int voxelNum)
{
    glm::fvec3 *dataset = (glm::fvec3 *)malloc(sizeof(glm::fvec3) * voxelNum);

    for (int i = 0; i < voxelNum; i++)
        dataset[i] = voxelPos[i];

    return dataset;
}
glm::fvec3 *** som_cls::createLatticeData(int width, int height, glm::ivec3 size)
{

    glm::fvec3 ***lattice = (glm::fvec3 ***)malloc(sizeof(glm::fvec3 **) * 5);
    for (int j = 0; j < 5; j++)
    {
        lattice[j] = (glm::fvec3 **)malloc(sizeof(glm::fvec3 *) * height);
        for (int i = 0; i < height; i++)
        {
            lattice[j][i] = (glm::fvec3 *)malloc(sizeof(glm::fvec3) * width);
        }
    }
    if(latticeData.type == PLANE){
        for (int h = 0; h < height; h++)
        {
            for (int w = 0; w < width; w++)
            {
                double i0, j0, k0;
                double ratio_w = (double)w / (double)(width - 1);
                double ratio_h = (double)h / (double)(height - 1);

                i0 = (double)size[0] * ratio_w;
                j0 = size[1];
                k0 = (double)size[2] * ratio_h;

                lattice[0][h][w] = {i0, j0, k0};
            }
        }
    }else if(latticeData.type == CYLINDER){
        for (int h = 0; h < height; h++)
        {
            double theta = 360.0 / (double)(height - 1);
            for (int w = 0; w < width; w++)
            {
                double i0, j0, k0;

                double ratio_w = (double)w / (double)(width - 1);
                double ratio_h = (double)h / (double)(height - 1);

                i0 = ((double)size[0] / 2.0) * cos(2 * PI * ratio_w) + (size[0] / 2);
                j0 = ratio_h * (double)size[1];
                k0 = ((double)size[2] / 2.0) * sin(2 * PI * ratio_w) + (size[2] / 2);
                // std::cout << i0 << ", " << size[0]<<std::endl;
                lattice[0][h][w] = {i0, j0, k0};
            }
        }
    }else if(latticeData.type == DONUT){
        float R = (size[2] + size[1]) / 4;
        float r = R / 5.0;
        for (int h = 0; h < height; h++)
        {
            for (int w = 0; w < width; w++)
            {
                double fi =  2 * PI * (double)w / (double)(width - 1);
                double theta =  2 * PI * (double)h / (double)(height - 1);

                double i0 = r * cos(theta) + ((double)size[0] / 2.0);
                double j0 =  cos(fi)* ( R + r*sin(theta)) + ((double)size[1] / 2.0);
                double k0 = sin(fi)* ( R + r*sin(theta)) + ((double)size[2] / 2.0);
                lattice[0][h][w] = {i0, j0, k0};
            }
        }
    }
    else if(latticeData.type == BALL){
        //   1          back
        // 2 0 4   left  top  right
        //   3          front
        // We need curly brackets because there are variable declarations

        double i0, j0, k0;
        for (int h = 0; h < height; h++)
        {
            for (int w = 0; w < width; w++)
            {
                double ratio_w = (double)w / (double)(width - 1);
                double ratio_h = (double)h / (double)(height - 1);
                // 0 x-z plane
                i0 = size[0] * ratio_w;
                j0 = size[1];
                k0 = size[2] * ratio_h;
                lattice[0][h][w] = {i0, j0, k0};

                // 1 x-y plane
                i0 = size[0] * ratio_w;
                j0 = size[1] * ratio_h;
                k0 = 0;
                lattice[1][h][w] = {i0, j0, k0};

                // 2 y-z plane
                i0 = size[0];
                j0 = size[1] * ratio_w;
                k0 = size[2] * ratio_h;
                lattice[2][h][w] = {i0, j0, k0};

                // 3 x-y plane
                i0 = size[0] * ratio_w;
                j0 = size[1] * ratio_h;
                k0 = size[2];
                lattice[3][h][w] = {i0, j0, k0};

                // 4 y-z plane
                i0 = 0;
                j0 = size[1] * ratio_w;
                k0 = size[2] * ratio_h;
                lattice[4][h][w] = {i0, j0, k0};
            }
        }
    }

    return lattice;
}
glm::ivec3 som_cls::computNeiborhood(glm::ivec3 node, glm::ivec3 bmu)
{

    glm::ivec3 diff = {0, 0, 0};

    if (latticeData.type == PLANE)
    { // plane
        diff = node - bmu;
    }
    else if (latticeData.type == CYLINDER)
    { // cylinder
        int half = (latticeData.width - 1) / 2;
        if (bmu.y <= half)
        {
            if (node.y >= half + bmu.y)
                diff.y = bmu.y + ((latticeData.width - 1) - node.y);
            else
                diff.y = node.y - bmu.y;
        }
        else if (bmu.y > half)
        {
            if (node.y >= bmu.y - half)
                diff.y = bmu.y - node.y;
            else
                diff.y = node.y + ((latticeData.width - 1) - bmu.y);
        }
        diff.x = node.x - bmu.x;
    }
    else if(latticeData.type == DONUT){
        int half = (latticeData.width-1)/2;
        if(bmu.x <= half){
            if(node.x >= half+bmu.x){
                diff.x = bmu.x+((latticeData.width-1) - node.x);
            }else{
                diff.x = node.x - bmu.x;
            }
        }else if(bmu.x > half){
            if(node.x >= bmu.x - half){
                diff.x = bmu.x - node.x;
            }else{
                diff.x = node.x + ((latticeData.width-1) - bmu.x);
            }
        }

        half = (latticeData.height-1)/2;
        if(bmu.y <= half){
            if(node.y >= half+bmu.y){
                diff.y = bmu.y+((latticeData.height-1) - node.y);
            }else{
                diff.y = node.y - bmu.y;
            }
        }else if(bmu.y > half){
            if(node.y >= bmu.y - half){
                diff.y = bmu.y - node.y;
            }else{
                diff.y = node.y + ((latticeData.height-1) - bmu.y);
            }
        }
    }
    else if (latticeData.type == BALL)
    { // half ball
        //   1          back
        // 2 0 4   left  top  right
        //   3          front
        diff = computeHalfballDist(node)-computeHalfballDist(bmu);
    }
    return diff;
}
glm::ivec3 som_cls::computeHalfballDist(glm::ivec3 p0){

    glm::ivec3 a = {0, 0, 0};
    int w = latticeData.width - 1;
    if(p0.z == 0) a = {p0.x, w, p0.y};
    else if(p0.z == 1) a = {p0.x, p0.y, 0};
    else if(p0.z == 2) a = {0, p0.x, p0.y};
    else if(p0.z == 3) a = {p0.x, p0.y, w};
    else if(p0.z == 4) a = {w, p0.x, p0.y};

    return a;
}
void som_cls::destroy(glm::fvec3 ***arr, int width, int height)
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
void som_cls::destroyDataset(glm::fvec3 *arr, int datasteNum)
{
    free(arr);
}
double som_cls::computeradius(int iter, double fun)
{
    double lamda = ((double)(latticeData.finalIter)) / log(fun);
    double sigma = fun * exp(-1 * ((double)iter) / lamda);

    return sigma;
}
double som_cls::computerate(int iter, double fun)
{
    double sigma = fun * exp(-1 * ((double)iter) / ((double)(latticeData.finalIter)));
    return sigma;
}

const glm::fvec3 som_cls::getInput(glm::fvec3 *dataset, int datasteNum)
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

bool som_cls::isInradiushood(double squaredDist, double radius)
{
    if (squaredDist <= (radius * radius))
    {
        // std::cout << "dist : " << squaredDist << " radius : " << radius*radius << std::endl;
        return true;
    }
    return false;
}

double som_cls::computeScale(double sigma, double dist)
{
    double theta = exp((-1 * dist) / (2 * pow(sigma, 2)));

    return theta;
}

void som_cls::updateNode(glm::fvec3 ***lattice, glm::fvec3 nowInput, glm::ivec3 nodeId, double radius, double learningRate)
{
    lattice[nodeId.z][nodeId.y][nodeId.x].x = lattice[nodeId.z][nodeId.y][nodeId.x].x + radius * learningRate * (nowInput.x - lattice[nodeId.z][nodeId.y][nodeId.x].x);
    lattice[nodeId.z][nodeId.y][nodeId.x].y = lattice[nodeId.z][nodeId.y][nodeId.x].y + radius * learningRate * (nowInput.y - lattice[nodeId.z][nodeId.y][nodeId.x].y);
    lattice[nodeId.z][nodeId.y][nodeId.x].z = lattice[nodeId.z][nodeId.y][nodeId.x].z + radius * learningRate * (nowInput.z - lattice[nodeId.z][nodeId.y][nodeId.x].z);
}