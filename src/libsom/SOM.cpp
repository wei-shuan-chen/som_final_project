#include <cstdlib>
#include <ctime>
#include <iostream>

#include "SOM.h"
som_cls **som;
som_cls psom;

void create_mutli_som(int layerNum, int blockNum)
{
    som = (som_cls **)malloc(sizeof(som_cls *) * layerNum);
    for (int layer = 0; layer < layerNum; layer++)
    {
        som[layer] = (som_cls *)malloc(sizeof(som_cls) * blockNum);
    }
}

som_cls::som_cls()
{
}

som_cls::~som_cls()
{
}

void som_cls::SOM_Create(std::vector<glm::ivec3> voxelPos, int voxelNum, glm::ivec3 max, glm::ivec3 min, int type, glm::ivec3 texWHD, int texType)
{
    som_init();
    latticeData.type = type;
    latticeData.texType = texType;
    inputData.nPos = voxelNum;
    inputData.nTex = texWHD.x * texWHD.y * texWHD.z;

    srand(time(NULL));
    // 1. Create input dataset
    // input0 pos
    inputData.iPos = create_input_position(voxelPos, voxelNum);
    // input1 tex
    inputData.iTex = create_input_texture(texWHD);
    // 2. Create lattice
    // weight0 pos
    latticeData.wPos = create_weight_position(max, min);
    // weight1 tex
    latticeData.wTex = create_weight_texture();
}
void som_cls::som_init()
{
    latticeData.width = 10;
    latticeData.height = 10;
    latticeData.depth = 10;

    latticeData.iter[0] = 0;
    latticeData.iter[1] = 0;
    latticeData.finalIter[0] = 120000;
    latticeData.finalIter[1] = 120000;

    latticeData.initLearningRate[0] = 0.005;
    latticeData.initLearningRate[1] = 0.005;

    latticeData.initRadius[0] = latticeData.width / 2.0;
    latticeData.initRadius[1] = latticeData.width / 2.0;

    latticeData.type = 1; // 0 plane, 1 cylinder, 2 donut, 3 ball
    latticeData.typeNum[0] = 1;
    latticeData.typeNum[1] = 1;
    latticeData.typeNum[2] = 1;
    latticeData.typeNum[3] = 6;
    latticeData.typeNum[4] = latticeData.depth;

    latticeData.texType = 0;
    latticeData.texTypeNum[0] = 1;
    latticeData.texTypeNum[1] = latticeData.depth;

    weightType = POS;

    latticeData.anchorP = (glm::ivec3 *)malloc(sizeof(glm::ivec3) * 8);
    // 0~3 front 4~7 back  (leftdown rightdown leftup rightup)
    latticeData.anchorP[0] = {0, 3, 0};
    latticeData.anchorP[1] = {7, 0, 0};
    latticeData.anchorP[2] = {latticeData.width - 1, latticeData.height - 1, 0};
    latticeData.anchorP[3] = {0, latticeData.height-1, 0};

    latticeData.anchorP[4] = {0, 0, latticeData.depth - 1};
    latticeData.anchorP[5] = {latticeData.width - 1, 0, latticeData.depth - 1};
    latticeData.anchorP[6] = {latticeData.width - 1, latticeData.height - 1, latticeData.depth - 1};
    latticeData.anchorP[7] = {0, latticeData.height - 1, latticeData.depth - 1};
}

