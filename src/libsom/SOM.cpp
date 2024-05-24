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

void som_cls::SOM_Create(std::vector<glm::ivec3> voxelPos, int voxelNum, glm::ivec3 max, glm::ivec3 min, int type, glm::ivec3 texWHD)
{
    som_init();
    latticeData.type = type;
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
    latticeData.width = 16;
    latticeData.height = 16;
    latticeData.depth = 6;

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

    weightType = POS;

    latticeData.anchorEdgeP = (glm::ivec3 *)malloc(sizeof(glm::ivec3) * 8);
    // 0~3 front 4~7 back  (leftdown rightdown leftup rightup)
    latticeData.anchorEdgeP[0] = {0, 0, 0};
    latticeData.anchorEdgeP[1] = {latticeData.width - 1, 0, 0};
    latticeData.anchorEdgeP[2] = {latticeData.width - 1, latticeData.height - 1, 0};
    latticeData.anchorEdgeP[3] = {0, latticeData.height - 1, 0};

    latticeData.anchorEdgeP[4] = {0, 0, latticeData.depth - 1};
    latticeData.anchorEdgeP[5] = {latticeData.width - 1, 0, latticeData.depth - 1};
    latticeData.anchorEdgeP[6] = {latticeData.width - 1, latticeData.height - 1, latticeData.depth - 1};
    latticeData.anchorEdgeP[7] = {0, latticeData.height - 1, latticeData.depth - 1};

    latticeData.anchorP = {(latticeData.width)/2, (latticeData.height)/2, 0};
    latticeData.anchorTime = 500;
}

