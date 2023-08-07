#include "world.h"

struct World world = {};



void create_world(SurfaceVoxModel_t  voxelModel) {
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
    world.axis = {
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
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
        }
        if(voxelModel.outerVoxel[i].faceAir[1]){//1
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
        }
        if(voxelModel.outerVoxel[i].faceAir[5]){//5
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 0.0f + z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 0.0f + z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 1.0f + z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 0.0f + z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
        }
        if(voxelModel.outerVoxel[i].faceAir[4]){//4
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 0.0f + z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 1.0f + z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 1.0f + z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 1.0f + z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
        }
        if(voxelModel.outerVoxel[i].faceAir[2]){//2
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 1.0f + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 0.0f + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 1.0f + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.outerVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 1.0f + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
        }
        if(voxelModel.outerVoxel[i].faceAir[3]){//3
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z}, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 0.0f + z}, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 0.0f + z}, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 0.0f + z}, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 1.0f + z}, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.outerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z}, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
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
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
        }
        if(voxelModel.innerVoxel[i].faceAir[1]){//1
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
        }
        if(voxelModel.innerVoxel[i].faceAir[5]){//5
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 0.0f + z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 0.0f + z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 1.0f + z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 0.0f + z}, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
        }
        if(voxelModel.innerVoxel[i].faceAir[4]){//4
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 0.0f + z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 1.0f + z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 1.0f + z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 1.0f + z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z}, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
        }
        if(voxelModel.innerVoxel[i].faceAir[2]){//2
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 1.0f + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 0.0f + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 1.0f + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.innerVoxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 1.0f + z}, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
        }
        if(voxelModel.innerVoxel[i].faceAir[3]){//3
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z}, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 0.0f + z}, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 0.0f + z}, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 0.0f + z}, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 1.0f + z}, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
            world.innerVoxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z}, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
        }
    }


    for(int layer = 0; layer < rawmodel.voxelModel.somChioceLayerNum; layer++){
        world.d_voxel.clear();
        for(int block = 0; block < rawmodel.voxelModel.blockNum; block++){
            world.voxel.clear();
            for(int i = 0;i < voxelModel.num[layer][block]; i++){
                float x = voxelModel.somVoxel[layer][block][i].locate.x;
                float y = voxelModel.somVoxel[layer][block][i].locate.y;
                float z = voxelModel.somVoxel[layer][block][i].locate.z;
                float r = (voxelModel.somVoxel[layer][block][i].color.r);
                float g = (voxelModel.somVoxel[layer][block][i].color.g);
                float b = (voxelModel.somVoxel[layer][block][i].color.b);

                float tx = voxelModel.somVoxel[layer][block][i].texcoord.x;
                float ty = voxelModel.somVoxel[layer][block][i].texcoord.y;
                if(voxelModel.somVoxel[layer][block][i].faceAir[0] && r >= 0.5){//0
                                                //  position                             normal                 color
                    world.voxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                    world.voxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                    world.voxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                    world.voxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                    world.voxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                    world.voxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z}, { 0.0f, 0.0f,-1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                }
                if(voxelModel.somVoxel[layer][block][i].faceAir[1] && r >= 0.5){//1
                    world.voxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                    world.voxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                    world.voxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                    world.voxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                    world.voxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                    world.voxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 1.0f + z}, { 0.0f, 0.0f, 1.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                }
                if(voxelModel.somVoxel[layer][block][i].faceAir[5] && r >= 0.5){//5
                    world.voxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 0.0f + z, }, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                    world.voxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 0.0f + z, }, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                    world.voxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z, }, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                    world.voxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z, }, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                    world.voxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 1.0f + z, }, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                    world.voxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 0.0f + z, }, { 0.0f, 1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                }
                if(voxelModel.somVoxel[layer][block][i].faceAir[4] && r >= 0.5){//4
                    world.voxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z, }, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                    world.voxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 0.0f + z, }, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                    world.voxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 1.0f + z, }, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                    world.voxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 1.0f + z, }, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                    world.voxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 1.0f + z, }, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                    world.voxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z, }, { 0.0f,-1.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                }
                if(voxelModel.somVoxel[layer][block][i].faceAir[2] && r >= 0.5){//2
                    world.voxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 1.0f + z, }, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                    world.voxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 0.0f + z, }, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                    world.voxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z, }, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                    world.voxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 0.0f + z, }, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                    world.voxel.push_back(Vertex{{ 0.0f + x, 0.0f + y, 1.0f + z, }, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                    world.voxel.push_back(Vertex{{ 0.0f + x, 1.0f + y, 1.0f + z, }, {-1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                }
                if(voxelModel.somVoxel[layer][block][i].faceAir[3] && r >= 0.5){//3
                    world.voxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z, }, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                    world.voxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 0.0f + z, }, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                    world.voxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 0.0f + z, }, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                    world.voxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 0.0f + z, }, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                    world.voxel.push_back(Vertex{{ 1.0f + x, 0.0f + y, 1.0f + z, }, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                    world.voxel.push_back(Vertex{{ 1.0f + x, 1.0f + y, 1.0f + z, }, { 1.0f, 0.0f, 0.0f}, {r, g, b}, {tx, ty}, {x, y, z}});
                }

            }
            world.d_voxel.push_back(world.voxel);
        }

        world.somVoxel.push_back(world.d_voxel);
    }

    for(int layer = 0; layer < voxelModel.somChioceLayerNum; layer++){
        world.d_lattice_line.clear();
        world.d_lattice_plane.clear();
        for(int block = 0; block < rawmodel.voxelModel.blockNum; block++){
            world.lattice_line.clear();
            world.lattice_plane.clear();

            const LatData_t* latticeData = som[layer][block].Lattice_get();
            float r = 1.0, g = 1.0, b = 1.0;
            float height = latticeData->height;
            float width = latticeData->width;
            for(int k = 0; k < latticeData->typeNum[latticeData->type]; k++){
                for (int y = 0; y < height-1; y++)
                {
                    for (int x = 0; x < width-1; x++)
                    {
                        float x_tex, x1_tex, y_tex, y1_tex;
                        glm::fvec3 l_pos, l_x_pos, l_y_pos, l_xy_pos;

                        x_tex = (float)x/(float)(width-1);
                        x1_tex = (float)(x+1)/(float)(width-1);
                        y_tex = (float)y/(float)(height-1);
                        y1_tex = (float)(y+1)/(float)(height-1);

                        l_pos = latticeData->lattice[k][y][x];
                        l_x_pos = latticeData->lattice[k][y][x+1];
                        l_y_pos = latticeData->lattice[k][y+1][x];
                        l_xy_pos = latticeData->lattice[k][y+1][x+1];


                        // line
                        world.lattice_line.push_back(Vertex{ {l_pos.x, l_pos.y, l_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x_tex, y_tex}});
                        world.lattice_line.push_back(Vertex{ {l_y_pos.x, l_y_pos.y, l_y_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x_tex, y1_tex}});

                        world.lattice_line.push_back(Vertex{ {l_y_pos.x, l_y_pos.y, l_y_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x_tex, y1_tex}});
                        world.lattice_line.push_back(Vertex{ {l_xy_pos.x, l_xy_pos.y, l_xy_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x1_tex, y1_tex}});

                        world.lattice_line.push_back(Vertex{ {l_xy_pos.x, l_xy_pos.y, l_xy_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x1_tex, y1_tex}});
                        world.lattice_line.push_back(Vertex{ {l_x_pos.x, l_x_pos.y, l_x_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x1_tex, y_tex}});

                        world.lattice_line.push_back(Vertex{ {l_x_pos.x, l_x_pos.y, l_x_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x1_tex, y_tex}});
                        world.lattice_line.push_back(Vertex{ {l_pos.x, l_pos.y, l_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x_tex, y_tex}});

                        // plane

                        world.lattice_plane.push_back(Vertex{ {l_pos.x, l_pos.y, l_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x_tex, y_tex}});
                        world.lattice_plane.push_back(Vertex{ {l_y_pos.x, l_y_pos.y, l_y_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x_tex, y1_tex}});
                        world.lattice_plane.push_back(Vertex{ {l_xy_pos.x, l_xy_pos.y, l_xy_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x1_tex, y1_tex}});

                        world.lattice_plane.push_back(Vertex{ {l_xy_pos.x, l_xy_pos.y, l_xy_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x1_tex, y1_tex}});
                        world.lattice_plane.push_back(Vertex{ {l_x_pos.x, l_x_pos.y, l_x_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x1_tex, y_tex}});
                        world.lattice_plane.push_back(Vertex{ {l_pos.x, l_pos.y, l_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x_tex, y_tex}});

                    }

                }
            }
            world.d_lattice_line.push_back(world.lattice_line);
            world.d_lattice_plane.push_back(world.lattice_plane);

        }
        world.l_lattice_line.push_back(world.d_lattice_line);
        world.l_lattice_plane.push_back(world.d_lattice_plane);
    }

    world.lightcube = {
        //       position
        Vertex{  { 0.0f,  0.0f,  0.0f, }, { 0.0f,  0.0f, -1.0f}, { 1.0f,  1.0f,  1.0f} },
        Vertex{  { 1.0f,  0.0f,  0.0f, }, { 0.0f,  0.0f, -1.0f}, { 1.0f,  1.0f,  1.0f}  },
        Vertex{  { 1.0f,  1.0f,  0.0f, }, { 0.0f,  0.0f, -1.0f}, { 1.0f,  1.0f,  1.0f}  },
        Vertex{  { 1.0f,  1.0f,  0.0f, }, { 0.0f,  0.0f, -1.0f}, { 1.0f,  1.0f,  1.0f}  },
        Vertex{  { 0.0f,  1.0f,  0.0f, }, { 0.0f,  0.0f, -1.0f}, { 1.0f,  1.0f,  1.0f}  },
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
        Vertex{  { 1.0f,  1.0f,  0.0f, }, { 0.0f,  1.0f,  0.0f}, { 1.0f,  1.0f,  1.0f}  },
        Vertex{  { 1.0f,  1.0f,  1.0f, }, { 0.0f,  1.0f,  0.0f}, { 1.0f,  1.0f,  1.0f}  },
        Vertex{  { 1.0f,  1.0f,  1.0f, }, { 0.0f,  1.0f,  0.0f}, { 1.0f,  1.0f,  1.0f}  },
        Vertex{  { 0.0f,  1.0f,  1.0f, }, { 0.0f,  1.0f,  0.0f}, { 1.0f,  1.0f,  1.0f}  },
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
void renew_voxel(SurfaceVoxModel_t voxelModel){
    world.somVoxel.clear();

    for(int layer = 0; layer < voxelModel.somChioceLayerNum; layer++){
        world.d_voxel.clear();
        for(int block = 0; block < voxelModel.blockNum; block++){
            world.voxel.clear();
            for(int i = 0;i < voxelModel.num[layer][block]; i++){
                int x = voxelModel.somVoxel[layer][block][i].locate.x;
                int y = voxelModel.somVoxel[layer][block][i].locate.y;
                int z = voxelModel.somVoxel[layer][block][i].locate.z;
                float r = voxelModel.somVoxel[layer][block][i].color.r;
                float g = voxelModel.somVoxel[layer][block][i].color.g;
                float b = voxelModel.somVoxel[layer][block][i].color.b;

                float tx = voxelModel.somVoxel[layer][block][i].texcoord.x;
                float ty = voxelModel.somVoxel[layer][block][i].texcoord.y;

                if(voxelModel.somVoxel[layer][block][i].faceAir[0] && r >= 0.5){//0
                    //                              position                             normal                 color
                    world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b}, {tx, ty} });
                    world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b}, {tx, ty} });
                    world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b}, {tx, ty} });
                    world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b}, {tx, ty} });
                    world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b}, {tx, ty} });
                    world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b}, {tx, ty} });
                }
                if(voxelModel.somVoxel[layer][block][i].faceAir[1] && r >= 0.5){//1
                    world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b}, {tx, ty} });
                    world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b}, {tx, ty} });
                    world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b}, {tx, ty} });
                    world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b}, {tx, ty} });
                    world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b}, {tx, ty} });
                    world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b}, {tx, ty} });
                }
                if(voxelModel.somVoxel[layer][block][i].faceAir[5] && r >= 0.5){//5
                    world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  1.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  1.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  1.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  1.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  1.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  1.0f,  0.0f}, { r, g, b}, {tx, ty} });
                }
                if(voxelModel.somVoxel[layer][block][i].faceAir[4] && r >= 0.5){//4
                    world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b}, {tx, ty} });
                }
                if(voxelModel.somVoxel[layer][block][i].faceAir[2] && r >= 0.5){//2
                    world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  1.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  0.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  1.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  1.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
                }
                if(voxelModel.somVoxel[layer][block][i].faceAir[3] && r >= 0.5){//3
                    world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  0.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  0.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  0.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  1.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
                    world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
                }

            }
            world.d_voxel.push_back(world.voxel);
        }
        world.somVoxel.push_back(world.d_voxel);

    }

}
void renew_world(int layerNum, int blockNum, MatrixStack texture_m){
    world.l_lattice_line.clear();
    world.l_lattice_plane.clear();

    for(int layer = 0; layer < layerNum; layer++){
        world.d_lattice_line.clear();
        world.d_lattice_plane.clear();
        for(int block = 0; block < blockNum; block++){
            world.lattice_line.clear();
            world.lattice_plane.clear();

            const LatData_t* latticeData = som[layer][block].Lattice_get();
            float r = 1.0, g = 1.0, b = 1.0;
            float height = latticeData->height;
            float width = latticeData->width;
            for(int k = 0; k < latticeData->typeNum[latticeData->type]; k++){
                for (int y = 0; y < height-1; y++)
                {
                    // cout << "\n";
                    for (int x = 0; x < width-1; x++)
                    {
                        float x_tex, x1_tex, y_tex, y1_tex;
                        glm::fvec3 l_pos, l_x_pos, l_y_pos, l_xy_pos;

                        x_tex = (float)x/(float)(width-1);
                        x1_tex = (float)(x+1)/(float)(width-1);
                        y_tex = (float)y/(float)(height-1);
                        y1_tex = (float)(y+1)/(float)(height-1);

                        l_pos = latticeData->lattice[k][y][x];
                        l_x_pos = latticeData->lattice[k][y][x+1];
                        l_y_pos = latticeData->lattice[k][y+1][x];
                        l_xy_pos = latticeData->lattice[k][y+1][x+1];

                        glm::fvec2 texCoord = tex.compute_voxel_texture(texture_m, glm::fvec4(x_tex, y_tex, 0.0, 1.0));
                        glm::fvec2 texCoord_n = tex.compute_voxel_texture(texture_m, glm::fvec4(x1_tex, y1_tex, 0.0, 1.0));
                        x_tex = texCoord[0];
                        y_tex = texCoord[1];
                        x1_tex = texCoord_n[0];
                        y1_tex = texCoord_n[1];

                        // line
                        world.lattice_line.push_back(Vertex{ {l_pos.x, l_pos.y, l_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x_tex, y_tex}});
                        world.lattice_line.push_back(Vertex{ {l_y_pos.x, l_y_pos.y, l_y_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x_tex, y1_tex}});

                        world.lattice_line.push_back(Vertex{ {l_y_pos.x, l_y_pos.y, l_y_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x_tex, y1_tex}});
                        world.lattice_line.push_back(Vertex{ {l_xy_pos.x, l_xy_pos.y, l_xy_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x1_tex, y1_tex}});

                        world.lattice_line.push_back(Vertex{ {l_xy_pos.x, l_xy_pos.y, l_xy_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x1_tex, y1_tex}});
                        world.lattice_line.push_back(Vertex{ {l_x_pos.x, l_x_pos.y, l_x_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x1_tex, y_tex}});

                        world.lattice_line.push_back(Vertex{ {l_x_pos.x, l_x_pos.y, l_x_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x1_tex, y_tex}});
                        world.lattice_line.push_back(Vertex{ {l_pos.x, l_pos.y, l_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x_tex, y_tex}});

                        // plane

                        world.lattice_plane.push_back(Vertex{ {l_pos.x, l_pos.y, l_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x_tex, y_tex}});
                        world.lattice_plane.push_back(Vertex{ {l_y_pos.x, l_y_pos.y, l_y_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x_tex, y1_tex}});
                        world.lattice_plane.push_back(Vertex{ {l_xy_pos.x, l_xy_pos.y, l_xy_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x1_tex, y1_tex}});

                        world.lattice_plane.push_back(Vertex{ {l_xy_pos.x, l_xy_pos.y, l_xy_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x1_tex, y1_tex}});
                        world.lattice_plane.push_back(Vertex{ {l_x_pos.x, l_x_pos.y, l_x_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x1_tex, y_tex}});
                        world.lattice_plane.push_back(Vertex{ {l_pos.x, l_pos.y, l_pos.z}, {0.0f, 0.0f, 0.0f}, {r, g, b}, {x_tex, y_tex}});

                    }

                }
            }
            world.d_lattice_line.push_back(world.lattice_line);
            world.d_lattice_plane.push_back(world.lattice_plane);

        }
        world.l_lattice_line.push_back(world.d_lattice_line);
        world.l_lattice_plane.push_back(world.d_lattice_plane);
    }
}
void destroy_world() {
    world.square.clear();
    world.voxel.clear();
    world.d_voxel.clear();
    world.somVoxel.clear();
    world.innerVoxel.clear();
    world.outerVoxel.clear();
    world.lightcube.clear();
    world.cube.clear();
    world.lattice_line.clear();
    world.d_lattice_line.clear();
    world.l_lattice_line.clear();
    world.lattice_plane.clear();
    world.d_lattice_plane.clear();
    world.l_lattice_plane.clear();
    world.axis.clear();
}