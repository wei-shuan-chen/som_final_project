#include "carve.h"
carve_cls carve;
carve_cls::carve_cls(){}
carve_cls::~carve_cls(){}

void carve_cls::pvoxel_mapping(){
    const LatData_t* latticeData = psom.Lattice_get();
    cout << rawmodel.pvoxelModel.psomVoxel.size() << endl;
    // for(int v =54439; v < 54440; v++){
    for(int v =0; v < rawmodel.pvoxelModel.psomVoxel.size(); v++){
        double v_x = rawmodel.pvoxelModel.psomVoxel[v].locate.x+0.5;
        double v_y = rawmodel.pvoxelModel.psomVoxel[v].locate.y+0.5;
        double v_z = rawmodel.pvoxelModel.psomVoxel[v].locate.z+0.5;
        double minDist = 100000;
        glm::ivec3 minLatticeCoord = find_min_dist_pos(latticeData, v_x, v_y, v_z, &minDist);

        // cout << "minLatticeCoord : "<<minLatticeCoord.x << ", " << minLatticeCoord.y<<", " <<minLatticeCoord.z<<endl;
        glm::fvec3 voxelToLatticeCoord = surround_Tetrahedron(latticeData, minDist, {v_x, v_y, v_z}, minLatticeCoord);
        // cout << "voxelToLatticeCoord : "<<voxelToLatticeCoord.x << ", " << voxelToLatticeCoord.y<<", " <<voxelToLatticeCoord.z<<endl;
        glm::fvec3 latticeTexCoord = {voxelToLatticeCoord.x/(latticeData->width-1), voxelToLatticeCoord.y/(latticeData->height-1), voxelToLatticeCoord.z/(latticeData->depth-1)};
        latticeTexCoord = latticeCoord_to_textureCoord_3D(latticeTexCoord, latticeData);
        latticeTexCoord = tex.lattice_to_texture(glm::fvec4(latticeTexCoord, 1.0), THREEDTEX);

        if(latticeTexCoord.x < 0.0 || latticeTexCoord.x > 1.0 || latticeTexCoord.y < 0.0 || latticeTexCoord.y > 1.0|| latticeTexCoord.z < 0.0 || latticeTexCoord.z > 1.0){
            // cout << latticeTexCoord.x<<", "<<latticeTexCoord.y <<", "<<latticeTexCoord.z<<endl;
            rawmodel.pvoxelModel.psomVoxel[v].color = {1.0, 1.0, 0.0};
        }else{
            glm::ivec3 imageRate = {(latticeTexCoord.x*(double)(tex.threeDTex.width-1)), (latticeTexCoord.y*(double)(tex.threeDTex.height-1)), (latticeTexCoord.z*(double)(tex.threeDTex.depth-1))};

            int num = imageRate.x*3 + imageRate.y*tex.threeDTex.width*3 + imageRate.z*tex.threeDTex.width*tex.threeDTex.height*3;
            float r = tex.threeDTex.data[num];
            float g = tex.threeDTex.data[num+1];
            float b = tex.threeDTex.data[num+2];

            rawmodel.pvoxelModel.psomVoxel[v].color = {r,g,b};

        }

        // output raw
        glm::ivec3 rawCoord = rawmodel.pvoxelModel.psomVoxel[v].locate;
        if(rawmodel.pvoxelModel.psomVoxel[v].color.r)
            rawmodel.newrawData[rawCoord.y][rawCoord.x][rawCoord.z] = 150;
        if(rawmodel.pvoxelModel.psomVoxel[v].color.b)
            rawmodel.newrawData[rawCoord.y][rawCoord.x][rawCoord.z] = 200;
    }
}
void carve_cls::voxel_mapping(int layer, int block){
    const LatData_t* latticeData = som[layer][block].Lattice_get();

    int texType = rawmodel.voxelModel.somVoxel[layer][block]->textype;
    int texfilter = MINIFICATION;
    int texsize = tex.imageTex[texType].height*tex.imageTex[texType].width;
    if(rawmodel.voxelModel.voxelnum[layer][block] > texsize)texfilter = MAGNIFICATON;

    cout << "voxel : "<< rawmodel.voxelModel.voxelnum[layer][block];
    cout << "texsize : "<< texsize;

    for(int n = 0; n < rawmodel.voxelModel.voxelnum[layer][block]; n++){// voxel
        double v_x = rawmodel.voxelModel.somVoxel[layer][block][n].locate.x+0.5;
        double v_y = rawmodel.voxelModel.somVoxel[layer][block][n].locate.y+0.5;
        double v_z = rawmodel.voxelModel.somVoxel[layer][block][n].locate.z+0.5;
        double minDist = 100000;
        glm::fvec3 latticeTexCoord0, latticeTexCoord1, latticeTexCoord2, tmpCoord;

        glm::ivec3 minLatticeCoord = find_min_dist_pos(latticeData, v_x, v_y, v_z, &minDist);
        if(latticeVoxelFilter == LINEAR){
            // v_x, v_y, v_z
            glm::fvec2 voxelToLatticeCoord;
            voxelToLatticeCoord = surround_Triangles(latticeData, minDist, {v_x, v_y, v_z}, minLatticeCoord);
            tmpCoord = latticeCoord_to_textureCoord_2D(voxelToLatticeCoord, latticeData);
            latticeTexCoord1 = rawmodel.voxelModel.somVoxel[layer][block][n].texcoord = tex.lattice_to_texture(glm::fvec4(tmpCoord, 1.0), TWODTEX);
            // v_x-0.5, v_y-0.5, v_z-0.5
            voxelToLatticeCoord = surround_Triangles(latticeData, minDist, {v_x-0.5, v_y-0.5, v_z-0.5}, minLatticeCoord);
            tmpCoord = latticeCoord_to_textureCoord_2D(voxelToLatticeCoord, latticeData);//{voxelToLatticeCoord.x/(latticeData->width-1), voxelToLatticeCoord.y/(latticeData->height-1), 0.5};
            latticeTexCoord0 = tex.lattice_to_texture(glm::fvec4(tmpCoord, 1.0), TWODTEX);
            // v_x+0.5, v_y+0.5, v_z+0.5
            voxelToLatticeCoord = surround_Triangles(latticeData, minDist, {v_x+0.5, v_y+0.5, v_z+0.5}, minLatticeCoord);
            tmpCoord = latticeCoord_to_textureCoord_2D(voxelToLatticeCoord, latticeData);//{voxelToLatticeCoord.x/(latticeData->width-1), voxelToLatticeCoord.y/(latticeData->height-1), 0.5};
            latticeTexCoord2 = tex.lattice_to_texture(glm::fvec4(tmpCoord, 1.0), TWODTEX);
        }
        if(latticeVoxelFilter == NEAREST){
            tmpCoord = latticeCoord_to_textureCoord_2D({minLatticeCoord.x, minLatticeCoord.y}, latticeData);
            latticeTexCoord0=latticeTexCoord1 =latticeTexCoord2= rawmodel.voxelModel.somVoxel[layer][block][n].texcoord = tex.lattice_to_texture(glm::fvec4(tmpCoord, 1.0), TWODTEX);
        }

        if(latticeTexCoord0.x < 0.0 || latticeTexCoord0.x > 1.0 || latticeTexCoord0.y < 0.0 || latticeTexCoord0.y > 1.0){
            rawmodel.voxelModel.somVoxel[layer][block][n].color = {1.0, 1.0, 1.0};
        }else if(latticeTexCoord1.x < 0.0 || latticeTexCoord1.x > 1.0 || latticeTexCoord1.y < 0.0 || latticeTexCoord1.y > 1.0){
            rawmodel.voxelModel.somVoxel[layer][block][n].color = {1.0, 1.0, 1.0};
        }else if(latticeTexCoord2.x < 0.0 || latticeTexCoord2.x > 1.0 || latticeTexCoord2.y < 0.0 || latticeTexCoord2.y > 1.0){
            rawmodel.voxelModel.somVoxel[layer][block][n].color = {1.0, 1.0, 1.0};
        }else{
            if(latticeTextureFilter == NEAREST){
                // glm::fvec3 color0 = {0.0,0.0,0.0};//{0.1,0.21,0.56};//b
                // glm::fvec3 color1 = {1.0,1.0,1.0};//{1.0,0.8941,0.8824};//pink
                glm::fvec2 imageRate1 = {latticeTexCoord1.x*(double)(tex.imageTex[texType].width-1), latticeTexCoord1.y*(double)(tex.imageTex[texType].height-1)};

                for(int c = 0; c < 3; c++){
                    // if(tex.imageTex[texType].image[(int)imageRate1.y][(int)imageRate1.x][c]/256.0 >0.8){
                    //     color[c] = color1[c];
                    // }else{
                    //     color[c] = color0[c];
                    // }
                    rawmodel.voxelModel.somVoxel[layer][block][n].color[c] = tex.imageTex[texType].image[(int)imageRate1.y][(int)imageRate1.x][c]/256.0;
                }
            }
            if(latticeTextureFilter ==LINEAR){
                if(texfilter == MAGNIFICATON){
                    // tex < voxel
                    glm::fvec2 imageRate1 = {latticeTexCoord1.x*(double)(tex.imageTex[texType].width-1), latticeTexCoord1.y*(double)(tex.imageTex[texType].height-1)};
                    rawmodel.voxelModel.somVoxel[layer][block][n].color = mag_filter(imageRate1, texType);
                }else{
                    glm::ivec2 imageRate0 = {(latticeTexCoord0.x*(double)(tex.imageTex[texType].width-1)), (latticeTexCoord0.y*(double)(tex.imageTex[texType].height-1))};
                    glm::ivec2 imageRate2 = {(latticeTexCoord2.x*(double)(tex.imageTex[texType].width-1)), (latticeTexCoord2.y*(double)(tex.imageTex[texType].height-1))};

                    rawmodel.voxelModel.somVoxel[layer][block][n].color = min_filter(imageRate0, imageRate2, texType);
                }
            }

            // output raw
            float r = rawmodel.voxelModel.somVoxel[layer][block][n].color.r;
            if(r < 0.5) {
                glm::ivec3 rawCoord = rawmodel.voxelModel.somVoxel[layer][block][n].locate;
                rawmodel.newrawData[rawCoord.y][rawCoord.x][rawCoord.z] = 50;
            }
        }
    }
    tex.update_intensityMap();
}
glm::fvec3 carve_cls::latticeCoord_to_textureCoord_2D(glm::fvec2 latticeCoord, const LatData_t* latticeData){
    int s = latticeCoord.s, t = latticeCoord.t, r = 0;

    if(latticeCoord.s == s && latticeCoord.t == t) return latticeData->wTex[r][t][s];

    int delta_t = 1, delta_s = 1;
    if(s == latticeData->width-1) delta_s = -1;
    if(t == latticeData->height-1) delta_t = -1;

    glm::fvec3 c00 = latticeData->wTex[r][t][s];
    glm::fvec3 c01 = latticeData->wTex[r][t][s+delta_s];
    glm::fvec3 c10 = latticeData->wTex[r][t+delta_t][s];
    glm::fvec3 c11 = latticeData->wTex[r][t+delta_t][s+delta_s];

    float h = latticeCoord.s-(float)s, k = latticeCoord.t-(float)t;

    glm::fvec3 c = (1-h)*(1-k)*c00 + h*(1-k)*c01 + (1-h)*k*c10 + h*k*c11;

    return c;
}
glm::fvec3 carve_cls::latticeCoord_to_textureCoord_3D(glm::fvec3 latticeCoord, const LatData_t* latticeData){
    int s = latticeCoord.s, t = latticeCoord.t, r = latticeCoord.r;

    if(latticeCoord.s == s && latticeCoord.t == t && latticeCoord.r == r) return latticeData->wTex[r][t][s];

    int delta_t = 1, delta_s = 1, delta_r = 1;
    if(s == latticeData->width-1) delta_s = -1;
    if(t == latticeData->height-1) delta_t = -1;
    if(r == latticeData->depth-1) delta_r = -1;

    glm::fvec3 c000 = latticeData->wTex[r][t][s];
    glm::fvec3 c001 = latticeData->wTex[r][t][s+delta_s];
    glm::fvec3 c010 = latticeData->wTex[r][t+delta_t][s];
    glm::fvec3 c011 = latticeData->wTex[r][t+delta_t][s+delta_s];

    glm::fvec3 c100 = latticeData->wTex[r+delta_r][t][s];
    glm::fvec3 c101 = latticeData->wTex[r+delta_r][t][s+delta_s];
    glm::fvec3 c110 = latticeData->wTex[r+delta_r][t+delta_t][s];
    glm::fvec3 c111 = latticeData->wTex[r+delta_r][t+delta_t][s+delta_s];

    float _s = latticeCoord.s-(float)s, _t = latticeCoord.t-(float)t, _r = latticeCoord.r-(float)r;

    glm::fvec3 c = (1-_s)*(1-_t)*(1-_r)*c000 + _s*(1-_t)*(1-_r)*c001 + (1-_s)*_t*(1-_r)*c010 + _s*_t*(1-_r)*c011
                    + (1-_s)*(1-_t)*_r*c100 + _s*(1-_t)*_r*c101 + (1-_s)*_t*_r*c110 + _s*_t*_r*c111;

    return c;
}
glm::fvec3 carve_cls::mag_filter(glm::fvec2 imageRate1, int texType){
    // tex < voxel
    glm::fvec3 color;
    float deltax = imageRate1.x-(int)imageRate1.x;
    float deltay = imageRate1.y-(int)imageRate1.y;
    glm::ivec3 color_ij = tex.imageTex[texType].image[(int)imageRate1.y][(int)imageRate1.x];
    glm::ivec3 color_i1j = tex.imageTex[texType].image[(int)imageRate1.y][(int)imageRate1.x+1];
    glm::ivec3 color_ij1 = tex.imageTex[texType].image[(int)imageRate1.y+1][(int)imageRate1.x];
    glm::ivec3 color_i1j1 = tex.imageTex[texType].image[(int)imageRate1.y+1][(int)imageRate1.x+1];
    for(int c = 0; c < 3; c++){
        color[c] = ((1-deltax)*(1-deltay)*color_ij[c]+
                    (deltax)*(1-deltay)*color_i1j[c]+
                    (1-deltax)*(deltay)*color_ij1[c]+
                    (deltax)*(deltay)*color_i1j1[c])/256.0;
    }
    return color;
}
glm::fvec3 carve_cls::min_filter(glm::ivec2 imageRate0, glm::ivec2 imageRate2, int texType){
    // tex > voxel
    glm::fvec3 color = {0,0,0};
    int l,r,d,t;
    if(imageRate0.x < imageRate2.x) {
        l = imageRate0.x;
        r = imageRate2.x;
    }else{
        r = imageRate0.x;
        l = imageRate2.x;
    }
    if(imageRate0.y < imageRate2.y){
        d = imageRate0.y;
        t = imageRate2.y;
    }else{
        t = imageRate0.y;
        d = imageRate2.y;
    }
    int num = 0;
    glm::fvec3 color0 = {0.1,0.21,0.56};//b
    glm::fvec3 color1 = {1.0,0.8941,0.8824};//y

    for(int w = l; w <= r; w++){
        for(int h = d; h <= t; h++){
            for(int c = 0; c < 3; c++){
                // change texture color
                // if(tex.imageTex[texType].image[h][w][c]/ 256.0 >0.8){
                //     color[c] += color1[c];
                // }else{
                //     color[c] += color0[c];
                // }
                color[c] += tex.imageTex[texType].image[h][w][c]/256.0;
            }
            num++;
        }
    }
    for(int c = 0; c < 3; c++){
        color[c] = color[c]/(num);
    }
    return color;
}
glm::ivec3 carve_cls::find_min_dist_pos(const LatData_t* latticeData, double v_x, double v_y, double v_z, double* minDist){

    glm::ivec3 minLatticeCoord = {0,0,0};
    //lattice
    for(int k = 0; k < latticeData->typeNum[latticeData->type]; k++){
        for(int j = 0; j < latticeData->height; j++){
            for(int i = 0; i < latticeData->width; i++){

                double l_x = latticeData->wPos[k][j][i].x;
                double l_y = latticeData->wPos[k][j][i].y;
                double l_z = latticeData->wPos[k][j][i].z;

                double nowDist = (l_x-v_x)*(l_x-v_x) + (l_y-v_y)*(l_y-v_y) + (l_z-v_z)*(l_z-v_z);
                if(nowDist < *minDist){ // find minDist between voxel point and lattice point
                    *minDist = nowDist;
                    minLatticeCoord = {i, j, k};
                }
            }
        }
    }
    return minLatticeCoord;
}
glm::fvec3 carve_cls::surround_Tetrahedron(const LatData_t* latticeData, double mid, glm::fvec3 voxelPos, glm::ivec3 minLatticeCoord){
    if(pcarve){
        float weight[3][3][3];
        float D = 0.0;
        float v_x = voxelPos.x;
        float v_y = voxelPos.y;
        float v_z = voxelPos.z;
        float lx0 = latticeData->wPos[minLatticeCoord.z][minLatticeCoord.y][minLatticeCoord.x].x;
        float ly0 = latticeData->wPos[minLatticeCoord.z][minLatticeCoord.y][minLatticeCoord.x].y;
        float lz0 = latticeData->wPos[minLatticeCoord.z][minLatticeCoord.y][minLatticeCoord.x].z;
        for(int z = -1; z <= 1; z++){
            for(int y = -1; y <= 1; y++){
                for(int x = -1; x <= 1; x++){
                    int x_i = minLatticeCoord.x+x;
                    int y_i = minLatticeCoord.y+y;
                    int z_i = minLatticeCoord.z+z;
                    if(x_i > latticeData->width-1 || x_i < 0 || y_i > latticeData->height-1 || y_i < 0 || z_i > latticeData->depth-1 || z_i < 0){
                        weight[z+1][y+1][x+1] = 0;
                    }
                    else{
                        float lx = latticeData->wPos[z_i][y_i][x_i].x;
                        float ly = latticeData->wPos[z_i][y_i][x_i].y;
                        float lz = latticeData->wPos[z_i][y_i][x_i].z;
                        // float tmpw = sqrt((lx-lx0)*(lx-lx0) + (ly-ly0)*(ly-ly0) + (lz-lz0)*(lz-lz0));
                        weight[z+1][y+1][x+1] = 1.0/sqrt((lx-v_x)*(lx-v_x) + (ly-v_y)*(ly-v_y) + (lz-v_z)*(lz-v_z));
                        // if(tmpw < weight[z+1][y+1][x+1])weight[z+1][y+1][x+1] = 0;
                        // else weight[z+1][y+1][x+1] = 1.0/weight[z+1][y+1][x+1];
                        D += weight[z+1][y+1][x+1];
                    }
                }
            }
        }
        if(D == 0) return minLatticeCoord;
        glm::fvec3 coord = {0,0,0};
        for(int z = -1; z <= 1; z++){
            for(int y = -1; y <= 1; y++){
                for(int x = -1; x <= 1; x++){
                    int x_i = minLatticeCoord.x+x;
                    int y_i = minLatticeCoord.y+y;
                    int z_i = minLatticeCoord.z+z;
                    if(x_i > latticeData->width-1 || x_i < 0 || y_i > latticeData->height-1 || y_i < 0 || z_i > latticeData->depth-1 || z_i < 0){
                        continue;
                    }else{
                        float ratio = weight[z+1][y+1][x+1]/D;
                        // cout <<x<<", "<<y<<", "<<z <<" : "<< 1.0/weight[z+1][y+1][x+1]<<"/"<<D<<" = "<<ratio << endl;
                        coord.x += x_i * ratio;
                        coord.y += y_i * ratio;
                        coord.z += z_i * ratio;
                    }
                }
            }
        }

        return coord;
    }else{
        glm::fvec3 threeDcoord = minLatticeCoord;
        double minDist = mid;
        int basePoint[6][3] = {{1,0,0},{0,1,0},{0,0,1},{1,1,0},{1,0,1},{0,1,1}};
        int sign[8][3] = {{1,1,1},{-1,1,1},{-1,-1,1},{1,-1,1},{1,1,-1},{-1,1,-1},{-1,-1,-1},{1,-1,-1}};
        int order[4][3] = {{0,3,4},{3,4,5},{2,4,5},{1,3,5}};

        for(int s = 0; s < 8; s++){
            for(int r = 0; r < 4; r++){
                // total 32 Tetrahedron
                int impair[6][3];
                for(int b = 0; b < 6; b++){
                    for(int i = 0; i < 3; i++)
                        impair[b][i] = basePoint[b][i]*sign[s][i];
                }
                int a0_o = order[r][0];
                int a0_i = minLatticeCoord.x+impair[a0_o][0];
                int a0_j = minLatticeCoord.y+impair[a0_o][1];
                int a0_k = minLatticeCoord.z+impair[a0_o][2];

                int a1_o = order[r][1];
                int a1_i = minLatticeCoord.x+impair[a1_o][0];
                int a1_j = minLatticeCoord.y+impair[a1_o][1];
                int a1_k = minLatticeCoord.z+impair[a1_o][2];

                int a2_o = order[r][2];
                int a2_i = minLatticeCoord.x+impair[a2_o][0];
                int a2_j = minLatticeCoord.y+impair[a2_o][1];
                int a2_k = minLatticeCoord.z+impair[a2_o][2];

                int o_i = minLatticeCoord.x;
                int o_j = minLatticeCoord.y;
                int o_k = minLatticeCoord.z;

                // a0
                if(a0_i < 0 || a0_i > latticeData->width-1) continue;
                if(a0_j < 0 || a0_j > latticeData->height-1) continue;
                if(a0_k < 0 || a0_k > latticeData->depth-1) continue;
                // a1
                if(a1_i < 0 || a1_i > latticeData->width-1) continue;
                if(a1_j < 0 || a1_j > latticeData->height-1) continue;
                if(a1_k < 0 || a1_k > latticeData->depth-1) continue;
                // a2
                if(a2_i < 0 || a2_i > latticeData->width-1) continue;
                if(a2_j < 0 || a2_j > latticeData->height-1) continue;
                if(a2_k < 0 || a2_k > latticeData->depth-1) continue;

                glm::fvec3 a0 = latticeData->wPos[a0_k][a0_j][a0_i];
                glm::fvec3 a1 = latticeData->wPos[a1_k][a1_j][a1_i];
                glm::fvec3 a2 = latticeData->wPos[a2_k][a2_j][a2_i];
                glm::fvec3 o = latticeData->wPos[o_k][o_j][o_i];
                glm::fvec3 p = voxelPos;

                // Use the Barycentric Coordinates to determine if voxelPos in a tetrahedron.
                // if in -> compute minDist and continue
                // if out call point_to_triangle (*4 triangle)
                glm::mat3x3 tmp = {a0-o, a1-o, a2-o};
                glm::mat3x3 inverse_m = math.inverseMatrix3(tmp);
                glm::vec3 n_v = inverse_m*p;
                // float o_a0_a1_a2 = math.determinant(tmp);
                // tmp = {p-o,a1-o,a2-o};
                // float o_p_a1_a2 = math.determinant(tmp);
                // tmp = {a0-o,p-o,a2-o};
                // float o_a0_p_a2 = math.determinant(tmp);
                // tmp = {a0-o,a1-o,p-o};
                // float o_a0_a1_p = math.determinant(tmp);
                // tmp = {a0-p,a1-p,a2-p};
                // float p_a0_a1_a2 = math.determinant(tmp);
                // glm::fvec4 ratio = {o_p_a1_a2/o_a0_a1_a2, o_a0_p_a2/o_a0_a1_a2, o_a0_a1_p/o_a0_a1_a2, p_a0_a1_a2/o_a0_a1_a2};
                // cout << "ratio : "<<ratio.x<<", "<<ratio.y<<", "<<ratio.z<<", "<<ratio.a<<endl;
                if(n_v.x > 0 && n_v.x < 1 && n_v.y > 0 && n_v.y < 1 && n_v.z > 0 && n_v.z < 1 && n_v.x + n_v.y + n_v.z < 1 && n_v.x + n_v.y + n_v.z > 0){
                // if(ratio[0]<0 || ratio[0]>1 ||ratio[1]<0 || ratio[1]>1 || ratio[2]< 0 || ratio[2]>1|| ratio[3]< 0 || ratio[3]>1){
                    // in
                    minDist = 0;
                    threeDcoord.x = n_v.x*(a0_i-o_i) + n_v.y*(a1_i-o_i) + n_v.z*(a2_i-o_i);
                    threeDcoord.y = n_v.x*(a0_j-o_j) + n_v.y*(a1_j-o_j) + n_v.z*(a2_j-o_j);
                    threeDcoord.z = n_v.x*(a0_k-o_k) + n_v.y*(a1_k-o_k) + n_v.z*(a2_k-o_k);
                    // threeDcoord.x = ratio[0]*a0_i + ratio[1]*a1_i + ratio[2]*a2_i + ratio[3]*minLatticeCoord.x;
                    // threeDcoord.y = ratio[0]*a0_j + ratio[1]*a1_j + ratio[2]*a2_j + ratio[3]*minLatticeCoord.y;
                    // threeDcoord.z = ratio[0]*a0_k + ratio[1]*a1_k + ratio[2]*a2_k + ratio[3]*minLatticeCoord.z;

                    if(threeDcoord.x < 0.0) threeDcoord.x = 0.0;
                    if(threeDcoord.x > latticeData->width-1) threeDcoord.x = latticeData->width-1;
                    if(threeDcoord.y < 0.0) threeDcoord.y = 0.0;
                    if(threeDcoord.y > latticeData->height-1) threeDcoord.y = latticeData->height-1;
                    if(threeDcoord.z < 0.0) threeDcoord.z = 0.0;
                    if(threeDcoord.z > latticeData->depth-1) threeDcoord.z = latticeData->depth-1;

                    return threeDcoord;
                }else{
                    // out
                    // cout << "a0_index : "<< a0_i<<", " << a0_j<<", "<<a0_k<<endl;
                    // cout << "a1_index : "<< a1_i<<", " << a1_j<<", "<<a1_k<<endl;
                    // cout << "a2_index : "<< a2_i<<", " << a2_j<<", "<<a2_k<<endl;
                    glm::fvec3 tmpCoord = outer_tetrahedron(o,minLatticeCoord,a0,{a0_i,a0_j,a0_k},a1,{a1_i,a1_j,a1_k},a2,{a2_i,a2_j,a2_k},p,&minDist);
                    if(tmpCoord.x != -1 || tmpCoord.y != -1 || tmpCoord.z != -1){
                        threeDcoord = tmpCoord;
                    }else{
                        // cout << "continue\n";
                    }



                }

            }
        }
        if(threeDcoord.x < 0.0) threeDcoord.x = 0.0;
        if(threeDcoord.x > latticeData->width-1) threeDcoord.x = latticeData->width-1;
        if(threeDcoord.y < 0.0) threeDcoord.y = 0.0;
        if(threeDcoord.y > latticeData->height-1) threeDcoord.y = latticeData->height-1;
        if(threeDcoord.z < 0.0) threeDcoord.z = 0.0;
        if(threeDcoord.z > latticeData->depth-1) threeDcoord.z = latticeData->depth-1;
        return threeDcoord;
    }
}
glm::fvec3 carve_cls::outer_tetrahedron(glm::fvec3 o, glm::fvec3 o_index, glm::fvec3 a0, glm::fvec3 a0_index, glm::fvec3 a1, glm::fvec3 a1_index, glm::fvec3 a2, glm::fvec3 a2_index, glm::fvec3 p, double* minDist){
    glm::fvec3 ratio = {0,0,0};
    glm::fvec3 threeDcoord = {-1,-1,-1};
    double tmpDist = *minDist;
    ratio = point_to_triangle(o, a0, a1, p, minDist);
    // cout << "0 "<< *minDist<<" ";
    // cout << "ratio : "<< ratio.x << ", " << ratio.y<<", "<<ratio.z<<endl;
    if(tmpDist>*minDist){
        tmpDist = *minDist;
        threeDcoord.x = ratio[0]*o_index.x + ratio[1]*a0_index.x + ratio[2]*a1_index.x;
        threeDcoord.y = ratio[0]*o_index.y + ratio[1]*a0_index.y + ratio[2]*a1_index.y;
        threeDcoord.z = ratio[0]*o_index.z + ratio[1]*a0_index.z + ratio[2]*a1_index.z;
    }
    ratio = point_to_triangle(o, a0, a2, p, minDist);
    // cout << "1 "<< *minDist<<" ";
    // cout << "ratio : "<< ratio.x << ", " << ratio.y<<", "<<ratio.z<<endl;
    if(tmpDist>*minDist){
        tmpDist = *minDist;
        threeDcoord.x = ratio[0]*o_index.x + ratio[1]*a0_index.x + ratio[2]*a2_index.x;
        threeDcoord.y = ratio[0]*o_index.y + ratio[1]*a0_index.y + ratio[2]*a2_index.y;
        threeDcoord.z = ratio[0]*o_index.z + ratio[1]*a0_index.z + ratio[2]*a2_index.z;
        // cout <<"threeDCoord : " << threeDcoord.x<<", "<<threeDcoord.y<<", "<<threeDcoord.z<<endl;
    }
    ratio = point_to_triangle(o, a1, a2, p, minDist);
    // cout << "2 "<< *minDist<<" ";
    // cout << "ratio : "<< ratio.x << ", " << ratio.y<<", "<<ratio.z<<endl;
    if(tmpDist>*minDist){
        tmpDist = *minDist;
        threeDcoord.x = ratio[0]*o_index.x + ratio[1]*a1_index.x + ratio[2]*a2_index.x;
        threeDcoord.y = ratio[0]*o_index.y + ratio[1]*a1_index.y + ratio[2]*a2_index.y;
        threeDcoord.z = ratio[0]*o_index.z + ratio[1]*a1_index.z + ratio[2]*a2_index.z;
        // cout <<"threeDCoord : " << threeDcoord.x<<", "<<threeDcoord.y<<", "<<threeDcoord.z<<endl;
    }
    ratio = point_to_triangle(a0, a1, a2, p, minDist);
    // cout << "3 "<< *minDist<<" ";
    // cout << "ratio : "<< ratio.x << ", " << ratio.y<<", "<<ratio.z<<endl;
    if(tmpDist>*minDist){
        tmpDist = *minDist;
        threeDcoord.x = ratio[0]*a0_index.x + ratio[1]*a1_index.x + ratio[2]*a2_index.x;
        threeDcoord.y = ratio[0]*a0_index.y + ratio[1]*a1_index.y + ratio[2]*a2_index.y;
        threeDcoord.z = ratio[0]*a0_index.z + ratio[1]*a1_index.z + ratio[2]*a2_index.z;
        // cout <<"threeDCoord : " << threeDcoord.x<<", "<<threeDcoord.y<<", "<<threeDcoord.z<<endl;

    }
    // cout <<"\nthreeDCoord : " << threeDcoord.x<<", "<<threeDcoord.y<<", "<<threeDcoord.z<<endl;
    // cout << "minDist : "<< *minDist<<endl;
    return threeDcoord;
}
glm::fvec2 carve_cls::surround_Triangles(const LatData_t* latticeData, double mid, glm::fvec3 voxelPos, glm::ivec3 minLatticeCoord){

    glm::fvec2 twoDcoord = {minLatticeCoord.x,minLatticeCoord.y};

    double minDist = mid;
    int impair[9][2] = {{1, 0}, {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}, {0,-1}, {1,-1}, {1, 0}};

    for(int i = 0; i < 8; i++){
        // find triangle(o,a1,a2)
        int a1_i = minLatticeCoord.x+impair[i][0];
        int a1_j = minLatticeCoord.y+impair[i][1];
        int a2_i = minLatticeCoord.x+impair[i+1][0];
        int a2_j = minLatticeCoord.y+impair[i+1][1];

        if(a1_i < 0 || a1_i > latticeData->width-1 ) continue;
        if(a1_j < 0 || a1_j > latticeData->height-1) continue;
        if(a2_i < 0 || a2_i > latticeData->width-1 ) continue;
        if(a2_j < 0 || a2_j > latticeData->height-1) continue;
        glm::fvec3 a1 = latticeData->wPos[minLatticeCoord.z][a1_j][a1_i];
        glm::fvec3 a2 = latticeData->wPos[minLatticeCoord.z][a2_j][a2_i];
        glm::fvec3 o = latticeData->wPos[minLatticeCoord.z][minLatticeCoord.y][minLatticeCoord.x];
        glm::fvec3 p = voxelPos;

        glm::fvec3 ratio = point_to_triangle(o, a1, a2, p, &minDist);

        if(ratio.x + ratio.y + ratio.z == -3){
            continue;
        }
        twoDcoord.x = ratio[0]*minLatticeCoord.x + ratio[1]*(a1_i) + ratio[2]*(a2_i);
        twoDcoord.y = ratio[0]*minLatticeCoord.y + ratio[1]*(a1_j) + ratio[2]*(a2_j);

        if(twoDcoord.x < 0.0) twoDcoord.x = 0.0;
        if(twoDcoord.x > latticeData->width-1) twoDcoord.x = latticeData->width-1;
        if(twoDcoord.y < 0.0) twoDcoord.y = 0.0;
        if(twoDcoord.y > latticeData->height-1) twoDcoord.y = latticeData->height-1;

    }

    return twoDcoord;

}
glm::fvec3 carve_cls::point_to_triangle(glm::fvec3 o, glm::fvec3 a1, glm::fvec3 a2, glm::fvec3 p, double* minDist){
    // Project the point p onto the plane where the triangle is located
    glm::fvec3 vector_n = glm::normalize(math.crossPruduct(a1-o, a2-o));
    glm::fvec3 vector_p = p-o;

    glm::fvec3 vector_d;
    vector_d.x = (-1*math.innerProduct(vector_p, vector_n))*vector_n.x;
    vector_d.y = (-1*math.innerProduct(vector_p, vector_n))*vector_n.y;
    vector_d.z = (-1*math.innerProduct(vector_p, vector_n))*vector_n.z;
    // find projection point
    glm::fvec3 projp = p + vector_d;

    // ensure the point is in the triangle
    glm::fvec3 cross1 = glm::normalize(math.crossPruduct(o-projp, a1-projp));
    glm::fvec3 cross2 = glm::normalize(math.crossPruduct(a1-projp, a2-projp));
    glm::fvec3 cross3 = glm::normalize(math.crossPruduct(a2-projp, o-projp));
    if(cross1.x*cross2.x < 0.0 || cross1.x*cross3.x < 0.0 || cross2.x*cross3.x < 0.0){
        // if outer triangle find close point or edgepoint

        projp = outer_projp(o, a1, a2, projp, p);
        vector_d = p - projp;
    }
    // glm::fvec3 ratio = barycentric_coord(o, a1, a2, projp, vector_n);
    // if(ratio[0]< 0 || ratio[0]>1 ||ratio[1]< 0 || ratio[1]>1||ratio[2]< 0 || ratio[2]>1){
    //     projp = outer_projp(o, a1, a2, projp, p);
    //     vector_d = p - projp;
    // }

    double tmpDist = vector_d.x*vector_d.x + vector_d.y*vector_d.y + vector_d.z*vector_d.z;
    if(tmpDist >= *minDist) {
        return glm::fvec3{-1,-1,-1};
    }
    *minDist = tmpDist;
    // compute dist of point to triangle
    glm::fvec3 ratio = barycentric_coord(o, a1, a2, projp, vector_n);
    return ratio;
}
glm::fvec3 carve_cls::outer_projp(glm::fvec3 o, glm::fvec3 a1, glm::fvec3 a2, glm::fvec3 projp, glm::fvec3 p){

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
    float ratio = math.innerProduct(a1-o, projp-o)/ (tmp.x*tmp.x + tmp.y*tmp.y + tmp.z*tmp.z);
    // cout <<"ratio : " <<ratio<<endl;
    tmp = p - ((a1-o)*ratio + o);
    tmpDist = tmp.x*tmp.x + tmp.y*tmp.y + tmp.z*tmp.z;
    // cout << tmpDist<< endl;;
    if(dist > tmpDist && ratio >= 0.0 && ratio <= 1.0){
        dist = tmpDist;
        newp = (a1-o)*ratio + o;
    }
    // o a2
    tmp = a2-o;
    ratio = math.innerProduct(a2-o, projp-o)/ (tmp.x*tmp.x + tmp.y*tmp.y + tmp.z*tmp.z);
    tmp = p - ((a2-o)*ratio + o);
    tmpDist = tmp.x*tmp.x + tmp.y*tmp.y + tmp.z*tmp.z;
    if(dist > tmpDist && ratio >= 0.0 && ratio <= 1.0){
        dist = tmpDist;
        newp = (a2-o)*ratio + o;
    }
    // a1 a2
    tmp = a2-a1;
    ratio = math.innerProduct(a2-a1, projp-a1)/ (tmp.x*tmp.x + tmp.y*tmp.y + tmp.z*tmp.z);
    tmp = p - ((a2-a1)*ratio + a1);
    tmpDist = tmp.x*tmp.x + tmp.y*tmp.y + tmp.z*tmp.z;
    if(dist > tmpDist && ratio >= 0.0 && ratio <= 1.0){
        dist = tmpDist;
        newp = (a2-a1)*ratio + a1;
    }

    return newp;

}
glm::fvec3 carve_cls::barycentric_coord(glm::fvec3 o, glm::fvec3 a1, glm::fvec3 a2, glm::fvec3 projp, glm::fvec3 vector_n){

    // compute center of gravity
    glm::fvec3 ratio;
    float total_volume = math.innerProduct(math.crossPruduct(a1-o, a2-o),vector_n);
    ratio[0] = math.innerProduct(math.crossPruduct(a1-projp, a2-projp),vector_n)/ total_volume;
    ratio[1] = math.innerProduct(math.crossPruduct(a2-projp, o-projp),vector_n)/ total_volume;
    ratio[2] = math.innerProduct(math.crossPruduct(o-projp, a1-projp),vector_n)/ total_volume;//1.0 - ratio[1] - ratio[0];

    return ratio;
}