void som_cls::Lattice_resolution_set(int resolution, glm::ivec3 max, glm::ivec3 min)
{
    destroy_weight_position(latticeData.typeNum[latticeData.type]);
    destroy_weight_texture(latticeData.typeNum[latticeData.type]);
    latticeData.width = resolution;
    latticeData.height = resolution;
    latticeData.typeNum[4] = latticeData.depth = resolution;
    latticeData.anchorEdgeP[0] = {0, 0, 0};
    latticeData.anchorEdgeP[1] = {latticeData.width - 1, 0, 0};
    latticeData.anchorEdgeP[2] = {latticeData.width - 1, latticeData.height - 1, 0};
    latticeData.anchorEdgeP[3] = {0, latticeData.height - 1, 0};

    latticeData.anchorEdgeP[4] = {0, 0, latticeData.depth - 1};
    latticeData.anchorEdgeP[5] = {latticeData.width - 1, 0, latticeData.depth - 1};
    latticeData.anchorEdgeP[6] = {latticeData.width - 1, latticeData.height - 1, latticeData.depth - 1};
    latticeData.anchorEdgeP[7] = {0, latticeData.height - 1, latticeData.depth - 1};
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
    destroy_weight_texture(latticeData.typeNum[latticeData.type]);
    latticeData.type = type;

    destroy_weight_position(latticeData.typeNum[latticeData.type]);

    latticeData.wPos = create_weight_position(max, min);
    latticeData.wTex = create_weight_texture();
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
void som_cls::Lattice_anchor_edge_set()
{
    destroy_weight_texture(latticeData.typeNum[latticeData.type]);
    latticeData.wTex = create_weight_texture();
}
void som_cls::Lattice_anchor_set(int *tanc, int anchorTime)
{
    latticeData.anchorTime = anchorTime;
    latticeData.anchorP[0] = tanc[0];
    latticeData.anchorP[1] = tanc[1];
    latticeData.anchorP[2] = tanc[2];
    // cout << tanc[0] << " , "<< tanc[1]<<endl;
    // cout << latticeData.anchorP[0] << " , "<< latticeData.anchorP[1]<<"\n\n";
    set_anchor_point(latticeData.wTex);
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
    const glm::ivec3 bmu = find_bmu(nowInput);//(nowInput.x == 1.5 && weightType == TEX) ? latticeData.anchorP : find_bmu(nowInput);
    // cout << "bmu : " << bmu.x << ", " << bmu.y << ", " << bmu.z << endl;
    // 3. Update BMU and the radius
    for (int k = 0; k < latticeData.typeNum[latticeData.type]; k++)
    {

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
    glm::ivec3 *p = latticeData.anchorEdgeP;

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
    int width = latticeData.width, height = latticeData.height, depth = latticeData.typeNum[latticeData.type];
    // 1. create 3D lattice
    glm::fvec3 ***texWeight = (glm::fvec3 ***)malloc(sizeof(glm::fvec3 **) * depth);
    glm::ivec3 **midAhcor = (glm::ivec3 **)malloc(sizeof(glm::ivec3 *) * (depth - 2));
    for (int d = 0; d < depth; d++)
    {
        if (d < depth - 2)
            midAhcor[d] = (glm::ivec3 *)malloc(sizeof(glm::ivec3) * 4);
        texWeight[d] = (glm::fvec3 **)malloc(sizeof(glm::fvec3 *) * height);
        for (int h = 0; h < height; h++)
        {
            texWeight[d][h] = (glm::fvec3 *)malloc(sizeof(glm::fvec3) * width);
            for (int w = 0; w < width; w++)
            {
                // 2. init texture weight value
                double i0, j0, k0;
                i0 = (double)rand() / (double)(RAND_MAX + 1.0);
                j0 = (double)rand() / (double)(RAND_MAX + 1.0);
                k0 = (double)rand() / (double)(RAND_MAX + 1.0);

                texWeight[d][h][w] = {i0, j0, k0};
            }
        }
    }

    if (latticeData.type != CUBE)
    {
        glm::ivec3 *p = (glm::ivec3 *)malloc(sizeof(glm::ivec3) * 5);
        for (int i = 0; i < 4; i++)
            p[i] = latticeData.anchorEdgeP[i];
        p[4] = p[0]; // 01 12 23 3(4=0)   four edge
        // 3. find boundary
        for (int i = 0; i < 4; i++)
        {
            connect_two_point_into_edge(texWeight, p[i], p[i + 1]);
        }
        // 4. find inside
        find_edge_indside(texWeight);
        // 5. set anchor edge point
        set_anchor_edge_point(texWeight, p);
        // 6. set anchor point
        set_anchor_point(texWeight);
    }
    if (latticeData.type == CUBE)
    {
        const glm::ivec3 *p = latticeData.anchorEdgeP;
        // for (int a = 0; a < 8; a++)
        // {
        //     int i0 =  (a == 0 || a == 3 || a == 4 || a == 7) ? 0 : 1;
        //     int j0 =  (a == 0 || a == 1 || a == 4 || a == 5) ? 0 : 1;
        //     int k0 =  (a == 0 || a == 1 || a == 2 || a == 3) ? 0 : 1;
        //     texWeight[p[a].z][p[a].y][p[a].x] = {i0, j0, k0};
        // }

        // for(int i = 0; i < 12; i++){
        //     glm::ivec3 p0 = p[i%8];
        //     glm::ivec3 p1 = p[(i%8)+1];
        //     if(i == 3) p1 = p[0];
        //     if(i == 7) p1 = p[4];
        //     if(i >= 8) p1 = p[(i%8)+4];
        //     cout << "p0 : " << p0.x << ", "<<p0.y<<", "<<p0.z<<endl;
        //     cout << "p1 : " << p1.x << ", "<<p1.y<<", "<<p1.z<<endl;
        //     connect_two_point_into_edge(texWeight, p0, p1);
        // }

        // for (int d = 0; d < depth; d++)
        // {
        //     for (int h = 0; h < height; h++){
        //         for (int w = 0; w < width; w++) {
        //             cout<<setprecision(2) <<"("<< texWeight[d][h][w].x <<", "<< texWeight[d][h][w].y <<", "<<texWeight[d][h][w].z<<")";
        //         }
        //         cout << "\n";
        //     }
        //     cout << "\n\n";
        // }
        // // 3.5. find 6 plane
        // set_six_plane(texWeight);
        // // 4. find inside + 5. set anchor point
        // find_edge_indside_set_anchor_point(texWeight, p);
        // for (int d = 0; d < depth; d++)
        // {
        //     for (int h = 0; h < height; h++){
        //         for (int w = 0; w < width; w++) {
        //             cout<<setprecision(2) <<"("<< texWeight[d][h][w].x <<", "<< texWeight[d][h][w].y <<", "<<texWeight[d][h][w].z<<")";
        //         }
        //         cout << "\n";
        //     }
        //     cout << "\n\n";
        // }
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
void som_cls::set_six_plane(glm::fvec3 ***texWeight)
{
    // int plane[4][4] = {{0,3,7,4},{},{},{}};
}
void som_cls::connect_two_point_into_edge(glm::fvec3 ***texWeight, const glm::ivec3 p0, const glm::ivec3 p1)
{
    int deltax = abs(p1.x - p0.x);
    int deltay = abs(p1.y - p0.y);
    int deltaz = abs(p1.z - p0.z);
    int delta_max = max(max(deltax, deltay), deltaz);

    int w_dir = (p1.x >= p0.x) ? 1 : -1;
    int h_dir = (p1.y >= p0.y) ? 1 : -1;
    int d_dir = (p1.z >= p0.z) ? 1 : -1;

    int step0 = (delta_max == deltax) ? deltay : deltax;
    int step1 = (delta_max != deltaz) ? deltaz : deltay;

    int w = p0.x, h = p0.y, d = p0.z;
    while (w != p1.x || h != p1.y || d != p1.z)
    {
        // get value
        if (latticeData.type == CUBE)
        {
            if (texWeight[d][h][w].x > 0)
                texWeight[d][h][w].x *= -1.0;
            if (texWeight[d][h][w].y > 0)
                texWeight[d][h][w].y *= -1.0;
            if (texWeight[d][h][w].z > 0)
                texWeight[d][h][w].z *= -1.0;
            // int width = latticeData.width, height = latticeData.height, depth = latticeData.typeNum[latticeData.type];
            // for (int d = 0; d < depth; d++)
            // {
            //     for (int h = 0; h < height; h++){
            //         for (int w = 0; w < width; w++) {
            //             cout<<setprecision(2) << texWeight[d][h][w].x <<", "<< texWeight[d][h][w].y <<", "<<texWeight[d][h][w].z<<" ";
            //         }
            //         cout << "\n";
            //     }
            //     cout << "\n\n";
            // }
        }
        else
        {
            for (int tmp = 0; tmp < latticeData.typeNum[latticeData.type]; tmp++)
            {
                if (texWeight[tmp][h][w].x > 0)
                    texWeight[tmp][h][w].x *= -1.0;
                if (texWeight[tmp][h][w].y > 0)
                    texWeight[tmp][h][w].y *= -1.0;
                if (texWeight[tmp][h][w].z > 0)
                    texWeight[tmp][h][w].z *= -1.0;
            }
        }
        // next grid
        if (deltax == delta_max)
        {
            if (step0 < deltax && step1 < deltax)
            {
                step0 += deltay;
                step1 += deltaz;
                w += w_dir;
            }
            else if (step0 >= deltax)
            {
                step0 -= deltax;
                h += h_dir;
            }
            else if (step1 >= deltax)
            {
                step1 -= deltax;
                d += d_dir;
            }
        }
        else if (deltay == delta_max)
        {
            if (step0 < deltay && step1 < deltay)
            {
                step0 += deltax;
                step1 += deltaz;
                h += h_dir;
            }
            else if (step0 >= deltay)
            {
                step0 -= deltay;
                w += w_dir;
            }
            else if (step1 >= deltay)
            {
                step1 -= deltay;
                d += d_dir;
            }
        }
        else if (deltaz == delta_max)
        {
            if (step0 < deltaz && step1 < deltaz)
            {
                step0 += deltax;
                step1 += deltay;
                d += d_dir;
            }
            else if (step0 >= deltaz)
            {
                step0 -= deltaz;
                w += w_dir;
            }
            else if (step1 >= deltaz)
            {
                step1 -= deltaz;
                h += h_dir;
            }
        }
    }
}
void som_cls::find_edge_indside(glm::fvec3 ***texWeight)
{
    int width = latticeData.width, height = latticeData.height, depth = latticeData.typeNum[latticeData.type];

    // 4. find inside
    for (int d = 0; d < depth; d++)
    {
        for (int h = 0; h < height; h++)
        {
            bool inside = false;
            int edge = 0;
            for (int w = 0; w < width; w++)
            {
                edge = w;
                if (texWeight[d][h][w].x <= 1.0 && texWeight[d][h][w].x >= 0.0 && inside)
                {
                    break;
                }
                if (texWeight[d][h][w].x < 0.0)
                {
                    inside = true;
                }
                if (inside)
                {
                    texWeight[d][h][w].x *= -1.0;
                    texWeight[d][h][w].y *= -1.0;
                    texWeight[d][h][w].z *= -1.0;
                }
                else
                    texWeight[d][h][w] = {10000.0, 10000.0, 10000.0};
            }
            inside = false;
            for (int w = width - 1; w >= edge; w--)
            {
                if (texWeight[d][h][w].x <= 1.0 && texWeight[d][h][w].x >= 0.0 && inside)
                    break;
                if (texWeight[d][h][w].x < 0.0)
                {
                    inside = true;
                }
                if (inside)
                {
                    texWeight[d][h][w].x *= -1.0;
                    texWeight[d][h][w].y *= -1.0;
                    texWeight[d][h][w].z *= -1.0;
                }
                else
                    texWeight[d][h][w] = {10000.0, 10000.0, 10000.0};
            }
        }
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
}
void som_cls::set_anchor_edge_point(glm::fvec3 ***texWeight, const glm::ivec3 *p)
{
    // 5. set anchor edge point
    int depth = latticeData.typeNum[latticeData.type];

    for (int d = 0; d < depth; d++)
    {
        int num = (latticeData.type != CUBE) ? 4 : 8;
        for (int a = 0; a < num; a++)
        {
            int i0 = (a == 0 || a == 3 || a == 4 || a == 7) ? 0 : 1;
            int j0 = (a == 0 || a == 1 || a == 4 || a == 5) ? 0 : 1;
            int k0 = (a == 0 || a == 1 || a == 2 || a == 3) ? 0 : 1;

            int tmpd = (latticeData.type != CUBE) ? d : p[a].z;
            texWeight[tmpd][p[a].y][p[a].x] = {i0, j0, k0};
        }
        // glm::ivec3 anc=latticeData.anchorP;
        // anc.x = (latticeData.anchorP.x<latticeData.anchorEdgeP[6].x) ? latticeData.anchorP.x:latticeData.anchorEdgeP[6].x;
        // anc.y = (latticeData.anchorP.y<latticeData.anchorEdgeP[6].y) ? latticeData.anchorP.y:latticeData.anchorEdgeP[6].y;
        // anc.z = (latticeData.anchorP.z<latticeData.anchorEdgeP[6].z) ? latticeData.anchorP.z:latticeData.anchorEdgeP[6].z;

        // texWeight[anc.z][anc.y][anc.x] = {0.5, 0.5, 0.0};
        // texWeight[d][p[1].y][p[1].x] = {1.0, 0.5, 0.0};
        // texWeight[d][p[2].y][p[2].x] = {1.0, 1.0, 0.0};
        // texWeight[d][p[3].y][p[3].x] = {0.5, 1.0, 0.0};
    }
}
void som_cls::set_anchor_point(glm::fvec3 ***texWeight){
    // 6. set anchor point
    int depth = latticeData.typeNum[latticeData.type];

    // for (int d = 0; d < depth; d++)
    // {
        glm::ivec3 anc=latticeData.anchorP;
        // cout << anc.x <<", "<<anc.y<<endl;
        // anc.x = (latticeData.anchorP.x<latticeData.anchorEdgeP[6].x) ? latticeData.anchorP.x:latticeData.anchorEdgeP[6].x;
        // anc.y = (latticeData.anchorP.y<latticeData.anchorEdgeP[6].y) ? latticeData.anchorP.y:latticeData.anchorEdgeP[6].y;
        // anc.z = (latticeData.anchorP.z<latticeData.anchorEdgeP[6].z) ? latticeData.anchorP.z:latticeData.anchorEdgeP[6].z;

        texWeight[0][anc.y][anc.x] = {0.5, 0.5, 0.0};
    // }
}
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
        if (rand() % latticeData.anchorTime == 0)
            return {0.5, 0.5, 0.0};
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
            if (latticeData.anchorEdgeP[t] == update)
            {
                return;
            }
        }
        if(latticeData.anchorP == update)
            return;
        if (latticeData.wTex[z][y][x].x > 1.0 || latticeData.wTex[z][y][x].y > 1.0 || latticeData.wTex[z][y][x].z > 1.0 || latticeData.anchorP == update)
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
    destroy_weight_texture(latticeData.typeNum[latticeData.type]);
    // 2. destroy_weight_position input dataset
    destroy_input_position();
    destroy_input_texturea();
}