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


void som_cls::SOM_Create(std::vector<glm::ivec3> voxelPos, int voxelNum, glm::ivec3 max, glm::ivec3 min)
{
    srand(time(NULL));
    // 1. Create input dataset
    inputData.input = createInputDataset(voxelPos, voxelNum);
    // 2. Create lattice
    latticeData.lattice = createLatticeData(latticeData.width, latticeData.height, max, min);
    inputData.num = voxelNum;
}

void som_cls::SOM_IterateOnce()
{
    // 1. Get one input from the dataset
    latticeData.learningRate = computeLearningRate();
    latticeData.radius = computeRadius();
    const glm::fvec3 nowInput = getInput();
    // cout << "nowinput : "<< nowInput.x << ", " << nowInput.y << ", " << nowInput.z<< endl;
    // 2. Find BMU
    const glm::ivec3 bmu = findBmu(nowInput);
    // cout << "bmu : " << bmu.x << ", " << bmu.y << ", " << bmu.z << endl;
    // 3. Update BMU and the radius
    // findBmuNeighbor(nowInput, bmu);
    for (int k = 0; k < latticeData.typeNum[latticeData.type]; k++)
    {
        for (int i = 0; i < latticeData.height; i++)
        {
            for (int j = 0; j < latticeData.width; j++)
            {
                glm::ivec3 node = glm::ivec3(j, i, k);
                glm::ivec3 diff = computNeiborhood(node, bmu); // node - bmu;
                double squaredDist = static_cast<double>(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);
                if (isInradiushood(squaredDist, latticeData.radius))
                {
                    double n_radius = computeScale(latticeData.radius, squaredDist);
                    // cout << "scale : " << n_radius << endl;
                    updateNode(latticeData.lattice, nowInput, node, n_radius, latticeData.learningRate);
                }
            }
        }
    }

    latticeData.iter++;
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
glm::fvec3 *** som_cls::createLatticeData(int width, int height, glm::ivec3 max, glm::ivec3 min)
{
    cout << "max : " << max.x << ", " << max.y << ", " << max.z << endl;
    cout << "min : " << min.x << ", " << min.y << ", " << min.z << endl;
    glm::ivec3 size = max-min;
    cout << "size : " << size.x << ", " << size.y << ", " << size.z << endl;
    glm::fvec3 ***lattice = (glm::fvec3 ***)malloc(sizeof(glm::fvec3 **) * 6);
    for (int j = 0; j < 6; j++)
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

                i0 = (double)size[0] * ratio_w + min[0];
                j0 = size[1] + min[1];
                k0 = (double)size[2] * ratio_h + min[2];

                lattice[0][h][w] = {i0, j0, k0};
            }
        }
    }else if(latticeData.type == CYLINDER){


        for (int h = 0; h < height; h++)
        {
            for (int w = 0; w < width; w++)
            {
                double i0, j0, k0;

                double ratio_w = (double)w / (double)(width - 1);
                double ratio_h = (double)h / (double)(height - 1);

                i0 = ((double)size[0] / 2.0) * cos(2 * PI * ratio_w) + (size[0] / 2) + min[0];
                j0 = ratio_h * (double)size[1] + min[1];
                k0 = ((double)size[2] / 2.0) * sin(2 * PI * ratio_w) + (size[2] / 2) + min[2];
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

                double i0 = r * cos(theta) + ((double)size[0] / 2.0) + min[0];
                double j0 =  cos(fi)* ( R + r*sin(theta)) + ((double)size[1] / 2.0) + min[1];
                double k0 = sin(fi)* ( R + r*sin(theta)) + ((double)size[2] / 2.0) + min[2];
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
                // 0 x-z plane up
                i0 = size[0] * ratio_w + min[0];
                j0 = size[1] + min[1];
                k0 = size[2] * ratio_h + min[2];
                lattice[0][h][w] = {i0, j0, k0};

                // 1 x-y plane back
                i0 = size[0] * ratio_w + min[0];
                j0 = size[1] * ratio_h + min[1];
                k0 = 0 + min[2];
                lattice[1][h][w] = {i0, j0, k0};

                // 2 y-z plane left
                i0 = 0 + min[0];
                j0 = size[1] * ratio_w + min[1];
                k0 = size[2] * ratio_h + min[2];
                lattice[2][h][w] = {i0, j0, k0};

                // 3 x-y plane front
                i0 = size[0] * ratio_w + min[0];
                j0 = size[1] * ratio_h + min[1];
                k0 = size[2] + min[2];
                lattice[3][h][w] = {i0, j0, k0};

                // 4 y-z plane right
                i0 = size[0] + min[0];
                j0 = size[1] * ratio_w + min[1];
                k0 = size[2] * ratio_h + min[2];
                lattice[4][h][w] = {i0, j0, k0};

                // 5 x-z plane down
                i0 = size[0] * ratio_w + min[0];
                j0 = 0 + min[1];
                k0 = size[2] * ratio_h + min[2];
                lattice[5][h][w] = {i0, j0, k0};

            }
        }
    }

    return lattice;
}