void som_cls::Lattice_resolution_set(int resolution, glm::ivec3 max, glm::ivec3 min)
{
    destroy_weight_position(latticeData.typeNum[latticeData.type]);
    destroy_weight_texture(latticeData.texTypeNum[latticeData.texType]);
    latticeData.width = resolution;
    latticeData.height = resolution;
    latticeData.typeNum[4] = latticeData.depth = resolution;
    latticeData.anchorP[0] = {0, 0, 0};
    latticeData.anchorP[1] = {latticeData.width - 1, 0, 0};
    latticeData.anchorP[2] = {latticeData.width - 1, latticeData.height - 1, 0};
    latticeData.anchorP[3] = {0, latticeData.height-1, 0};

    latticeData.anchorP[4] = {0, 0, latticeData.depth - 1};
    latticeData.anchorP[5] = {latticeData.width - 1, 0, latticeData.depth - 1};
    latticeData.anchorP[6] = {latticeData.width - 1, latticeData.height - 1, latticeData.depth - 1};
    latticeData.anchorP[7] = {0, latticeData.height - 1, latticeData.depth - 1};
    latticeData.wPos = create_weight_position(max, min);
    latticeData.wTex = create_weight_texture();
}
void som_cls::Lattice_iter_set(int finalIter)
{
    latticeData.finalIter[weightType] = finalIter;
}
void som_cls::Lattice_radius_set(float initradius)
{
    latticeData.initRadius[weightType] = initradius;
}
void som_cls::Lattice_rate_set(float initrate)
{
    latticeData.initLearningRate[weightType] = initrate;
}
void som_cls::Lattice_type_set(int type, glm::ivec3 max, glm::ivec3 min)
{
    latticeData.type = type;
    destroy_weight_position(latticeData.typeNum[latticeData.type]);
    latticeData.wPos = create_weight_position(max, min);
}
void som_cls::Lattice_pos_set(std::vector<glm::ivec3> voxelPos, int voxelNum, glm::ivec3 max, glm::ivec3 min)
{
    destroy_weight_position(latticeData.typeNum[latticeData.type]);
    destroy_input_position();
    latticeData.wPos = create_weight_position(max, min);
    inputData.iPos = create_input_position(voxelPos, voxelNum);
    inputData.nPos = voxelNum;
}
void som_cls::Lattice_tex_set(glm::ivec3 texWHD)
{
    destroy_input_texturea();
    inputData.iTex = create_input_texture(texWHD);
    inputData.nTex = texWHD.x * texWHD.y * texWHD.z;
}
void som_cls::Lattice_anchor_set(glm::ivec3 *newp)
{
    free(latticeData.anchorP);
    destroy_weight_texture(latticeData.typeNum[latticeData.type]);
    latticeData.anchorP = newp;
    latticeData.wTex = create_weight_texture();
}
void som_cls::SOM_IterateOnce(int wType)
{
    weightType = wType;
    // 1. Get one input from the dataset
    double learningRate = compute_learningrate();
    double radius = compute_radius();
    const glm::fvec3 nowInput = get_input();
    // cout << "nowinput : "<< nowInput.x << ", " << nowInput.y << ", " << nowInput.z<< endl;
    // 2. Find BMU
    const glm::ivec3 bmu = find_bmu(nowInput);
    // cout << "bmu : " << bmu.x << ", " << bmu.y << ", " << bmu.z << endl;
    // 3. Update BMU and the radius
    for (int k = 0; k < latticeData.typeNum[latticeData.type]; k++)
    {
        if (weightType == TEX)
            if (k == latticeData.texTypeNum[latticeData.texType])
                break; // 0000000000000000000

        for (int i = 0; i < latticeData.height; i++)
        {
            for (int j = 0; j < latticeData.width; j++)
            {
                glm::ivec3 node = glm::ivec3(j, i, k);
                glm::ivec3 diff = comput_neiborhood(node, bmu); // node - bmu;
                double squaredDist = static_cast<double>(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);
                if (inradius_neiborhood(squaredDist, radius))
                {
                    double n_radius = compute_scale(radius, squaredDist);
                    // cout << "scale : " << n_radius << endl;
                    update_node(nowInput, node, n_radius, learningRate);
                }
                // cout << "("<<latticeData.wTex[k][i][j].x <<","<<latticeData.wTex[k][i][j].y<<") ";
            }
            // cout << "\n";
        }
        // cout << "\n\n";
    }

    latticeData.iter[weightType]++;
}

