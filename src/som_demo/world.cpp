#include "world.h"

struct World world = {};



void create_world(SurfaceVoxModel_t  voxelModel) {
    world.cube = {
        //       position                  normal                 color               tex
        Vertex{  { 0.0f,  0.0f,  0.0f, } , { 0.0f,  0.0f, -1.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 0.0} },
        Vertex{  { 1.0f,  0.0f,  0.0f, } , { 0.0f,  0.0f, -1.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 0.0} },
        Vertex{  { 1.0f,  1.0f,  0.0f, } , { 0.0f,  0.0f, -1.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 1.0} },
        Vertex{  { 1.0f,  1.0f,  0.0f, } , { 0.0f,  0.0f, -1.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 1.0} },
        Vertex{  { 0.0f,  1.0f,  0.0f, } , { 0.0f,  0.0f, -1.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 1.0} },
        Vertex{  { 0.0f,  0.0f,  0.0f, } , { 0.0f,  0.0f, -1.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 0.0} },

        Vertex{  { 0.0f,  0.0f,  1.0f, } , { 0.0f,  0.0f,  1.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 0.0} },
        Vertex{  { 1.0f,  0.0f,  1.0f, } , { 0.0f,  0.0f,  1.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 0.0} },
        Vertex{  { 1.0f,  1.0f,  1.0f, } , { 0.0f,  0.0f,  1.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 1.0} },
        Vertex{  { 1.0f,  1.0f,  1.0f, } , { 0.0f,  0.0f,  1.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 1.0} },
        Vertex{  { 0.0f,  1.0f,  1.0f, } , { 0.0f,  0.0f,  1.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 1.0} },
        Vertex{  { 0.0f,  0.0f,  1.0f, } , { 0.0f,  0.0f,  1.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 0.0} },

        Vertex{  { 0.0f,  1.0f,  1.0f, } , {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 1.0} },
        Vertex{  { 0.0f,  1.0f,  0.0f, } , {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 0.0} },
        Vertex{  { 0.0f,  0.0f,  0.0f, } , {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 0.0} },
        Vertex{  { 0.0f,  0.0f,  0.0f, } , {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 0.0} },
        Vertex{  { 0.0f,  0.0f,  1.0f, } , {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 1.0} },
        Vertex{  { 0.0f,  1.0f,  1.0f, } , {-1.0f,  0.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 1.0} },

        Vertex{  { 1.0f,  1.0f,  1.0f, } , { 1.0f,  0.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 1.0} },
        Vertex{  { 1.0f,  1.0f,  0.0f, } , { 1.0f,  0.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 0.0} },
        Vertex{  { 1.0f,  0.0f,  0.0f, } , { 1.0f,  0.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 0.0} },
        Vertex{  { 1.0f,  0.0f,  0.0f, } , { 1.0f,  0.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 0.0} },
        Vertex{  { 1.0f,  0.0f,  1.0f, } , { 1.0f,  0.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 1.0} },
        Vertex{  { 1.0f,  1.0f,  1.0f, } , { 1.0f,  0.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 1.0} },

        Vertex{  { 0.0f,  0.0f,  0.0f, } , { 0.0f, -1.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 0.0} },
        Vertex{  { 1.0f,  0.0f,  0.0f, } , { 0.0f, -1.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 0.0} },
        Vertex{  { 1.0f,  0.0f,  1.0f, } , { 0.0f, -1.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 1.0} },
        Vertex{  { 1.0f,  0.0f,  1.0f, } , { 0.0f, -1.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 1.0} },
        Vertex{  { 0.0f,  0.0f,  1.0f, } , { 0.0f, -1.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 1.0} },
        Vertex{  { 0.0f,  0.0f,  0.0f, } , { 0.0f, -1.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 0.0} },

        Vertex{  { 0.0f,  1.0f,  0.0f, } , { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 0.0} },
        Vertex{  { 1.0f,  1.0f,  0.0f, } , { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 0.0} },
        Vertex{  { 1.0f,  1.0f,  1.0f, } , { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 1.0} },
        Vertex{  { 1.0f,  1.0f,  1.0f, } , { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {1.0, 1.0} },
        Vertex{  { 0.0f,  1.0f,  1.0f, } , { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 1.0} },
        Vertex{  { 0.0f,  1.0f,  0.0f, } , { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f, 1.0f}, {0.0, 0.0} },
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
    // for(int i = 92633; i < 93634; i++){// voxel
    for(int i = 0; i < voxelModel.num; i++){
        int x = voxelModel.voxel[i].locate.x;
        int y = voxelModel.voxel[i].locate.y;
        int z = voxelModel.voxel[i].locate.z;
        float r = voxelModel.voxel[i].color.r;
        float g = voxelModel.voxel[i].color.g;
        float b = voxelModel.voxel[i].color.b;

        float tx = voxelModel.voxel[i].texcoord.x;
        float ty = voxelModel.voxel[i].texcoord.y;
        // for(int air = 0; air < 6; air++){
        //     cout << "voxelnum : " << i << ", faceair : "<<air << ", "<< voxelModel.voxel[i].faceAir[air]<<endl;
        // }
        if(voxelModel.voxel[i].faceAir[0]){//0
            //                              position                             normal                 color
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b}, {tx, ty} });
        }
        if(voxelModel.voxel[i].faceAir[1]){//1
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b}, {tx, ty} });
        }
        if(voxelModel.voxel[i].faceAir[5]){//5
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  1.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  1.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  1.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  1.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  1.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  1.0f,  0.0f}, { r, g, b}, {tx, ty} });
        }
        if(voxelModel.voxel[i].faceAir[4]){//4
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b}, {tx, ty} });
        }
        if(voxelModel.voxel[i].faceAir[2]){//2
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  1.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  0.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  1.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  1.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
        }
        if(voxelModel.voxel[i].faceAir[3]){//3
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  0.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  0.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  0.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  1.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
        }


    }


    const LatData_t* latticeData = som.Lattice_get();

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

    world.lightcube = {
        //       position
        Vertex{  { 0.0f,  0.0f,  0.0f, } },
        Vertex{  { 1.0f,  0.0f,  0.0f, } },
        Vertex{  { 1.0f,  1.0f,  0.0f, } },
        Vertex{  { 1.0f,  1.0f,  0.0f, } },
        Vertex{  { 0.0f,  1.0f,  0.0f, } },
        Vertex{  { 0.0f,  0.0f,  0.0f, } },

        Vertex{  { 0.0f,  0.0f,  1.0f, } },
        Vertex{  { 1.0f,  0.0f,  1.0f, } },
        Vertex{  { 1.0f,  1.0f,  1.0f, } },
        Vertex{  { 1.0f,  1.0f,  1.0f, } },
        Vertex{  { 0.0f,  1.0f,  1.0f, } },
        Vertex{  { 0.0f,  0.0f,  1.0f, } },

        Vertex{  { 0.0f,  1.0f,  1.0f, } },
        Vertex{  { 0.0f,  1.0f,  0.0f, } },
        Vertex{  { 0.0f,  0.0f,  0.0f, } },
        Vertex{  { 0.0f,  0.0f,  0.0f, } },
        Vertex{  { 0.0f,  0.0f,  1.0f, } },
        Vertex{  { 0.0f,  1.0f,  1.0f, } },

        Vertex{  { 1.0f,  1.0f,  1.0f, } },
        Vertex{  { 1.0f,  1.0f,  0.0f, } },
        Vertex{  { 1.0f,  0.0f,  0.0f, } },
        Vertex{  { 1.0f,  0.0f,  0.0f, } },
        Vertex{  { 1.0f,  0.0f,  1.0f, } },
        Vertex{  { 1.0f,  1.0f,  1.0f, } },

        Vertex{  { 0.0f,  0.0f,  0.0f, } },
        Vertex{  { 1.0f,  0.0f,  0.0f, } },
        Vertex{  { 1.0f,  0.0f,  1.0f, } },
        Vertex{  { 1.0f,  0.0f,  1.0f, } },
        Vertex{  { 0.0f,  0.0f,  1.0f, } },
        Vertex{  { 0.0f,  0.0f,  0.0f, } },

        Vertex{  { 0.0f,  1.0f,  0.0f, } },
        Vertex{  { 1.0f,  1.0f,  0.0f, } },
        Vertex{  { 1.0f,  1.0f,  1.0f, } },
        Vertex{  { 1.0f,  1.0f,  1.0f, } },
        Vertex{  { 0.0f,  1.0f,  1.0f, } },
        Vertex{  { 0.0f,  1.0f,  0.0f, } },
    };
    world.square = {
            Vertex{ { 0.0f, 0.0f, 0.0f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
            Vertex{ { 1.0f, 0.0f, 0.0f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
            Vertex{ { 1.0f, 0.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},

            Vertex{ { 1.0f, 0.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
            Vertex{ { 0.0f, 0.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
            Vertex{ { 0.0f, 0.0f, 0.0f}, { 0.0f,  1.0f,  0.0f}, {0.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
    };

}
void renew_voxel_color(SurfaceVoxModel_t voxelModel){
    world.voxel.clear();

    for(int i = 0;i < voxelModel.num; i++){
        int x = voxelModel.voxel[i].locate.x;
        int y = voxelModel.voxel[i].locate.y;
        int z = voxelModel.voxel[i].locate.z;
        float r = (voxelModel.voxel[i].color.r)/256.0;
        float g = (voxelModel.voxel[i].color.g)/256.0;
        float b = (voxelModel.voxel[i].color.b)/256.0;

        float tx = voxelModel.voxel[i].texcoord.x;
        float ty = voxelModel.voxel[i].texcoord.y;

         if(voxelModel.voxel[i].faceAir[0] && r >= 0.5){//0
            //                              position                             normal                 color
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b}, {tx, ty} });
        }
        if(voxelModel.voxel[i].faceAir[1] && r >= 0.5){//1
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b}, {tx, ty} });
        }
        if(voxelModel.voxel[i].faceAir[5] && r >= 0.5){//5
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  1.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  1.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  1.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  1.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  1.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  1.0f,  0.0f}, { r, g, b}, {tx, ty} });
        }
        if(voxelModel.voxel[i].faceAir[4] && r >= 0.5){//4
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b}, {tx, ty} });
        }
        if(voxelModel.voxel[i].faceAir[2] && r >= 0.5){//2
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  1.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  0.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  1.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  1.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
        }
        if(voxelModel.voxel[i].faceAir[3] && r >= 0.5){//3
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  0.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  0.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  0.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  1.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b}, {tx, ty} });
        }

    }
}
void renew_world(){
    world.lattice_line.clear();
    world.lattice_plane.clear();
    const LatData_t* latticeData = som.Lattice_get();

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
}
void destroy_world() {
    world.square.clear();
    world.voxel.clear();
    world.lightcube.clear();
    world.cube.clear();
    world.lattice_line.clear();
    world.lattice_plane.clear();
    world.axis.clear();
}