double som_cls::computeRadius()
{
    double iter_d = latticeData.iter;
    double finalIter_d = latticeData.finalIter;
    double initRadius_d = latticeData.initRadius;

    double sigma = initRadius_d * exp(-1 * log(initRadius_d) * iter_d / finalIter_d);

    return sigma;
}
double som_cls::computeLearningRate()
{
    double iter_d = latticeData.iter;
    double finalIter_d = latticeData.finalIter;
    double initLearningRate_d = latticeData.initLearningRate;

    double sigma = initLearningRate_d * exp(-1 * iter_d / finalIter_d);

    return sigma;
}
const glm::fvec3 som_cls::getInput()
{
    // 0 <= rand_i < 1
    double rand_i = (double)rand() / (double)(RAND_MAX+1.0);
    int i = rand_i*inputData.num;

    return inputData.input[i];
}
const glm::ivec3 som_cls::findBmu(glm::fvec3 nowInput){
    double minDist = -1.0;
    glm::ivec3 bmu;
    // compute winner point
    for (int k = 0; k < latticeData.typeNum[latticeData.type]; k++)
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
                    bmu = {j, i, k};
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
    return bmu;
}
void som_cls::findBmuNeighbor(glm::fvec3 nowInput, const glm::ivec3 bmu){
    int radius = latticeData.radius;
    for(int r = 0; r < radius; r++){
        for(int m = 0; m < 7; m+=2){
            glm::ivec2 move;
            if(r == 0){
                if(m == 0){
                    move = {0, 0};
                    ensureNeighbor(nowInput, bmu, move, 0.0);
                }
            }else{
                int nowp, nextp;
                if(m == 0){
                    nowp = r*bmuMove[m+2].x;
                    nextp = r*bmuMove[m].x;
                }else if(m == 2){
                    nowp = (r*bmuMove[m+2].y)+1;
                    nextp = (r*bmuMove[m].y)-1;
                }else if(m == 4){
                    nowp = r*bmuMove[m].x;
                    nextp = r*bmuMove[m+2].x;
                }else if(m == 6){
                    nowp = (r*bmuMove[m].y)+1;
                    nextp = (r*bmuMove[m+2].y)-1;
                }

                while(nowp <= nextp){
                    if(m == 0 || m == 4){
                        move.y = r*bmuMove[m].y;
                        move.x = nowp;
                    }
                    if(m == 2 || m == 6){
                        move.x = r*bmuMove[m].x;
                        move.y = nowp;
                    }
                    double squaredDist = static_cast<double>(move.x * move.x + move.y * move.y);
                    if (isInradiushood(squaredDist, radius)){
                        ensureNeighbor(nowInput, bmu, move, squaredDist);
                    }
                    nowp++;
                }
            }
        }

    }

}
void som_cls::ensureNeighbor(glm::fvec3 nowInput, const glm::ivec3 bmu, glm::ivec2 move, double squaredDist){
    int radius = latticeData.radius;
    int w = latticeData.width;
    int h = latticeData.height;

    glm::ivec3 update = bmu;

    glm::ivec2 tmp, delta;
    tmp.x = move.x + bmu.x;
    tmp.y = move.y + bmu.y;

    delta.x = computDelta(w, tmp.x);
    delta.y = computDelta(h, tmp.y);

    if(latticeData.type == PLANE){
        update.x = tmp.x;
        update.y = tmp.y;
        if(tmp.x < 0 || tmp.x >= w)return;
        if(tmp.y < 0 || tmp.y >= h)return;
    }
    if(latticeData.type == CYLINDER){
        update.x = delta.x;
        update.y = tmp.y;
        if(tmp.y < 0 || tmp.y >= h) return;
    }
    if(latticeData.type == DONUT){
        update.x = delta.x;
        update.y = delta.y;
    }
    if(latticeData.type == BALL){
        if((tmp.x < 0 || tmp.x >= w) && (tmp.y < 0 || tmp.y >= h)) return;
        if((tmp.x >= 0 || tmp.x < w) && (tmp.y >= 0 || tmp.y < h)){
            update.x = delta.x;
            update.y = delta.y;
        }else{
            int style = bmu.z, newStyle;

            if(tmp.x < 0 || tmp.x >= w){
                if(tmp.x >= w) newStyle = ballneighber[style][0];
                else newStyle = ballneighber[style][2];

                update.x = delta.x;
                update.y = delta.y;
                if(ballneighber[newStyle][0] == style){
                    update.x = (w-1) - delta.x;
                }
                if(ballneighber[newStyle][1] == style){
                    update.y = (h-1) - delta.y;
                }
            }
            if(tmp.y < 0 || tmp.y >= h){
                if(tmp.y >= h) newStyle = ballneighber[style][1];
                else newStyle = ballneighber[style][3];

                update.x = delta.y;
                update.y = delta.x;
                if(ballneighber[newStyle][0] == style){
                    update.x = (w-1) - delta.y;
                }
                if(ballneighber[newStyle][1] == style){
                    update.y = (h-1) - delta.x;
                }
            }

        }

    }
    double scale = computeScale(radius, squaredDist);
    updateNode(latticeData.lattice, nowInput, update, scale, latticeData.learningRate);

    if(latticeData.type == CYLINDER){
        for(int h1 = 0; h1 < h; h1++){
            latticeData.lattice[0][h1][w-1] = latticeData.lattice[0][h1][0];
        }
    }
    if(latticeData.type == DONUT){
        for(int h1 = 0; h1 < h; h1++){
            latticeData.lattice[0][h1][w-1] = latticeData.lattice[0][h1][0];
        }
        for(int w1 = 0; w1 < w; w1++){
            latticeData.lattice[0][h-1][w1] = latticeData.lattice[0][0][w1];
        }
    }

    return;
}
int som_cls::computDelta(int edge, int tmp){
    int delta;

    if(tmp < 0){ //tmpx < 0
        delta = (edge-1) + tmp;
    }else if(tmp < edge-1){ // 0 <= tmpx <= width-1
        delta = tmp;
    }else{ // width-1 < tmpx
        delta = tmp - (edge-1);
    }

    return delta;
}
double som_cls::computeScale(double radius, double dist)
{
    double scale = exp((-1 * dist) / (2 * pow(radius, 2)));

    return scale;
}
void som_cls::updateNode(glm::fvec3 ***lattice, glm::fvec3 nowInput, glm::ivec3 update, double scale, double learningRate)
{
    int x = update.x, y = update.y, z = update.z;
    // cout << x << ", " << y << ", " << z << endl;
    lattice[z][y][x].x = lattice[z][y][x].x + scale * learningRate * (nowInput.x - lattice[z][y][x].x);
    lattice[z][y][x].y = lattice[z][y][x].y + scale * learningRate * (nowInput.y - lattice[z][y][x].y);
    lattice[z][y][x].z = lattice[z][y][x].z + scale * learningRate * (nowInput.z - lattice[z][y][x].z);
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
    else if(p0.z == 5) a = {p0.x, 0, p0.y};

    return a;
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