LatData_t *som_cls::Lattice_get()
{
    return &latticeData;
}
glm::fvec3 *som_cls::create_input_position(std::vector<glm::ivec3> voxelPos, int voxelNum)
{
    glm::fvec3 *dataset = (glm::fvec3 *)malloc(sizeof(glm::fvec3) * voxelNum);

    for (int i = 0; i < voxelNum; i++)
        dataset[i] = voxelPos[i];

    return dataset;
}
glm::fvec3 *som_cls::create_input_texture(glm::ivec3 texWHD)
{
    glm::ivec3 *p = latticeData.anchorP;

    glm::fvec3 *dataset = (glm::fvec3 *)malloc(sizeof(glm::fvec3) * texWHD.x * texWHD.y * texWHD.z); // 0000000000

    for (int z = 0; z < texWHD.z; z++)
    {
        for (int y = 0; y < texWHD.y; y++)
        {
            for (int x = 0; x < texWHD.x; x++)
            {
                int n = x + y * texWHD.x + z * texWHD.x * texWHD.y;
                dataset[n] = {(double)x / (double)texWHD.x, (double)y / (double)texWHD.y, (double)z / (double)texWHD.z};
            }
        }
    }

    return dataset;
}
glm::fvec3 ***som_cls::create_weight_texture()
{
    int width = latticeData.width, height = latticeData.height, depth = latticeData.texTypeNum[latticeData.texType];
    // 1. create 3D lattice
    glm::fvec3 ***texWeight = (glm::fvec3 ***)malloc(sizeof(glm::fvec3 **) * depth);
    for (int j = 0; j < depth; j++)
    {
        texWeight[j] = (glm::fvec3 **)malloc(sizeof(glm::fvec3 *) * height);
        for (int i = 0; i < height; i++)
        {
            texWeight[j][i] = (glm::fvec3 *)malloc(sizeof(glm::fvec3) * width);
            for (int k = 0; k < width; k++)
            {
                // 2. init texture weight value
                double i0, j0, k0;

                i0 = (double)rand() / (double)(RAND_MAX + 1.0);
                j0 = (double)rand() / (double)(RAND_MAX + 1.0);
                k0 = (double)rand() / (double)(RAND_MAX + 1.0);

                texWeight[j][i][k] = {i0, j0, k0};
            }
        }
    }


    if (latticeData.texType == TWODTEX)
    {
        // latticeData.partArea = (big_x-small_x+1)*(big_y-small_y+1);
        return create_weight_texture_2D(texWeight);
    }
    if(latticeData.texType == THREEDTEX){
    //     latticeData.partArea = (big_x-small_x)*(big_y-small_y)*(big_z-small_z);

        glm::ivec3 *p = latticeData.anchorP;

        int small_x, small_y, small_z, big_x, big_y, big_z;
        small_x = min(min(p[0].x, p[2].x), min(p[4].x, p[6].x));
        big_x = max(max(p[1].x, p[3].x), max(p[5].x, p[7].x));

        small_y = min(min(p[0].y, p[1].y), min(p[4].y, p[5].y));
        big_y = max(max(p[2].y, p[3].y), max(p[6].y, p[7].y));

        small_z = min(min(p[0].z, p[1].z), min(p[2].z, p[3].z));
        big_z = max(max(p[4].z, p[5].z), max(p[6].z, p[7].z));

        for (int d = 0; d < depth; d++)
        {
            for (int h = 0; h < height; h++)
            {
                for (int w = 0; w < width; w++)
                {
                    double i0, j0, k0;

                    i0 = (float)w / (float)(width - 1);
                    j0 = (float)h / (float)(height - 1);
                    k0 = (float)d / (float)(depth - 1);

                    texWeight[d][h][w] = {i0, j0, k0};
                }
            }
        }

    }

    return texWeight;
}
glm::fvec3 ***som_cls::create_weight_texture_2D(glm::fvec3 ***texWeight){
    int width = latticeData.width, height = latticeData.height, depth = latticeData.texTypeNum[latticeData.texType];
    glm::ivec3 *p = latticeData.anchorP;
    // 3. find boundary
    p[4] = p[0];
    for (int i = 0; i < 4; i++)
    { // 01 12 23 30   four edge
        int deltay = abs(p[i + 1].y - p[i].y);
        int deltax = abs(p[i + 1].x - p[i].x);

        int w_dir = (p[i + 1].x >= p[i].x) ? 1 : -1;
        int h_dir = (p[i + 1].y >= p[i].y) ? 1 : -1;
        int step = (deltax >= deltay) ? deltay : deltax;

        // cout << "\ndelta y = " << deltay << ", delta x = " << deltax<< ", y_dir = " << h_dir << ", x_dir = " << w_dir << endl;
        int w = p[i].x, h = p[i].y;
        while (w != p[i + 1].x || h != p[i + 1].y)
        {
            // get value
            if(texWeight[0][h][w].x > 0) texWeight[0][h][w].x *= -1.0;
            if(texWeight[0][h][w].y > 0) texWeight[0][h][w].y *= -1.0;
            if(texWeight[0][h][w].z > 0) texWeight[0][h][w].z *= -1.0;
            // cout << "h : " << h << ", w : " << w << ", step : " << step << endl;
            // for (int hi = 0; hi < height; hi++)
            // {
            //     for (int wi = 0; wi < width; wi++)
            //     {
            //         cout <<setprecision(2) << "(" << texWeight[0][hi][wi].x << ", " << texWeight[0][hi][wi].y << ")";
            //     }
            //     cout << "\n";
            // }
            // cout << "\n\n\n";
            // next grid
            if(deltax >= deltay){
                if(step < deltax){
                    step += deltay;
                    w+=w_dir;
                }else{
                    step -= deltax;
                    h+=h_dir;
                }
            }else if(deltax < deltay){
                if(step < deltay){
                    step+=deltax;
                    h+=h_dir;
                }else{
                    step-=deltay;
                    w+=w_dir;
                }
            }
        }
    }
    // 4. find inside
    for (int h = 0; h < height; h++)
    {
        bool inside = false;
        int edge = 0;
        for (int w = 0; w < width; w++)
        {
            edge=w;
            if(texWeight[0][h][w].x <= 1.0 && texWeight[0][h][w].x >= 0.0 && inside) {
                break;
            }
            if(texWeight[0][h][w].x < 0.0){
                inside = true;
            }
            if(inside) {
                texWeight[0][h][w].x *= -1.0;
                texWeight[0][h][w].y *= -1.0;
                texWeight[0][h][w].z *= -1.0;
            }
            else texWeight[0][h][w] = {1.1,1.1,1.1};

        }
        inside = false;
        for(int w = width-1; w >= edge; w--){
            if(texWeight[0][h][w].x <= 1.0 && texWeight[0][h][w].x >= 0.0 && inside) break;
            if(texWeight[0][h][w].x < 0.0){
                inside = true;
            }
            if(inside) {
                texWeight[0][h][w].x *= -1.0;
                texWeight[0][h][w].y *= -1.0;
                texWeight[0][h][w].z *= -1.0;
            }
            else texWeight[0][h][w] = {1.1,1.1,1.1};

        }
    }
    // 5. set anchor point
    for (int a = 0; a < 4; a++)
    {
        int i0, j0, k0;
        // i0 = a % 2;
        if (a == 0 || a == 3 || a == 4 || a == 7)
            i0 = 0;
        else
            i0 = 1;
        if (a == 0 || a == 1 || a == 4 || a == 5)
            j0 = 0;
        else
            j0 = 1;
        k0 = 0.0;

        texWeight[0][p[a].y][p[a].x] = {i0, j0, k0};

    }
    // for (int hi = 0; hi < height; hi++)
    // {
    //     for (int wi = 0; wi < width; wi++)
    //     {
    //         cout <<setprecision(2) << "(" << texWeight[0][hi][wi].x << ", " << texWeight[0][hi][wi].y << ")";
    //     }
    //     cout << "\n";
    // }
    // cout << "\n\n\n";
    return texWeight;
}
// glm::fvec3 ***som_cls::create_weight_texture_3D(){

