#ifndef WORLD_H
#define WORLD_H

#include <array>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <glm/glm.hpp>

#include "Vertex.h"
#include "RAWmodel.h"
#include "SOM.h"

struct World {

    std::vector<Vertex> square;// floor
    std::vector<Vertex> cube; // test
    std::vector<Vertex> lightcube; // light
    std::vector<Vertex> voxel; // voxel model
    std::vector<Vertex> lattice_line; // lattice
    std::vector<Vertex> lattice_plane; // plane of texture
    std::vector<Vertex> axis;
};

void create_world(SurfaceVoxModel_t  voxelModel);
void renew_world();
void renew_voxel_color(SurfaceVoxModel_t voxelModel);
void destroy_world();
extern struct World world;

#endif