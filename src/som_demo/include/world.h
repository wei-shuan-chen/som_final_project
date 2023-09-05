#ifndef WORLD_H
#define WORLD_H

#include <array>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Vertex.h"
#include "RAWmodel.h"
#include "SOM.h"
#include "textureMap.h"


struct World {

    std::vector<Vertex> square;// floor
    std::vector<Vertex> cube; // test
    std::vector<Vertex> lightcube; // light
    std::vector<Vertex> outerVoxel;
    std::vector<Vertex> innerVoxel;
    std::vector<Vertex> psomVoxel;
    std::vector<std::vector<std::vector<Vertex>>> somVoxel; // voxel model
    std::vector<std::vector<std::vector<Vertex>>> s_lattice_line; // lattice
    std::vector<std::vector<std::vector<Vertex>>> s_lattice_plane; // plane of texture
    std::vector<Vertex> ps_lattice_line;
    std::vector<Vertex> ps_lattice_plane;
    std::vector<Vertex> axis;
    std::vector<Vertex> p_axis;
};

void create_world(svoxModel_t  voxelModel, psvoxModel_t pvoxelModel, MatrixStack texture_m);
void renew_lattice(int layerNum, int blockNum, MatrixStack texture_m);
void renew_plattice();
void renew_voxel(svoxModel_t voxelModel);
void renew_pvoxel(psvoxModel_t voxelModel);
void renew_paxis(glm::mat3x3 A, glm::vec3 t);
void destroy_world();
extern struct World world;

#endif