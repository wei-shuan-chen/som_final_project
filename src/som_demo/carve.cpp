#include "carve.h"
carve_cls carve;
carve_cls::carve_cls(){}
carve_cls::~carve_cls(){}

void carve_cls::voxel_mapping(int layer, int block, MatrixStack texture_m){
    const LatData_t* latticeData = som[layer][block].Lattice_get();
    int texType = rawmodel.voxelModel.somVoxel[layer][block]->textype;
    for(int n = 0; n < rawmodel.voxelModel.num[layer][block]; n++){// voxel
        double v_x = rawmodel.voxelModel.somVoxel[layer][block][n].locate.x;
        double v_y = rawmodel.voxelModel.somVoxel[layer][block][n].locate.y;
        double v_z = rawmodel.voxelModel.somVoxel[layer][block][n].locate.z;
        double minDist = 100000;
        glm::ivec3 minLatticeCoord = {0,0,0};
        //lattice
        for(int k = 0; k < latticeData->typeNum[latticeData->type]; k++){
            for(int j = 0; j < latticeData->height; j++){
                for(int i = 0; i < latticeData->width; i++){

                    double l_x = latticeData->lattice[k][j][i].x;
                    double l_y = latticeData->lattice[k][j][i].y;
                    double l_z = latticeData->lattice[k][j][i].z;

                    double nowDist = (l_x-v_x)*(l_x-v_x) + (l_y-v_y)*(l_y-v_y) + (l_z-v_z)*(l_z-v_z);
                    if(nowDist < minDist){ // find minDist between voxel point and lattice point
                        minDist = nowDist;
                        minLatticeCoord = {i, j, k};
                    }
                }
            }
        }
        glm::fvec2 trueMinLatticeCoord = findMinDistPrecisePos(latticeData, minDist, {v_x, v_y, v_z}, minLatticeCoord, n);
        // find the color of minDist lattice
        glm::fvec2 tmpCoord  = {trueMinLatticeCoord.x/(latticeData->width-1), trueMinLatticeCoord.y/(latticeData->height-1)};
        glm::fvec2 latticeTexCoord = rawmodel.voxelModel.somVoxel[layer][block][n].texcoord = tex.compute_texture(texture_m, glm::fvec4(tmpCoord , 0.0, 1.0));

        if(latticeTexCoord.x < 0.0 || latticeTexCoord.x > 1.0 || latticeTexCoord.y < 0.0 || latticeTexCoord.y > 1.0){
            rawmodel.voxelModel.somVoxel[layer][block][n].color = {1.0, 1.0, 1.0};
        }else{
            glm::ivec2 imageRate = {(int)(latticeTexCoord.x*(double)(tex.imageTex[texType].width-1)), (int)(latticeTexCoord.y*(double)(tex.imageTex[texType].height-1))};

            float r = tex.imageTex[texType].image[imageRate.y][imageRate.x].r / 256.0;
            float g = tex.imageTex[texType].image[imageRate.y][imageRate.x].g / 256.0;
            float b = tex.imageTex[texType].image[imageRate.y][imageRate.x].b / 256.0;
            rawmodel.voxelModel.somVoxel[layer][block][n].color = {r,g,b};
        }

    }
}
glm::fvec2 carve_cls::findMinDistPrecisePos(const LatData_t* latticeData, double mid, glm::fvec3 voxelPos, glm::ivec3 minLatticeCoord, int de){

    glm::fvec3 twoDcoord = minLatticeCoord;

    double minDist = mid;
    int impair[9][2] = {{1, 0}, {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}, {0,-1}, {1,-1}, {1, 0}};

    for(int i = 0; i < 8; i++){
        // find triangle(o,a1,a2)
        if(minLatticeCoord.x+impair[i][0] < 0 || minLatticeCoord.x+impair[i][0] > latticeData->width-1 ) continue;
        if(minLatticeCoord.y+impair[i][1] < 0 || minLatticeCoord.y+impair[i][1] > latticeData->height-1) continue;
        if(minLatticeCoord.x+impair[i+1][0] < 0 || minLatticeCoord.x+impair[i+1][0] > latticeData->width-1 ) continue;
        if(minLatticeCoord.y+impair[i+1][1] < 0 || minLatticeCoord.y+impair[i+1][1] > latticeData->height-1) continue;
        glm::fvec3 a1 = latticeData->lattice[minLatticeCoord.z][minLatticeCoord.y+impair[i][1]][minLatticeCoord.x+impair[i][0]];
        glm::fvec3 a2 = latticeData->lattice[minLatticeCoord.z][minLatticeCoord.y+impair[i+1][1]][minLatticeCoord.x+impair[i+1][0]];
        glm::fvec3 o = latticeData->lattice[minLatticeCoord.z][minLatticeCoord.y][minLatticeCoord.x];
        glm::fvec3 p = voxelPos;

        // Project the point p onto the plane where the triangle is located
        glm::fvec3 vector_n = glm::normalize(crossPruduct(a1-o, a2-o));
        glm::fvec3 vector_p = p-o;

        glm::fvec3 vector_d;
        vector_d.x = (-1*innerProduct(vector_p, vector_n))*vector_n.x;
        vector_d.y = (-1*innerProduct(vector_p, vector_n))*vector_n.y;
        vector_d.z = (-1*innerProduct(vector_p, vector_n))*vector_n.z;
        // find projection point
        glm::fvec3 projp = p + vector_d;

        // ensure the point is in the triangle
        glm::fvec3 cross1 = glm::normalize(crossPruduct(o-projp, a1-projp));
        glm::fvec3 cross2 = glm::normalize(crossPruduct(a1-projp, a2-projp));
        glm::fvec3 cross3 = glm::normalize(crossPruduct(a2-projp, o-projp));
        if(cross1.x*cross2.x < 0.0 || cross1.x*cross3.x < 0.0 || cross2.x*cross3.x < 0.0){
            // if outer triangle find close point or edgepoint
            projp = outerProjp(o, a1, a2, projp, p);
            vector_d = p - projp;
        }

        double tmpDist = vector_d.x*vector_d.x + vector_d.y*vector_d.y + vector_d.z*vector_d.z;
        if(tmpDist >= minDist) {
            continue;
        }
        minDist = tmpDist;
        // compute dist of point to triangle
        glm::fvec3 ratio = pointTotriangle(o, a1, a2, projp, vector_n);


        twoDcoord.x = ratio[0]*minLatticeCoord.x + ratio[1]*(minLatticeCoord.x+impair[i][0]) + ratio[2]*(minLatticeCoord.x+impair[i+1][0]);
        twoDcoord.y = ratio[0]*minLatticeCoord.y + ratio[1]*(minLatticeCoord.y+impair[i][1]) + ratio[2]*(minLatticeCoord.y+impair[i+1][1]);

        if(twoDcoord.x < 0.0) twoDcoord.x = 0.0;
        if(twoDcoord.x > latticeData->width-1) twoDcoord.x = latticeData->width-1;
        if(twoDcoord.y < 0.0) twoDcoord.y = 0.0;
        if(twoDcoord.y > latticeData->height-1) twoDcoord.y = latticeData->height-1;

        }

    return twoDcoord;

}
glm::fvec3 carve_cls::outerProjp(glm::fvec3 o, glm::fvec3 a1, glm::fvec3 a2, glm::fvec3 projp, glm::fvec3 p){

    // outer point close to triangle point
    // o
    glm::fvec3 newp = o;
    glm::fvec3 tmp = p-o;
    float tmpDist = tmp.x*tmp.x + tmp.y*tmp.y + tmp.z*tmp.z;
    float dist = tmpDist;

    // a1
    tmp = p - a1;
    tmpDist = tmp.x*tmp.x + tmp.y*tmp.y + tmp.z*tmp.z;
    if(dist > tmpDist){
        dist = tmpDist;
        newp = a1;

    }
    // a2
    tmp = p - a2;
    tmpDist = tmp.x*tmp.x + tmp.y*tmp.y + tmp.z*tmp.z;
    if(dist > tmpDist){
        dist = tmpDist;
        newp = a2;
    }
    // outer point close to triangle edge
    // o a1
    tmp = a1-o;
    float ratio = innerProduct(a1-o, projp-o)/ (tmp.x*tmp.x + tmp.y*tmp.y + tmp.z*tmp.z);
    tmp = p - ((a1-o)*ratio + o);
    tmpDist = tmp.x*tmp.x + tmp.y*tmp.y + tmp.z*tmp.z;
    if(dist > tmpDist && ratio >= 0.0 && ratio <= 1.0){
        dist = tmpDist;
        newp = (a1-o)*ratio + o;
    }
    // o a2
    tmp = a2-o;
    ratio = innerProduct(a2-o, projp-o)/ (tmp.x*tmp.x + tmp.y*tmp.y + tmp.z*tmp.z);
    tmp = p - ((a2-o)*ratio + o);
    tmpDist = tmp.x*tmp.x + tmp.y*tmp.y + tmp.z*tmp.z;
    if(dist > tmpDist && ratio >= 0.0 && ratio <= 1.0){
        dist = tmpDist;
        newp = (a2-o)*ratio + o;
    }
    // a1 a2
    tmp = a2-a1;
    ratio = innerProduct(a2-a1, projp-a1)/ (tmp.x*tmp.x + tmp.y*tmp.y + tmp.z*tmp.z);
    tmp = p - ((a2-a1)*ratio + a1);
    tmpDist = tmp.x*tmp.x + tmp.y*tmp.y + tmp.z*tmp.z;
    if(dist > tmpDist && ratio >= 0.0 && ratio <= 1.0){
        dist = tmpDist;
        newp = (a2-a1)*ratio + a1;
    }

    return newp;

}
glm::fvec3 carve_cls::pointTotriangle(glm::fvec3 o, glm::fvec3 a1, glm::fvec3 a2, glm::fvec3 projp, glm::fvec3 vector_n){

    // compute center of gravity
    glm::fvec3 ratio;
    float total_volume = innerProduct(crossPruduct(a1-o, a2-o),vector_n);
    ratio[0] = innerProduct(crossPruduct(a1-projp, a2-projp),vector_n)/ total_volume;
    ratio[1] = innerProduct(crossPruduct(a2-projp, o-projp),vector_n)/ total_volume;
    ratio[2] = 1.0 - ratio[1] - ratio[0];

    return ratio;
}

glm::fvec3 carve_cls::crossPruduct(glm::fvec3 a, glm::fvec3 b){
    glm::fvec3 c;
    c.x = a.y*b.z - a.z*b.y;
    c.y = -1*(a.x*b.z - a.z*b.x);
    c.z = a.x*b.y - a.y*b.x;

    return c;
}
float carve_cls::innerProduct(glm::fvec3 a, glm::fvec3 b){
    return ((a.x*b.x) + (a.y*b.y) + (a.z*b.z));
}
