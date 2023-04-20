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
}
void renew_world(){
    world.lattice_line.clear();
    world.lattice_plane.clear();
    const LatData* latticeData = Lattice_Struct_Use();
    int latticeTime = 1;
    if(latticeData->shapeLattice == 4) latticeTime = 5;
    for(int k = 0; k < latticeTime; k++){
        for (int j = 0; j < latticeData->map_height-1; j++)
        {
            for (int i = 0; i < latticeData->map_width-1; i++)
            {
                float i_tex = (float)i / (float)(latticeData->map_width-2);
                float i1_tex = (float)(i+1) / (float)(latticeData->map_width-2);
                float j_tex = (float)j / (float)(latticeData->map_width-2);
                float j1_tex = (float)(j+1) / (float)(latticeData->map_width-2);
            

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
}
void destroy_world() {
    world.square.clear();
    world.voxel.clear();
    world.lightcube.clear();
    world.cube.clear();
    world.lattice_line.clear();
    world.lattice_plane.clear();
}