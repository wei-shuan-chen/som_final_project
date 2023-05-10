#include "world.h"

struct World world = {};



void create_world(std::vector<VoxData_b>  bounderVoxelData, int bounderNum) {
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
    // for(int i = 54890; i < 54900; i++){// voxel
    for(int i = 0; i < bounderNum; i++){
        int x = bounderVoxelData[i].bounderVoxelLocate.x;
        int y = bounderVoxelData[i].bounderVoxelLocate.y;
        int z = bounderVoxelData[i].bounderVoxelLocate.z;
        float r = bounderVoxelData[i].bounderVoxelColor.r;
        float g = bounderVoxelData[i].bounderVoxelColor.g;
        float b = bounderVoxelData[i].bounderVoxelColor.b;
        if(bounderVoxelData[i].bounderVoxelFaceAir[0] == 0){//0
            //                              position                             normal                 color
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b} });
        }
        if(bounderVoxelData[i].bounderVoxelFaceAir[1] == 0){//1
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b} });
        }
        if(bounderVoxelData[i].bounderVoxelFaceAir[4] == 0){//2
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  1.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  0.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  1.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  1.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b} });
        }
        if(bounderVoxelData[i].bounderVoxelFaceAir[5] == 0){//3
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  0.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  0.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  0.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  1.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b} });
        }
        if(bounderVoxelData[i].bounderVoxelFaceAir[2] == 0){//4
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b} });
        }
        if(bounderVoxelData[i].bounderVoxelFaceAir[3] == 0){//5
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  1.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  1.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  1.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  1.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  1.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  1.0f,  0.0f}, {r, g, b} });
        }
    }


    const LatData* latticeData = Lattice_Struct_Use();
    int latticeTime = 1;
    if(latticeData->shapeLattice == 4) latticeTime = 5;
    for(int k = 0; k < latticeTime; k++){
        for (int i = 0; i < latticeData->map_width-1; i++)
        {
            for (int j = 0; j < latticeData->map_height-1; j++)
            {
                float i_tex, i1_tex, j_tex, j1_tex;

                i_tex = (float)i / (float)(latticeData->map_width-1);
                i1_tex = (float)(i+1) / (float)(latticeData->map_width-1);
                j_tex = (float)j / (float)(latticeData->map_width-1);
                j1_tex = (float)(j+1) / (float)(latticeData->map_width-1);


                // line
                world.lattice_line.push_back(Vertex{ {latticeData->lattice[k][i][j].x, latticeData->lattice[k][i][j].y, latticeData->lattice[k][i][j].z}, {0.0f, 0.0f, 0.0f}, { 1.0f,  1.0f, 1.0f}, {i_tex, j_tex}});
                world.lattice_line.push_back(Vertex{ {latticeData->lattice[k][i+1][j].x, latticeData->lattice[k][i+1][j].y, latticeData->lattice[k][i+1][j].z}, {0.0f, 0.0f, 0.0f}, { 1.0f,  1.0f, 1.0f}, {i1_tex, j_tex}});

                world.lattice_line.push_back(Vertex{ {latticeData->lattice[k][i+1][j].x, latticeData->lattice[k][i+1][j].y, latticeData->lattice[k][i+1][j].z}, {0.0f, 0.0f, 0.0f}, { 1.0f,  1.0f, 1.0f}, {i1_tex, j_tex}});
                world.lattice_line.push_back(Vertex{ {latticeData->lattice[k][i+1][j+1].x, latticeData->lattice[k][i+1][j+1].y, latticeData->lattice[k][i+1][j+1].z}, {0.0f, 0.0f, 0.0f}, { 1.0f,  1.0f, 1.0f}, {i1_tex, j1_tex}});

                world.lattice_line.push_back(Vertex{ {latticeData->lattice[k][i+1][j+1].x, latticeData->lattice[k][i+1][j+1].y, latticeData->lattice[k][i+1][j+1].z}, {0.0f, 0.0f, 0.0f}, { 1.0f,  1.0f, 1.0f}, {i1_tex, j1_tex}});
                world.lattice_line.push_back(Vertex{ {latticeData->lattice[k][i][j+1].x, latticeData->lattice[k][i][j+1].y, latticeData->lattice[k][i][j+1].z}, {0.0f, 0.0f, 0.0f}, { 1.0f,  1.0f, 1.0f}, {i_tex, j1_tex}});

                world.lattice_line.push_back(Vertex{ {latticeData->lattice[k][i][j+1].x, latticeData->lattice[k][i][j+1].y, latticeData->lattice[k][i][j+1].z}, {0.0f, 0.0f, 0.0f}, { 1.0f,  1.0f, 1.0f}, {i_tex, j1_tex}});
                world.lattice_line.push_back(Vertex{ {latticeData->lattice[k][i][j].x, latticeData->lattice[k][i][j].y, latticeData->lattice[k][i][j].z}, {0.0f, 0.0f, 0.0f}, { 1.0f,  1.0f, 1.0f}, {i_tex, j_tex}});

                // plane

                world.lattice_plane.push_back(Vertex{ {latticeData->lattice[k][i][j].x, latticeData->lattice[k][i][j].y, latticeData->lattice[k][i][j].z}, {0.0f, 0.0f, 0.0f}, { 1.0f,  1.0f, 1.0f}, {i_tex, j_tex}});
                world.lattice_plane.push_back(Vertex{ {latticeData->lattice[k][i+1][j].x, latticeData->lattice[k][i+1][j].y, latticeData->lattice[k][i+1][j].z}, {0.0f, 0.0f, 0.0f}, { 1.0f,  1.0f, 1.0f}, {i1_tex, j_tex}});
                world.lattice_plane.push_back(Vertex{ {latticeData->lattice[k][i+1][j+1].x, latticeData->lattice[k][i+1][j+1].y, latticeData->lattice[k][i+1][j+1].z}, {0.0f, 0.0f, 0.0f}, { 1.0f,  1.0f, 1.0f}, {i1_tex, j1_tex}});

                world.lattice_plane.push_back(Vertex{ {latticeData->lattice[k][i+1][j+1].x, latticeData->lattice[k][i+1][j+1].y, latticeData->lattice[k][i+1][j+1].z}, {0.0f, 0.0f, 0.0f}, { 1.0f,  1.0f, 1.0f}, {i1_tex, j1_tex}});
                world.lattice_plane.push_back(Vertex{ {latticeData->lattice[k][i][j+1].x, latticeData->lattice[k][i][j+1].y, latticeData->lattice[k][i][j+1].z}, {0.0f, 0.0f, 0.0f}, { 1.0f,  1.0f, 1.0f}, {i_tex, j1_tex}});
                world.lattice_plane.push_back(Vertex{ {latticeData->lattice[k][i][j].x, latticeData->lattice[k][i][j].y, latticeData->lattice[k][i][j].z}, {0.0f, 0.0f, 0.0f}, { 1.0f,  1.0f, 1.0f}, {i_tex, j_tex}});

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
void renew_voxel_color(std::vector<VoxData_b>  bounderVoxelData, int bounderNum){
    world.voxel.clear();
    // for(int i = 54890; i < 54900; i++){// voxel
    for(int i = 0; i < bounderNum; i++){
        int x = bounderVoxelData[i].bounderVoxelLocate.x;
        int y = bounderVoxelData[i].bounderVoxelLocate.y;
        int z = bounderVoxelData[i].bounderVoxelLocate.z;
        float r = (bounderVoxelData[i].bounderVoxelColor.r)/256.0;
        float g = (bounderVoxelData[i].bounderVoxelColor.g)/256.0;
        float b = (bounderVoxelData[i].bounderVoxelColor.b)/256.0;

        if(bounderVoxelData[i].bounderVoxelFaceAir[0] == 0){//0
            //                              position                             normal                 color
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f,  0.0f, -1.0f}, { r, g, b} });
        }
        if(bounderVoxelData[i].bounderVoxelFaceAir[1] == 0){//1
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f,  0.0f,  1.0f}, { r, g, b} });
        }
        if(bounderVoxelData[i].bounderVoxelFaceAir[4] == 0){//2
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  1.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  0.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  1.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  1.0f + z, } , {-1.0f,  0.0f,  0.0f}, { r, g, b} });
        }
        if(bounderVoxelData[i].bounderVoxelFaceAir[5] == 0){//3
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  0.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  0.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  0.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  1.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 1.0f,  0.0f,  0.0f}, { r, g, b} });
        }
        if(bounderVoxelData[i].bounderVoxelFaceAir[2] == 0){//4
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  1.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  0.0f + y,  0.0f + z, } , { 0.0f, -1.0f,  0.0f}, { r, g, b} });
        }
        if(bounderVoxelData[i].bounderVoxelFaceAir[3] == 0){//5
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  1.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  1.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  1.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 1.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  1.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  1.0f + z, } , { 0.0f,  1.0f,  0.0f}, { r, g, b} });
            world.voxel.push_back(Vertex{  { 0.0f + x,  1.0f + y,  0.0f + z, } , { 0.0f,  1.0f,  0.0f}, {r, g, b} });
        }
    }
}
void renew_world(){
    world.lattice_line.clear();
    world.lattice_plane.clear();
    const LatData* latticeData = Lattice_Struct_Use();

    float r = 1.0, g = 1.0, b = 1.0;
    float height = latticeData->map_height;
    float width = latticeData->map_width;

    int latticeTime = 1;
    if(latticeData->shapeLattice == 4) latticeTime = 5;

    for(int k = 0; k < latticeTime; k++){
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


                // log_info("h : %d(%f), w : %d(%f)", i, i_tex, j, j_tex);

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
}