// }
glm::fvec3 ***som_cls::create_weight_position(glm::ivec3 max, glm::ivec3 min)
{
    int width = latticeData.width, height = latticeData.height, depth = latticeData.depth;
    glm::ivec3 size = max - min;
    glm::fvec3 ***lattice = (glm::fvec3 ***)malloc(sizeof(glm::fvec3 **) * depth);
    for (int j = 0; j < depth; j++)
    {
        lattice[j] = (glm::fvec3 **)malloc(sizeof(glm::fvec3 *) * height);
        for (int i = 0; i < height; i++)
        {
            lattice[j][i] = (glm::fvec3 *)malloc(sizeof(glm::fvec3) * width);
        }
    }

    if (latticeData.type == PLANE)
    {
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
    }
    else if (latticeData.type == CYLINDER)
    {

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
    }
    else if (latticeData.type == DONUT)
    {
        float R = (size[2] + size[1]) / 4;
        float r = R / 5.0;
        for (int h = 0; h < height; h++)
        {
            for (int w = 0; w < width; w++)
            {
                double fi = 2 * PI * (double)w / (double)(width - 1);
                double theta = 2 * PI * (double)h / (double)(height - 1);

                double i0 = r * cos(theta) + ((double)size[0] / 2.0) + min[0];
                double j0 = cos(fi) * (R + r * sin(theta)) + ((double)size[1] / 2.0) + min[1];
                double k0 = sin(fi) * (R + r * sin(theta)) + ((double)size[2] / 2.0) + min[2];
                lattice[0][h][w] = {i0, j0, k0};
            }
        }
    }
    else if (latticeData.type == BALL)
    {
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
    else if (latticeData.type == CUBE)
    {
        double i0, j0, k0;
        for (int d = 0; d < depth; d++)
        {
            for (int h = 0; h < height; h++)
            {
                for (int w = 0; w < width; w++)
                {
                    double ratio_w = (double)w / (double)(width - 1);
                    double ratio_h = (double)h / (double)(height - 1);
                    double ratio_d = (double)d / (double)(depth - 1);

                    i0 = (double)size[0] * ratio_w + min[0];
                    j0 = (double)size[1] * ratio_h + min[1];
                    k0 = (double)size[2] * ratio_d + min[2];

                    lattice[d][h][w] = {i0, j0, k0};
                }
            }
        }
    }

    return lattice;
}

double som_cls::compute_radius()
{
    double iter_d = latticeData.iter[weightType];
    double finalIter_d = latticeData.finalIter[weightType];
    double initRadius_d = latticeData.initRadius[weightType];

    double sigma = initRadius_d * exp(-1 * log(initRadius_d) * iter_d / finalIter_d);

    return sigma;
}
double som_cls::compute_learningrate()
{
    double iter_d = latticeData.iter[weightType];
    double finalIter_d = latticeData.finalIter[weightType];
    double initLearningRate_d = latticeData.initLearningRate[weightType];

    double sigma = initLearningRate_d * exp(-1 * iter_d / (finalIter_d));

    return sigma;
}
const glm::fvec3 som_cls::get_input()
{
    // 0 <= rand_i < 1
    double rand_i = (double)rand() / (double)(RAND_MAX + 1.0);

    if (weightType == POS)
    {
        int i = rand_i * inputData.nPos;
        return inputData.iPos[i];
    }
    if (weightType == TEX)
    {
        int i = rand_i * (inputData.nTex);
        return inputData.iTex[i];
    }
}

const glm::ivec3 som_cls::find_bmu(glm::fvec3 nowInput)
{
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
                float dx, dy, dz;
                if (weightType == POS)
                {
                    dx = (latticeData.wPos[k][i][j].x - nowInput.x);
                    dy = (latticeData.wPos[k][i][j].y - nowInput.y);
                    dz = (latticeData.wPos[k][i][j].z - nowInput.z);
                }
                if (weightType == TEX)
                {
                    dx = (latticeData.wTex[k][i][j].x - nowInput.x);
                    dy = (latticeData.wTex[k][i][j].y - nowInput.y);
                    dz = (latticeData.wTex[k][i][j].z - nowInput.z);
                }
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
double som_cls::compute_scale(double radius, double dist)
{
    double scale = exp((-1 * dist) / (2 * pow(radius, 2)));

    return scale;
}
void som_cls::update_node(glm::fvec3 input, glm::ivec3 update, double scale, double learningRate)
{
    int x = update.x, y = update.y, z = update.z;
    // cout << x << ", " << y << ", " << z << endl;
    if (weightType == POS)
    {
        latticeData.wPos[z][y][x].x = latticeData.wPos[z][y][x].x + scale * learningRate * (input.x - latticeData.wPos[z][y][x].x);
        latticeData.wPos[z][y][x].y = latticeData.wPos[z][y][x].y + scale * learningRate * (input.y - latticeData.wPos[z][y][x].y);
        latticeData.wPos[z][y][x].z = latticeData.wPos[z][y][x].z + scale * learningRate * (input.z - latticeData.wPos[z][y][x].z);
    }
    if (weightType == TEX)
    {
        for (int t = 0; t < 8; t++)
        {
            if (latticeData.anchorP[t] == update)
            {
                return;
            }
        }
        if (latticeData.wTex[z][y][x].x > 1.0 || latticeData.wTex[z][y][x].y > 1.0 || latticeData.wTex[z][y][x].z > 1.0)
            return;

        latticeData.wTex[z][y][x].x = latticeData.wTex[z][y][x].x + scale * learningRate * (input.x - latticeData.wTex[z][y][x].x);
        latticeData.wTex[z][y][x].y = latticeData.wTex[z][y][x].y + scale * learningRate * (input.y - latticeData.wTex[z][y][x].y);
        latticeData.wTex[z][y][x].z = latticeData.wTex[z][y][x].z + scale * learningRate * (input.z - latticeData.wTex[z][y][x].z);
    }
}

glm::ivec3 som_cls::comput_neiborhood(glm::ivec3 node, glm::ivec3 bmu)
{

    glm::ivec3 diff = {0, 0, 0};

    if (latticeData.type == PLANE || latticeData.type == CUBE || weightType == TEX)
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
    else if (latticeData.type == DONUT)
    {
        int half = (latticeData.width - 1) / 2;
        if (bmu.x <= half)
        {
            if (node.x >= half + bmu.x)
            {
                diff.x = bmu.x + ((latticeData.width - 1) - node.x);
            }
            else
            {
                diff.x = node.x - bmu.x;
            }
        }
        else if (bmu.x > half)
        {
            if (node.x >= bmu.x - half)
            {
                diff.x = bmu.x - node.x;
            }
            else
            {
                diff.x = node.x + ((latticeData.width - 1) - bmu.x);
            }
        }

        half = (latticeData.height - 1) / 2;
        if (bmu.y <= half)
        {
            if (node.y >= half + bmu.y)
            {
                diff.y = bmu.y + ((latticeData.height - 1) - node.y);
            }
            else
            {
                diff.y = node.y - bmu.y;
            }
        }
        else if (bmu.y > half)
        {
            if (node.y >= bmu.y - half)
            {
                diff.y = bmu.y - node.y;
            }
            else
            {
                diff.y = node.y + ((latticeData.height - 1) - bmu.y);
            }
        }
    }
    else if (latticeData.type == BALL)
    { // half ball
        //   1          back
        // 2 0 4   left  top  right
        //   3          front
        diff = compute_halfball_dist(node) - compute_halfball_dist(bmu);
    }
    // else if(latticeData.type == CUBE){
    //     diff = node - bmu;
    // }
    return diff;
}
glm::ivec3 som_cls::compute_halfball_dist(glm::ivec3 p0)
{

    glm::ivec3 a = {0, 0, 0};
    int w = latticeData.width - 1;
    if (p0.z == 0)
        a = {p0.x, w, p0.y};
    else if (p0.z == 1)
        a = {p0.x, p0.y, 0};
    else if (p0.z == 2)
        a = {0, p0.x, p0.y};
    else if (p0.z == 3)
        a = {p0.x, p0.y, w};
    else if (p0.z == 4)
        a = {w, p0.x, p0.y};
    else if (p0.z == 5)
        a = {p0.x, 0, p0.y};

    return a;
}

bool som_cls::inradius_neiborhood(double squaredDist, double radius)
{
    if (squaredDist <= (radius * radius))
    {
        // std::cout << "dist : " << squaredDist << " radius : " << radius*radius << std::endl;
        return true;
    }
    return false;
}

void som_cls::destroy_weight_position(int depth)
{
    for (int d = 0; d < depth; d++)
    {
        for (int h = 0; h < latticeData.height; h++)
        {
            free(latticeData.wPos[d][h]);
        }
        free(latticeData.wPos[d]);
    }
}
void som_cls::destroy_weight_texture(int depth)
{
    for (int d = 0; d < depth; d++)
    {
        for (int h = 0; h < latticeData.height; h++)
        {
            free(latticeData.wTex[d][h]);
        }
        free(latticeData.wTex[d]);
    }
}

void som_cls::destroy_input_position()
{
    free(inputData.iPos);
}
void som_cls::destroy_input_texturea()
{
    free(inputData.iTex);
}
void som_cls::SOM_End()
{
    // 1. destroy_weight_position lattice
    destroy_weight_position(latticeData.typeNum[latticeData.type]);
    destroy_weight_texture(latticeData.texTypeNum[latticeData.texType]);
    // 2. destroy_weight_position input dataset
    destroy_input_position();
    destroy_input_texturea();
}