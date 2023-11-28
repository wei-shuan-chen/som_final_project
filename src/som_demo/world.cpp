#include "world.h"

struct World world = {};



void create_world(svoxModel_t  voxelModel, psvoxModel_t pvoxelModel) {
    world.cube = {
        //       position                  normal                 color               tex
        Vertex{  { 0.0f,  0.0f,  0.0f, } , { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.0, 0.0} },
        Vertex{  { 0.0f,  1.0f,  0.0f, } , { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.0, 1.0} },
        Vertex{  { 1.0f,  1.0f,  0.0f, } , { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {1.0, 1.0} },
        Vertex{  { 1.0f,  1.0f,  0.0f, } , { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {1.0, 1.0} },
        Vertex{  { 1.0f,  0.0f,  0.0f, } , { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {1.0, 0.0} },
        Vertex{  { 0.0f,  0.0f,  0.0f, } , { 0.0f,  0.0f, -1.0f}, {1.0f, 1.0f, 1.0f}, {0.0, 0.0} },

        Vertex{  { 0.0f,  0.0f,  1.0f, } , { 0.0f,  0.0f,  1.0f}, {1.0f, 1.0f, 1.0f}, {0.0, 0.0} },
        Vertex{  { 1.0f,  0.0f,  1.0f, } , { 0.0f,  0.0f,  1.0f}, {1.0f, 1.0f, 1.0f}, {1.0, 0.0} },
        Vertex{  { 1.0f,  1.0f,  1.0f, } , { 0.0f,  0.0f,  1.0f}, {1.0f, 1.0f, 1.0f}, {1.0, 1.0} },
        Vertex{  { 1.0f,  1.0f,  1.0f, } , { 0.0f,  0.0f,  1.0f}, {1.0f, 1.0f, 1.0f}, {1.0, 1.0} },
        Vertex{  { 0.0f,  1.0f,  1.0f, } , { 0.0f,  0.0f,  1.0f}, {1.0f, 1.0f, 1.0f}, {0.0, 1.0} },
        Vertex{  { 0.0f,  0.0f,  1.0f, } , { 0.0f,  0.0f,  1.0f}, {1.0f, 1.0f, 1.0f}, {0.0, 0.0} },

        Vertex{  { 0.0f,  1.0f,  1.0f, } , {-1.0f,  0.0f,  0.0f}, {1.0f, 1.0f, 1.0f}, {1.0, 1.0} },
        Vertex{  { 0.0f,  1.0f,  0.0f, } , {-1.0f,  0.0f,  0.0f}, {1.0f, 1.0f, 1.0f}, {1.0, 0.0} },
        Vertex{  { 0.0f,  0.0f,  0.0f, } , {-1.0f,  0.0f,  0.0f}, {1.0f, 1.0f, 1.0f}, {0.0, 0.0} },
        Vertex{  { 0.0f,  0.0f,  0.0f, } , {-1.0f,  0.0f,  0.0f}, {1.0f, 1.0f, 1.0f}, {0.0, 0.0} },
        Vertex{  { 0.0f,  0.0f,  1.0f, } , {-1.0f,  0.0f,  0.0f}, {1.0f, 1.0f, 1.0f}, {0.0, 1.0} },
        Vertex{  { 0.0f,  1.0f,  1.0f, } , {-1.0f,  0.0f,  0.0f}, {1.0f, 1.0f, 1.0f}, {1.0, 1.0} },

        Vertex{  { 1.0f,  1.0f,  1.0f, } , { 1.0f,  0.0f,  0.0f}, {1.0f, 1.0f, 1.0f}, {1.0, 1.0} },
        Vertex{  { 1.0f,  0.0f,  1.0f, } , { 1.0f,  0.0f,  0.0f}, {1.0f, 1.0f, 1.0f}, {0.0, 1.0} },
        Vertex{  { 1.0f,  0.0f,  0.0f, } , { 1.0f,  0.0f,  0.0f}, {1.0f, 1.0f, 1.0f}, {0.0, 0.0} },
        Vertex{  { 1.0f,  0.0f,  0.0f, } , { 1.0f,  0.0f,  0.0f}, {1.0f, 1.0f, 1.0f}, {0.0, 0.0} },
        Vertex{  { 1.0f,  1.0f,  0.0f, } , { 1.0f,  0.0f,  0.0f}, {1.0f, 1.0f, 1.0f}, {1.0, 0.0} },
        Vertex{  { 1.0f,  1.0f,  1.0f, } , { 1.0f,  0.0f,  0.0f}, {1.0f, 1.0f, 1.0f}, {1.0, 1.0} },

        Vertex{  { 0.0f,  0.0f,  0.0f, } , { 0.0f, -1.0f,  0.0f}, {1.0f, 1.0f, 1.0f}, {0.0, 0.0} },
        Vertex{  { 1.0f,  0.0f,  0.0f, } , { 0.0f, -1.0f,  0.0f}, {1.0f, 1.0f, 1.0f}, {1.0, 0.0} },
        Vertex{  { 1.0f,  0.0f,  1.0f, } , { 0.0f, -1.0f,  0.0f}, {1.0f, 1.0f, 1.0f}, {1.0, 1.0} },
        Vertex{  { 1.0f,  0.0f,  1.0f, } , { 0.0f, -1.0f,  0.0f}, {1.0f, 1.0f, 1.0f}, {1.0, 1.0} },
        Vertex{  { 0.0f,  0.0f,  1.0f, } , { 0.0f, -1.0f,  0.0f}, {1.0f, 1.0f, 1.0f}, {0.0, 1.0} },
        Vertex{  { 0.0f,  0.0f,  0.0f, } , { 0.0f, -1.0f,  0.0f}, {1.0f, 1.0f, 1.0f}, {0.0, 0.0} },

        Vertex{  { 0.0f,  1.0f,  0.0f, } , { 0.0f,  1.0f,  0.0f}, {1.0f, 1.0f, 1.0f}, {0.0, 0.0} },
        Vertex{  { 0.0f,  1.0f,  1.0f, } , { 0.0f,  1.0f,  0.0f}, {1.0f, 1.0f, 1.0f}, {0.0, 1.0} },
        Vertex{  { 1.0f,  1.0f,  1.0f, } , { 0.0f,  1.0f,  0.0f}, {1.0f, 1.0f, 1.0f}, {1.0, 1.0} },
        Vertex{  { 1.0f,  1.0f,  1.0f, } , { 0.0f,  1.0f,  0.0f}, {1.0f, 1.0f, 1.0f}, {1.0, 1.0} },
        Vertex{  { 1.0f,  1.0f,  0.0f, } , { 0.0f,  1.0f,  0.0f}, {1.0f, 1.0f, 1.0f}, {1.0, 0.0} },
        Vertex{  { 0.0f,  1.0f,  0.0f, } , { 0.0f,  1.0f,  0.0f}, {1.0f, 1.0f, 1.0f}, {0.0, 0.0} },
    };

    world.axis = world.p_axis = {
        // x
        Vertex{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0}},
        Vertex{{1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0}},
        // y
        Vertex{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0}},
        Vertex{{0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0}},
        // z
        Vertex{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0}},
        Vertex{{0.0, 0.0, 1.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0}},
    };

    for(int i = 0; i < voxelModel.outerVoxel.size(); i++){
        float x = voxelModel.outerVoxel[i].locate.x;
        float y = voxelModel.outerVoxel[i].locate.y;
        float z = voxelModel.outerVoxel[i].locate.z;

        float r = voxelModel.outerVoxel[i].color.r;
        float g = voxelModel.outerVoxel[i].color.g;
        float b = voxelModel.outerVoxel[i].color.b;

        float tx = voxelModel.outerVoxel[i].texcoord.x;
        float ty = voxelModel.outerVoxel[i].texcoord.y;

        if(voxelModel.outerVoxel[i].faceAir[0]){
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty} });
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty} });
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty} });
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty} });
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty} });
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty} });
        }
        if(voxelModel.outerVoxel[i].faceAir[1]){//1
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty} });
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty} });
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty} });
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty} });
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty} });
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty} });
        }
        if(voxelModel.outerVoxel[i].faceAir[5]){//5
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 0.0f + z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 0.0f + z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 1.0f + z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 0.0f + z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty} });
        }
        if(voxelModel.outerVoxel[i].faceAir[4]){//4
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 0.0f + z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 1.0f + z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 1.0f + z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 1.0f + z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty} });
        }
        if(voxelModel.outerVoxel[i].faceAir[2]){//2
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 1.0f + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 0.0f + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 1.0f + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 1.0f + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty} });
        }
        if(voxelModel.outerVoxel[i].faceAir[3]){//3
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z}, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 0.0f + z}, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 0.0f + z}, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 0.0f + z}, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 1.0f + z}, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z}, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty} });
        }
    }
    for(int i = 0; i < voxelModel.innerVoxel.size(); i++){
        float x = voxelModel.innerVoxel[i].locate.x;
        float y = voxelModel.innerVoxel[i].locate.y;
        float z = voxelModel.innerVoxel[i].locate.z;

        float r = voxelModel.innerVoxel[i].color.r;
        float g = voxelModel.innerVoxel[i].color.g;
        float b = voxelModel.innerVoxel[i].color.b;

        float tx = voxelModel.innerVoxel[i].texcoord.x;
        float ty = voxelModel.innerVoxel[i].texcoord.y;


        if(voxelModel.innerVoxel[i].faceAir[0]){
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty} });
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty} });
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty} });
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty} });
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty} });
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty} });
        }
        if(voxelModel.innerVoxel[i].faceAir[1]){//1
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty} });
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty} });
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty} });
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty} });
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty} });
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty} });
        }
        if(voxelModel.innerVoxel[i].faceAir[5]){//5
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 0.0f + z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 0.0f + z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 1.0f + z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 0.0f + z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty} });
        }
        if(voxelModel.innerVoxel[i].faceAir[4]){//4
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 0.0f + z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 1.0f + z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 1.0f + z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 1.0f + z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty} });
        }
        if(voxelModel.innerVoxel[i].faceAir[2]){//2
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 1.0f + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 0.0f + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 1.0f + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 1.0f + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty} });
        }
        if(voxelModel.innerVoxel[i].faceAir[3]){//3
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z}, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 0.0f + z}, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 0.0f + z}, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 0.0f + z}, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 1.0f + z}, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty} });
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z}, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty} });
        }
    }
    renew_pvoxel(pvoxelModel);
    renew_voxel(voxelModel);
    renew_plattice();
    renew_lattice(voxelModel.somChioceLayerNum, voxelModel.blockNum);

    world.lightcube = {
        //       position
        Vertex{  { 0.0f,  0.0f,  0.0f, }, { 0.0f,  0.0f, -1.0f}, { 1.0f,  1.0f,  1.0f} },
        Vertex{  { 0.0f,  1.0f,  0.0f, }, { 0.0f,  0.0f, -1.0f}, { 1.0f,  1.0f,  1.0f}  },
        Vertex{  { 1.0f,  1.0f,  0.0f, }, { 0.0f,  0.0f, -1.0f}, { 1.0f,  1.0f,  1.0f}  },
        Vertex{  { 1.0f,  1.0f,  0.0f, }, { 0.0f,  0.0f, -1.0f}, { 1.0f,  1.0f,  1.0f}  },
        Vertex{  { 1.0f,  0.0f,  0.0f, }, { 0.0f,  0.0f, -1.0f}, { 1.0f,  1.0f,  1.0f}  },
        Vertex{  { 0.0f,  0.0f,  0.0f, }, { 0.0f,  0.0f, -1.0f}, { 1.0f,  1.0f,  1.0f}  },

        Vertex{  { 0.0f,  0.0f,  1.0f, }, { 0.0f,  0.0f,  1.0f}, { 1.0f,  1.0f,  1.0f}  },
        Vertex{  { 1.0f,  0.0f,  1.0f, }, { 0.0f,  0.0f,  1.0f}, { 1.0f,  1.0f,  1.0f}  },
        Vertex{  { 1.0f,  1.0f,  1.0f, }, { 0.0f,  0.0f,  1.0f}, { 1.0f,  1.0f,  1.0f}  },
        Vertex{  { 1.0f,  1.0f,  1.0f, }, { 0.0f,  0.0f,  1.0f}, { 1.0f,  1.0f,  1.0f}  },
        Vertex{  { 0.0f,  1.0f,  1.0f, }, { 0.0f,  0.0f,  1.0f}, { 1.0f,  1.0f,  1.0f}  },
        Vertex{  { 0.0f,  0.0f,  1.0f, }, { 0.0f,  0.0f,  1.0f}, { 1.0f,  1.0f,  1.0f}  },

        Vertex{  { 0.0f,  1.0f,  1.0f, }, {-1.0f,  0.0f,  0.0f}, { 1.0f,  1.0f,  1.0f}  },
        Vertex{  { 0.0f,  1.0f,  0.0f, }, {-1.0f,  0.0f,  0.0f}, { 1.0f,  1.0f,  1.0f}  },
        Vertex{  { 0.0f,  0.0f,  0.0f, }, {-1.0f,  0.0f,  0.0f}, { 1.0f,  1.0f,  1.0f}  },
        Vertex{  { 0.0f,  0.0f,  0.0f, }, {-1.0f,  0.0f,  0.0f}, { 1.0f,  1.0f,  1.0f}  },
        Vertex{  { 0.0f,  0.0f,  1.0f, }, {-1.0f,  0.0f,  0.0f}, { 1.0f,  1.0f,  1.0f}  },
        Vertex{  { 0.0f,  1.0f,  1.0f, }, {-1.0f,  0.0f,  0.0f}, { 1.0f,  1.0f,  1.0f}  },

        Vertex{  { 1.0f,  1.0f,  1.0f, }, { 1.0f,  0.0f,  0.0f}, { 1.0f,  1.0f,  1.0f}  },
        Vertex{  { 1.0f,  1.0f,  0.0f, }, { 1.0f,  0.0f,  0.0f}, { 1.0f,  1.0f,  1.0f}  },
        Vertex{  { 1.0f,  0.0f,  0.0f, }, { 1.0f,  0.0f,  0.0f}, { 1.0f,  1.0f,  1.0f}  },
        Vertex{  { 1.0f,  0.0f,  0.0f, }, { 1.0f,  0.0f,  0.0f}, { 1.0f,  1.0f,  1.0f}  },
        Vertex{  { 1.0f,  0.0f,  1.0f, }, { 1.0f,  0.0f,  0.0f}, { 1.0f,  1.0f,  1.0f}  },
        Vertex{  { 1.0f,  1.0f,  1.0f, }, { 1.0f,  0.0f,  0.0f}, { 1.0f,  1.0f,  1.0f}  },

        Vertex{  { 0.0f,  0.0f,  0.0f, }, { 0.0f, -1.0f,  0.0f}, { 1.0f,  1.0f,  1.0f}  },
        Vertex{  { 1.0f,  0.0f,  0.0f, }, { 0.0f, -1.0f,  0.0f}, { 1.0f,  1.0f,  1.0f}  },
        Vertex{  { 1.0f,  0.0f,  1.0f, }, { 0.0f, -1.0f,  0.0f}, { 1.0f,  1.0f,  1.0f}  },
        Vertex{  { 1.0f,  0.0f,  1.0f, }, { 0.0f, -1.0f,  0.0f}, { 1.0f,  1.0f,  1.0f}  },
        Vertex{  { 0.0f,  0.0f,  1.0f, }, { 0.0f, -1.0f,  0.0f}, { 1.0f,  1.0f,  1.0f}  },
        Vertex{  { 0.0f,  0.0f,  0.0f, }, { 0.0f, -1.0f,  0.0f}, { 1.0f,  1.0f,  1.0f}  },

        Vertex{  { 0.0f,  1.0f,  0.0f, }, { 0.0f,  1.0f,  0.0f}, { 1.0f,  1.0f,  1.0f}  },
        Vertex{  { 0.0f,  1.0f,  1.0f, }, { 0.0f,  1.0f,  0.0f}, { 1.0f,  1.0f,  1.0f}  },
        Vertex{  { 1.0f,  1.0f,  1.0f, }, { 0.0f,  1.0f,  0.0f}, { 1.0f,  1.0f,  1.0f}  },
        Vertex{  { 1.0f,  1.0f,  1.0f, }, { 0.0f,  1.0f,  0.0f}, { 1.0f,  1.0f,  1.0f}  },
        Vertex{  { 1.0f,  1.0f,  0.0f, }, { 0.0f,  1.0f,  0.0f}, { 1.0f,  1.0f,  1.0f}  },
        Vertex{  { 0.0f,  1.0f,  0.0f, }, { 0.0f,  1.0f,  0.0f}, { 1.0f,  1.0f,  1.0f}  },
    };

    world.square = {
            Vertex{ { 0.0f, 0.0f, 0.0f}, { 0.0f,  1.0f,  0.0f}, {0.15f, 0.1f, 0.59f}, {0.0f, 0.0f}},
            Vertex{ { 0.0f, 0.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}, {0.15f, 0.1f, 0.59f}, {0.0f, 1.0f}},
            Vertex{ { 1.0f, 0.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}, {0.15f, 0.1f, 0.59f}, {1.0f, 1.0f}},

            Vertex{ { 1.0f, 0.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}, {0.15f, 0.1f, 0.59f}, {1.0f, 1.0f}},
            Vertex{ { 1.0f, 0.0f, 0.0f}, { 0.0f,  1.0f,  0.0f}, {0.15f, 0.1f, 0.59f}, {1.0f, 0.0f}},
            Vertex{ { 0.0f, 0.0f, 0.0f}, { 0.0f,  1.0f,  0.0f}, {0.15f, 0.1f, 0.59f}, {0.0f, 0.0f}},
    };

}
void renew_paxis(glm::mat3x3 A, glm::vec3 t){
    world.p_axis.clear();
    world.p_axis = {
        // x
        Vertex{{t.x, t.y, t.z}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0}},
        Vertex{{t.x+A[0][0], t.y+A[1][0], t.z+A[2][0]}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0}, {0.0, 0.0}},
        // y
        Vertex{{t.x, t.y, t.z}, {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0}},
        Vertex{{t.x+A[0][1], t.y+A[1][1], t.z+A[2][1]}, {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0}},
        // z
        Vertex{{t.x, t.y, t.z}, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0}},
        Vertex{{t.x+A[0][2], t.y+A[1][2], t.z+A[2][2]}, {0.0, 0.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0}},
    };
}
void renew_voxel(svoxModel_t voxelModel){
    world.somVoxel.clear();
    std::vector<Vertex> voxel;
    std::vector<std::vector<Vertex>> d_voxel;
    for(int layer = 0; layer < voxelModel.somChioceLayerNum; layer++){
        d_voxel.clear();
        for(int block = 0; block < voxelModel.blockNum; block++){
            voxel.clear();
            // cout <<"surface voxel num : "<<layer<<", "<<block<<" : "<< voxelModel.voxelnum[layer][block] << endl;
            for(int i = 0;i < voxelModel.voxelnum[layer][block]; i++){
                int x = voxelModel.somVoxel[layer][block][i].locate.x;
                int y = voxelModel.somVoxel[layer][block][i].locate.y;
                int z = voxelModel.somVoxel[layer][block][i].locate.z;
                float r = voxelModel.somVoxel[layer][block][i].color.r;
                float g = voxelModel.somVoxel[layer][block][i].color.g;
                float b = voxelModel.somVoxel[layer][block][i].color.b;

                float tx = voxelModel.somVoxel[layer][block][i].texcoord.x;
                float ty = voxelModel.somVoxel[layer][block][i].texcoord.y;

                if(voxelModel.somVoxel[layer][block][i].faceAir[0] && r > 0.5){//0
                    //                              position                             normal                 color
                    voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b}, {tx, ty} });
                    voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b}, {tx, ty} });
                    voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b}, {tx, ty} });
                    voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b}, {tx, ty} });
                    voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b}, {tx, ty} });
                    voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b}, {tx, ty} });
                }
                if(voxelModel.somVoxel[layer][block][i].faceAir[1] && r > 0.5){//1
                    voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b}, {tx, ty} });
                    voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b}, {tx, ty} });
                    voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b}, {tx, ty} });
                    voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b}, {tx, ty} });
                    voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b}, {tx, ty} });
                    voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b}, {tx, ty} });
                }
                if(voxelModel.somVoxel[layer][block][i].faceAir[5] && r > 0.5){//5
                    voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  1.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  1.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  1.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  1.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  1.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  1.0f,  0.0f}, { r, g, b}, {tx, ty} });
                }
                if(voxelModel.somVoxel[layer][block][i].faceAir[4] && r > 0.5){//4
                    voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b}, {tx, ty} });
                }
                if(voxelModel.somVoxel[layer][block][i].faceAir[2] && r > 0.5){//2
                    voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  1.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  0.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  1.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  1.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
                }
                if(voxelModel.somVoxel[layer][block][i].faceAir[3] && r > 0.5){//3
                    voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  0.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  0.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  0.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  1.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
                }

            }
            d_voxel.push_back(voxel);
        }
        world.somVoxel.push_back(d_voxel);

    }

}
void renew_pvoxel(psvoxModel_t voxelModel){
    world.psomVoxel.clear();
    for(int i = 0; i < voxelModel.psomVoxel.size(); i++){
        // if(i < 54439 || i >= 54440) continue;
        float x = voxelModel.psomVoxel[i].locate.x;
        float y = voxelModel.psomVoxel[i].locate.y;
        float z = voxelModel.psomVoxel[i].locate.z;

        float r = voxelModel.psomVoxel[i].color.r;
        float g = voxelModel.psomVoxel[i].color.g;
        float b = voxelModel.psomVoxel[i].color.b;

        float tx = voxelModel.psomVoxel[i].texcoord.x;
        float ty = voxelModel.psomVoxel[i].texcoord.y;
        float tz = voxelModel.psomVoxel[i].texcoord.z;

        if(b>=0.5 ){
            world.psomVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty, tz} });
            world.psomVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty, tz} });
            world.psomVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty, tz} });
            world.psomVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty, tz} });
            world.psomVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty, tz} });
            world.psomVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty, tz} });
        }
        if(b>=0.5 ){//1
            world.psomVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty, tz} });
            world.psomVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty, tz} });
            world.psomVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty, tz} });
            world.psomVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty, tz} });
            world.psomVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty, tz} });
            world.psomVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty, tz} });
        }
        if(b>=0.5 ){//5
            world.psomVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 0.0f + z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty, tz} });
            world.psomVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 1.0f + z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty, tz} });
            world.psomVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty, tz} });
            world.psomVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty, tz} });
            world.psomVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 0.0f + z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty, tz} });
            world.psomVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 0.0f + z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty, tz} });
        }
        if(b>=0.5){//4
            world.psomVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty, tz} });
            world.psomVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 0.0f + z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty, tz} });
            world.psomVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 1.0f + z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty, tz} });
            world.psomVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 1.0f + z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty, tz} });
            world.psomVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 1.0f + z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty, tz} });
            world.psomVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty, tz} });
        }
        if(b>=0.5 ){//2
            world.psomVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 1.0f + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty, tz} });
            world.psomVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 0.0f + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty, tz} });
            world.psomVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty, tz} });
            world.psomVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty, tz} });
            world.psomVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 1.0f + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty, tz} });
            world.psomVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 1.0f + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty, tz} });
        }
        if(b>=0.5 ){//3
            world.psomVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z}, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty, tz} });
            world.psomVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 0.0f + z}, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty, tz} });
            world.psomVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 0.0f + z}, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty, tz} });
            world.psomVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 0.0f + z}, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty, tz} });
            world.psomVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 1.0f + z}, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty, tz} });
            world.psomVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z}, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty, tz} });
        }
    }

}
void renew_plattice(){
    world.ps_lattice_line.clear();
    world.ps_lattice_plane.clear();
    const LatData_t* latticeData = psom.Lattice_get();
    float r = 1.0, g = 1.0, b = 1.0;//r = 0.8902, g = 0.6471, b = 0.69;
    float height = latticeData->height;
    float width = latticeData->width;
    float depth = latticeData->depth;
    for(int d = 0; d < depth-1; d++){
        for(int h = 0; h < height-1; h++){
            for(int w = 0; w < width-1; w++){
                float x_tex, x1_tex, y_tex, y1_tex, z_tex, z1_tex ;
                glm::fvec3 l_pos, l_x_pos, l_y_pos, l_z_pos, l_xy_pos, l_yz_pos, l_xz_pos, l_xyz_pos;

                x_tex = (float)w/(float)(width-1);
                x1_tex = (float)(w+1)/(float)(width-1);
                y_tex = (float)h/(float)(height-1);
                y1_tex = (float)(h+1)/(float)(height-1);
                z_tex = (float)d/(float)(depth-1);
                z1_tex = (float)(d+1)/(float)(depth-1);

                l_pos = latticeData->lattice[d][h][w];
                l_x_pos = latticeData->lattice[d][h][w+1];
                l_y_pos = latticeData->lattice[d][h+1][w];
                l_z_pos = latticeData->lattice[d+1][h][w];
                l_xy_pos = latticeData->lattice[d][h+1][w+1];
                l_yz_pos = latticeData->lattice[d+1][h+1][w];
                l_xz_pos = latticeData->lattice[d+1][h][w+1];
                l_xyz_pos = latticeData->lattice[d+1][h+1][w+1];

                // -z
                    world.ps_lattice_line.push_back(Vertex{{ l_pos.x, l_pos.y, l_pos.z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {x_tex, y_tex, z_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_x_pos.x, l_x_pos.y, l_x_pos.z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {x1_tex, y_tex, z_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_x_pos.x, l_x_pos.y, l_x_pos.z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {x1_tex, y_tex, z_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_xy_pos.x, l_xy_pos.y, l_xy_pos.z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {x1_tex, y1_tex, z_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_xy_pos.x, l_xy_pos.y, l_xy_pos.z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {x1_tex, y1_tex, z_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_y_pos.x, l_y_pos.y, l_y_pos.z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {x_tex, y1_tex, z_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_y_pos.x, l_y_pos.y, l_y_pos.z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {x_tex, y1_tex, z_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_pos.x, l_pos.y, l_pos.z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {x_tex, y_tex, z_tex} });

                    world.ps_lattice_plane.push_back(Vertex{{ l_pos.x, l_pos.y, l_pos.z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {x_tex, y_tex, z_tex} });
                    world.ps_lattice_plane.push_back(Vertex{{ l_x_pos.x, l_x_pos.y, l_x_pos.z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {x1_tex, y_tex, z_tex} });
                    world.ps_lattice_plane.push_back(Vertex{{ l_xy_pos.x, l_xy_pos.y, l_xy_pos.z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {x1_tex, y1_tex, z_tex} });
                    world.ps_lattice_plane.push_back(Vertex{{ l_xy_pos.x, l_xy_pos.y, l_xy_pos.z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {x1_tex, y1_tex, z_tex} });
                    world.ps_lattice_plane.push_back(Vertex{{ l_y_pos.x, l_y_pos.y, l_y_pos.z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {x_tex, y1_tex, z_tex} });
                    world.ps_lattice_plane.push_back(Vertex{{ l_pos.x, l_pos.y, l_pos.z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {x_tex, y_tex, z_tex} });
                // +z
                    world.ps_lattice_line.push_back(Vertex{{ l_z_pos.x, l_z_pos.y, l_z_pos.z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {x_tex, y_tex, z1_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_xz_pos.x, l_xz_pos.y, l_xz_pos.z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {x1_tex, y_tex, z1_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_xz_pos.x, l_xz_pos.y, l_xz_pos.z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {x1_tex, y_tex, z1_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_xyz_pos.x, l_xyz_pos.y, l_xyz_pos.z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {x1_tex, y1_tex, z1_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_xyz_pos.x, l_xyz_pos.y, l_xyz_pos.z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {x1_tex, y1_tex, z1_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_yz_pos.x, l_yz_pos.y, l_yz_pos.z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {x_tex, y1_tex, z1_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_yz_pos.x, l_yz_pos.y, l_yz_pos.z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {x_tex, y1_tex, z1_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_z_pos.x, l_z_pos.y, l_z_pos.z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {x_tex, y_tex, z1_tex} });
                    // cout << l_z_pos.x<<", " <<l_z_pos.y<<", " << l_z_pos.z<<" :  " <<x_tex<<", " << y_tex<<", " << z1_tex<<"\n";
                    // cout << l_xz_pos.x<<", " <<l_xz_pos.y<<", " << l_xz_pos.z<<" :  " <<x1_tex<<", " << y_tex<<", " << z1_tex<<"\n";
                    // cout << l_xyz_pos.x<<", " <<l_xyz_pos.y<<", " << l_xyz_pos.z<<" :  " <<x1_tex<<", " << y1_tex<<", " << z1_tex<<"\n\n";
                    // cout << l_xyz_pos.x<<", " <<l_xyz_pos.y<<", " << l_xyz_pos.z<<" :  " <<x1_tex<<", " << y1_tex<<", " << z1_tex<<"\n";
                    // cout << l_yz_pos.x<<", " <<l_yz_pos.y<<", " << l_yz_pos.z<<" :  " <<x_tex<<", " << y1_tex<<", " << z1_tex<<"\n";
                    // cout << l_z_pos.x<<", " <<l_z_pos.y<<", " << l_z_pos.z<<" :  " <<x_tex<<", " << y_tex<<", " << z1_tex<<"\n\n";

                    world.ps_lattice_plane.push_back(Vertex{{ l_z_pos.x, l_z_pos.y, l_z_pos.z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {x_tex, y_tex, z1_tex} });
                    world.ps_lattice_plane.push_back(Vertex{{ l_xz_pos.x, l_xz_pos.y, l_xz_pos.z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {x1_tex, y_tex, z1_tex} });
                    world.ps_lattice_plane.push_back(Vertex{{ l_xyz_pos.x, l_xyz_pos.y, l_xyz_pos.z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {x1_tex, y1_tex, z1_tex} });
                    world.ps_lattice_plane.push_back(Vertex{{ l_xyz_pos.x, l_xyz_pos.y, l_xyz_pos.z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {x1_tex, y1_tex, z1_tex} });
                    world.ps_lattice_plane.push_back(Vertex{{ l_yz_pos.x, l_yz_pos.y, l_yz_pos.z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {x_tex, y1_tex, z1_tex} });
                    world.ps_lattice_plane.push_back(Vertex{{ l_z_pos.x, l_z_pos.y, l_z_pos.z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {x_tex, y_tex, z1_tex} });
                // -y
                    world.ps_lattice_line.push_back(Vertex{{ l_pos.x, l_pos.y, l_pos.z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {x_tex, y_tex, z_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_x_pos.x, l_x_pos.y, l_x_pos.z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {x1_tex, y_tex, z_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_x_pos.x, l_x_pos.y, l_x_pos.z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {x1_tex, y_tex, z_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_xz_pos.x, l_xz_pos.y, l_xz_pos.z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {x1_tex, y_tex, z1_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_xz_pos.x, l_xz_pos.y, l_xz_pos.z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {x1_tex, y_tex, z1_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_z_pos.x, l_z_pos.y, l_z_pos.z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {x_tex, y_tex, z1_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_z_pos.x, l_z_pos.y, l_z_pos.z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {x_tex, y_tex, z1_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_pos.x, l_pos.y, l_pos.z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {x_tex, y_tex, z_tex} });

                    world.ps_lattice_plane.push_back(Vertex{{ l_pos.x, l_pos.y, l_pos.z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {x_tex, y_tex, z_tex} });
                    world.ps_lattice_plane.push_back(Vertex{{ l_x_pos.x, l_x_pos.y, l_x_pos.z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {x1_tex, y_tex, z_tex} });
                    world.ps_lattice_plane.push_back(Vertex{{ l_xz_pos.x, l_xz_pos.y, l_xz_pos.z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {x1_tex, y_tex, z1_tex} });
                    world.ps_lattice_plane.push_back(Vertex{{ l_xz_pos.x, l_xz_pos.y, l_xz_pos.z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {x1_tex, y_tex, z1_tex} });
                    world.ps_lattice_plane.push_back(Vertex{{ l_z_pos.x, l_z_pos.y, l_z_pos.z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {x_tex, y_tex, z1_tex} });
                    world.ps_lattice_plane.push_back(Vertex{{ l_pos.x, l_pos.y, l_pos.z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {x_tex, y_tex, z_tex} });
                // +y
                    world.ps_lattice_line.push_back(Vertex{{ l_y_pos.x, l_y_pos.y, l_y_pos.z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {x_tex, y1_tex, z_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_xy_pos.x, l_xy_pos.y, l_xy_pos.z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {x1_tex, y1_tex, z_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_xy_pos.x, l_xy_pos.y, l_xy_pos.z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {x1_tex, y1_tex, z_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_xyz_pos.x, l_xyz_pos.y, l_xyz_pos.z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {x1_tex, y1_tex, z1_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_xyz_pos.x, l_xyz_pos.y, l_xyz_pos.z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {x1_tex, y1_tex, z1_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_yz_pos.x, l_yz_pos.y, l_yz_pos.z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {x_tex, y1_tex, z1_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_yz_pos.x, l_yz_pos.y, l_yz_pos.z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {x_tex, y1_tex, z1_tex} });
                    world.ps_lattice_line.push_back(Vertex{{l_y_pos.x, l_y_pos.y, l_y_pos.z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {x_tex, y1_tex, z_tex} });

                    world.ps_lattice_plane.push_back(Vertex{{ l_y_pos.x, l_y_pos.y, l_y_pos.z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {x_tex, y1_tex, z_tex} });
                    world.ps_lattice_plane.push_back(Vertex{{ l_yz_pos.x, l_yz_pos.y, l_yz_pos.z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {x_tex, y1_tex, z1_tex} });
                    world.ps_lattice_plane.push_back(Vertex{{ l_xyz_pos.x, l_xyz_pos.y, l_xyz_pos.z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {x1_tex, y1_tex, z1_tex} });
                    world.ps_lattice_plane.push_back(Vertex{{ l_xyz_pos.x, l_xyz_pos.y, l_xyz_pos.z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {x1_tex, y1_tex, z1_tex} });
                    world.ps_lattice_plane.push_back(Vertex{{ l_xy_pos.x, l_xy_pos.y, l_xy_pos.z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {x1_tex, y1_tex, z_tex} });
                    world.ps_lattice_plane.push_back(Vertex{{l_y_pos.x, l_y_pos.y, l_y_pos.z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {x_tex, y1_tex, z_tex} });
                // -x
                    world.ps_lattice_line.push_back(Vertex{{ l_pos.x, l_pos.y, l_pos.z}, { -1.0f, 0.0f,0.0f}, {r, g, b}, {x_tex, y_tex, z_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_y_pos.x, l_y_pos.y, l_y_pos.z}, { -1.0f, 0.0f,0.0f}, {r, g, b}, {x_tex, y1_tex, z_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_y_pos.x, l_y_pos.y, l_y_pos.z}, { -1.0f, 0.0f,0.0f}, {r, g, b}, {x_tex, y1_tex, z_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_yz_pos.x, l_yz_pos.y, l_yz_pos.z}, { -1.0f, 0.0f,0.0f}, {r, g, b}, {x_tex, y1_tex, z1_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_yz_pos.x, l_yz_pos.y, l_yz_pos.z}, { -1.0f, 0.0f,0.0f}, {r, g, b}, {x_tex, y1_tex, z1_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_z_pos.x, l_z_pos.y, l_z_pos.z}, { -1.0f, 0.0f,0.0f}, {r, g, b}, {x_tex, y_tex, z1_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_z_pos.x, l_z_pos.y, l_z_pos.z}, { -1.0f, 0.0f,0.0f}, {r, g, b}, {x_tex, y_tex, z1_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_pos.x, l_pos.y, l_pos.z}, { -1.0f, 0.0f,0.0f}, {r, g, b}, {x_tex, y_tex, z_tex} });

                    world.ps_lattice_plane.push_back(Vertex{{ l_pos.x, l_pos.y, l_pos.z}, { -1.0f, 0.0f,0.0f}, {r, g, b}, {x_tex, y_tex, z_tex} });
                    world.ps_lattice_plane.push_back(Vertex{{ l_z_pos.x, l_z_pos.y, l_z_pos.z}, { -1.0f, 0.0f,0.0f}, {r, g, b}, {x_tex, y_tex, z1_tex} });
                    world.ps_lattice_plane.push_back(Vertex{{ l_yz_pos.x, l_yz_pos.y, l_yz_pos.z}, { -1.0f, 0.0f,0.0f}, {r, g, b}, {x_tex, y1_tex, z1_tex} });
                    world.ps_lattice_plane.push_back(Vertex{{ l_yz_pos.x, l_yz_pos.y, l_yz_pos.z}, { -1.0f, 0.0f,0.0f}, {r, g, b}, {x_tex, y1_tex, z1_tex} });
                    world.ps_lattice_plane.push_back(Vertex{{ l_y_pos.x, l_y_pos.y, l_y_pos.z}, { -1.0f, 0.0f,0.0f}, {r, g, b}, {x_tex, y1_tex, z_tex} });
                    world.ps_lattice_plane.push_back(Vertex{{ l_pos.x, l_pos.y, l_pos.z}, { -1.0f, 0.0f,0.0f}, {r, g, b}, {x_tex, y_tex, z_tex} });
                // +x
                    world.ps_lattice_line.push_back(Vertex{{ l_x_pos.x, l_x_pos.y, l_x_pos.z}, { 1.0f, 0.0f,0.0f}, {r, g, b}, {x1_tex, y_tex, z_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_xy_pos.x, l_xy_pos.y, l_xy_pos.z}, { 1.0f, 0.0f,0.0f}, {r, g, b}, {x1_tex, y1_tex, z_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_xy_pos.x, l_xy_pos.y, l_xy_pos.z}, { 1.0f, 0.0f,0.0f}, {r, g, b}, {x1_tex, y1_tex, z_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_xyz_pos.x, l_xyz_pos.y, l_xyz_pos.z}, { 1.0f, 0.0f,0.0f}, {r, g, b}, {x1_tex, y1_tex, z1_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_xyz_pos.x, l_xyz_pos.y, l_xyz_pos.z}, { 1.0f, 0.0f,0.0f}, {r, g, b}, {x1_tex, y1_tex, z1_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_xz_pos.x, l_xz_pos.y, l_xz_pos.z}, { 1.0f, 0.0f,0.0f}, {r, g, b}, {x1_tex, y_tex, z1_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_xz_pos.x, l_xz_pos.y, l_xz_pos.z}, { 1.0f, 0.0f,0.0f}, {r, g, b}, {x1_tex, y_tex, z1_tex} });
                    world.ps_lattice_line.push_back(Vertex{{ l_x_pos.x, l_x_pos.y, l_x_pos.z}, { 1.0f, 0.0f,0.0f}, {r, g, b}, {x1_tex, y_tex, z_tex} });

                    world.ps_lattice_plane.push_back(Vertex{{ l_x_pos.x, l_x_pos.y, l_x_pos.z}, { 1.0f, 0.0f,0.0f}, {r, g, b}, {x1_tex, y_tex, z_tex} });
                    world.ps_lattice_plane.push_back(Vertex{{ l_xy_pos.x, l_xy_pos.y, l_xy_pos.z}, { 1.0f, 0.0f,0.0f}, {r, g, b}, {x1_tex, y1_tex, z_tex} });
                    world.ps_lattice_plane.push_back(Vertex{{ l_xyz_pos.x, l_xyz_pos.y, l_xyz_pos.z}, { 1.0f, 0.0f,0.0f}, {r, g, b}, {x1_tex, y1_tex, z1_tex} });
                    world.ps_lattice_plane.push_back(Vertex{{ l_xyz_pos.x, l_xyz_pos.y, l_xyz_pos.z}, { 1.0f, 0.0f,0.0f}, {r, g, b}, {x1_tex, y1_tex, z1_tex} });
                    world.ps_lattice_plane.push_back(Vertex{{ l_xz_pos.x, l_xz_pos.y, l_xz_pos.z}, { 1.0f, 0.0f,0.0f}, {r, g, b}, {x1_tex, y_tex, z1_tex} });
                    world.ps_lattice_plane.push_back(Vertex{{ l_x_pos.x, l_x_pos.y, l_x_pos.z}, { 1.0f, 0.0f,0.0f}, {r, g, b}, {x1_tex, y_tex, z_tex} });
            }
        }
    }
}
void renew_lattice(int layerNum, int blockNum){
    world.s_lattice_line.clear();
    world.s_lattice_plane.clear();
    std::vector<Vertex> lattice_line; // lattice
    std::vector<std::vector<Vertex>> d_lattice_line; // lattice
    std::vector<Vertex> lattice_plane; // plane of texture
    std::vector<std::vector<Vertex>> d_lattice_plane; // plane of texture
    for(int layer = 0; layer < layerNum; layer++){
        d_lattice_line.clear();
        d_lattice_plane.clear();
        for(int block = 0; block < blockNum; block++){
            lattice_line.clear();
            lattice_plane.clear();
            const LatData_t* latticeData = som[layer][block].Lattice_get();
            float r = 1.0, g = 1.0, b = 1.0;
            float height = latticeData->height;
            float width = latticeData->width;
            for(int k = 0; k < latticeData->typeNum[latticeData->type]; k++){

                for (int y = 0; y < height-1; y++)
                {

                    for (int x = 0; x < width-1; x++)
                    {
                        float x_tex, x1_tex, y_tex, y1_tex, z_tex, z1_tex ;
                        glm::fvec3 l_pos, l_x_pos, l_y_pos, l_xy_pos;

                        x_tex = (float)x/(float)(width-1);
                        x1_tex = (float)(x+1)/(float)(width-1);
                        y_tex = (float)y/(float)(height-1);
                        y1_tex = (float)(y+1)/(float)(height-1);
                        z_tex = 0.5;
                        z1_tex = 0.5;

                        l_pos = latticeData->lattice[k][y][x];
                        l_x_pos = latticeData->lattice[k][y][x+1];
                        l_y_pos = latticeData->lattice[k][y+1][x];
                        l_xy_pos = latticeData->lattice[k][y+1][x+1];
                        glm::fvec3 texCoord = tex.compute_voxel_texture(glm::fvec4(x_tex, y_tex, z_tex, 1.0));
                        glm::fvec3 texCoord_n = tex.compute_voxel_texture(glm::fvec4(x1_tex, y1_tex, z1_tex, 1.0));
                        x_tex = texCoord[0];
                        y_tex = texCoord[1];
                        z_tex = texCoord[2];

                        x1_tex = texCoord_n[0];
                        y1_tex = texCoord_n[1];
                        z1_tex = texCoord_n[2];
                        // line
                        lattice_line.push_back(Vertex{ {l_pos.x, l_pos.y, l_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x_tex, y_tex, z_tex}});
                        lattice_line.push_back(Vertex{ {l_y_pos.x, l_y_pos.y, l_y_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x_tex, y1_tex, z_tex}});

                        lattice_line.push_back(Vertex{ {l_y_pos.x, l_y_pos.y, l_y_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x_tex, y1_tex, z_tex}});
                        lattice_line.push_back(Vertex{ {l_xy_pos.x, l_xy_pos.y, l_xy_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x1_tex, y1_tex, z_tex}});

                        lattice_line.push_back(Vertex{ {l_xy_pos.x, l_xy_pos.y, l_xy_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x1_tex, y1_tex, z_tex}});
                        lattice_line.push_back(Vertex{ {l_x_pos.x, l_x_pos.y, l_x_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x1_tex, y_tex, z_tex}});

                        lattice_line.push_back(Vertex{ {l_x_pos.x, l_x_pos.y, l_x_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x1_tex, y_tex, z_tex}});
                        lattice_line.push_back(Vertex{ {l_pos.x, l_pos.y, l_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x_tex, y_tex, z_tex}});

                        // plane

                        lattice_plane.push_back(Vertex{ {l_pos.x, l_pos.y, l_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x_tex, y_tex, z_tex}});
                        lattice_plane.push_back(Vertex{ {l_y_pos.x, l_y_pos.y, l_y_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x_tex, y1_tex, z_tex}});
                        lattice_plane.push_back(Vertex{ {l_xy_pos.x, l_xy_pos.y, l_xy_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x1_tex, y1_tex, z_tex}});

                        lattice_plane.push_back(Vertex{ {l_xy_pos.x, l_xy_pos.y, l_xy_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x1_tex, y1_tex, z_tex}});
                        lattice_plane.push_back(Vertex{ {l_x_pos.x, l_x_pos.y, l_x_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x1_tex, y_tex, z_tex}});
                        lattice_plane.push_back(Vertex{ {l_pos.x, l_pos.y, l_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x_tex, y_tex, z_tex}});

                    }
                }
            }
            d_lattice_line.push_back(lattice_line);
            d_lattice_plane.push_back(lattice_plane);

        }
        world.s_lattice_line.push_back(d_lattice_line);
        world.s_lattice_plane.push_back(d_lattice_plane);
    }
}
void destroy_world() {
    world.square.clear();
    world.somVoxel.clear();
    world.innerVoxel.clear();
    world.outerVoxel.clear();
    world.psomVoxel.clear();
    world.lightcube.clear();
    world.cube.clear();
    world.s_lattice_line.clear();
    world.ps_lattice_line.clear();
    world.s_lattice_plane.clear();
    world.ps_lattice_plane.clear();
    world.axis.clear();
}