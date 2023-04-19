#include "Drawmodel.h"

const unsigned int SCR_WIDTH = 800, SCR_HEIGHT = 600;
glm::vec3 lightPos = glm::vec3(50.0,50.0,50.0);
Camera camera(glm::vec3(0.0f, 5.0f, 15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
float rate;
bool showVoxel = true;
bool showLatticePlane = true;
bool showLatticeLine = true;
bool startSOM = false;

MatrixStack model;
MatrixStack view;
MatrixStack projection;
std::vector<glm::mat4> shadowTransforms;

Shader ourShader;
Shader lightShader;
Shader depthShader;

Item cube;
Item lightcube;
Item ground;
Item voxel;
Item lattice_line;
Item lattice_plane;

RAWmodel rawmodel;

float near_plane = 0.01f, far_plane = 10000000.0f;

// thread
thread t1;

//public func
void Shader_Create();
void Shader_Use();
void Model_del();
void Model_mapping();
//private func
void Modify_position(int x, int y, int z);
void Shader_init(int n, bool settex);
void ViewProjection_Create(int n);
void Model_Floor_Create(Shader shader);
void Model_create(Shader shader);
void Model_create_noshadow(Shader shader);
void Model_lightCube_create(Shader shader);
void ourShader_model();
void depthShader_model();
void lightShader_model();
glm::fvec2 findMinDistPrecisePos(const LatData* latticeData, double mid, glm::fvec3 voxelPos, glm::ivec3 minLatticeCoord, int de);
glm::fvec3 pointTotriangle(glm::fvec3 o, glm::fvec3 a1, glm::fvec3 a2, glm::fvec3 projp, glm::fvec3 vector_n);
glm::fvec3 crossPruduct(glm::fvec3 a, glm::fvec3 b);
float innerProduct(glm::fvec3 a, glm::fvec3 b);
// thread public
void createThread();
//thread private
void runthreadSomIter();

void Shader_Create()
{

    rawmodel.LoadFile("raw/vase01.inf", "raw/vase01.raw");
    // rawmodel.LoadFile("raw/ball67.inf", "raw/ball67.raw");
    // rawmodel.LoadFile("raw/utah_teapot.inf", "raw/utah_teapot.raw");
    // std::vector<glm::ivec3> voxelPosition;
    SOM_Create(rawmodel.Voxel_Position(), rawmodel.bounderNum, rawmodel.bounderMaxLocate);
    create_world(rawmodel.bounderVoxelData, rawmodel.bounderNum);

    Modify_position(rawmodel.infdata.resolution[0], rawmodel.infdata.resolution[1], rawmodel.infdata.resolution[2]);

    ourShader = Shader("shader/shader.vs", "shader/shader.fs");
    lightShader = Shader("shader/lightShader.vs", "shader/lightShader.fs");
    depthShader = Shader("shader/depthShader.vs", "shader/depthShader.fs", "shader/depthShader.gs");

    cube = Item(world.cube);
    ground = Item((world.square));
    lightcube = Item(world.lightcube);
    voxel = Item(world.voxel);
    lattice_line = Item(world.lattice_line);
    lattice_plane = Item(world.lattice_plane); 
	Shader_init(0, true);
}
void Modify_position(int x, int y, int z){
    // modify camera
    rate = max(max(x,y),z) / 2.0;
    camera.modifyPositionAndmoveSpeed(glm::vec3(x / -2.0, y / 2.0, z * 4.0), rate);

    // modify light
    lightPos = glm::vec3(x, y * 1.3, z * 2.0);
}
void Shader_Use(){
    // som iter
    const LatData* latticeData = Lattice_Struct_Use();
    if(latticeData->iter < latticeData->max_iter && startSOM){
        // SOM_IterateOnce();	
        renew_world();
        lattice_line.renewVBO(world.lattice_line);
		lattice_plane.renewVBO(world.lattice_plane);
    }
    
    //depth shader
    ViewProjection_Create(2);
    Shader_init(2, true);
    depthShader_model();
    //our shader
    Shader_init(0, false);
    ViewProjection_Create(0);
    ourShader_model();
    //light shader
    Shader_init(1, false);
    ViewProjection_Create(1);
    lightShader_model();
}
void Shader_init(int n, bool settex){
    if(n == 0){
        ourShader.use();
        if(settex){
            ourShader.setInt("texturemap", 0);
            ourShader.setInt("shadowMap", 1);
            ourShader.setFloat("bias", 1.0);
        }
    }else if(n == 1){
        lightShader.use();
    }else if(n == 2){
        depthShader.use(); 
        if(settex){
            for (unsigned int i = 0; i < 6; ++i)
                depthShader.setMat4("shadowMatrices[" + std::to_string(i) + "]", shadowTransforms[i]);
            depthShader.setFloat("far_plane", far_plane);
            depthShader.setVec3("lightPos", lightPos);
        }
    }
}   
void ViewProjection_Create(int n){
    
    if(n == 0){
        view.Save(camera.GetViewMatrix());
        projection.Save(glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, near_plane, far_plane));
        ourShader.setMat4("view", view.Top());
        ourShader.setMat4("projection", projection.Top());
        ourShader.setVec3("viewPos", camera.Position);
        ourShader.setVec3("lightPos", lightPos);
        ourShader.setFloat("far_plane", far_plane);
    }else if(n == 1){
        lightShader.setMat4("view", view.Top());
        lightShader.setMat4("projection", projection.Top());
    }else if(n == 2){
        MatrixStack shadowProj;
        shadowProj.Save(glm::perspective(glm::radians(90.0f), (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT, near_plane, far_plane));
        
        shadowTransforms.clear();
        shadowTransforms.push_back(shadowProj.Top() * glm::lookAt(lightPos, lightPos + glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)));
        shadowTransforms.push_back(shadowProj.Top() * glm::lookAt(lightPos, lightPos + glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)));
        shadowTransforms.push_back(shadowProj.Top() * glm::lookAt(lightPos, lightPos + glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)));
        shadowTransforms.push_back(shadowProj.Top() * glm::lookAt(lightPos, lightPos + glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)));
        shadowTransforms.push_back(shadowProj.Top() * glm::lookAt(lightPos, lightPos + glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)));
        shadowTransforms.push_back(shadowProj.Top() * glm::lookAt(lightPos, lightPos + glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f)));
  
    }
}
void ourShader_model(){
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
   	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    bindTexture(0,0);//texture
    bindTexture(1,1);//depthtexture
    Model_Floor_Create(ourShader);
    Model_create(ourShader);
    Model_create_noshadow(ourShader);
}
void lightShader_model(){
    Model_lightCube_create(lightShader);
}
void depthShader_model(){
    glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);
        glClear(GL_DEPTH_BUFFER_BIT);
        bindTexture(0,0);
        Model_create(depthShader);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void Model_Floor_Create(Shader shader){
    model.Push();
    model.Save(glm::scale(model.Top(), glm::vec3( 20000.0f, 1.0f, 20000.0f)));
    model.Save(glm::translate(model.Top(), glm::vec3(-0.5f, 0.0f, -0.5)));
    shader.setMat4("model", model.Top());
    shader.setBool("tex",false);
    shader.setBool("shader",true);
    glBindVertexArray(ground.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    model.Pop();
    // log_debug("%ld", ground.VAO);

}
void Model_create_noshadow(Shader shader){
    if(showLatticePlane){
        model.Push();
        model.Save(glm::rotate(model.Top(), glm::radians(-90.0f), glm::vec3(0.0,1.0,0.0)));
        shader.setMat4("model", model.Top());
        shader.setBool("shader",false);
        glBindVertexArray(lattice_plane.VAO);
        glDrawArrays(GL_TRIANGLES, 0, world.lattice_plane.size());
        model.Pop();
    }

    if(showLatticeLine){
        model.Push();
        model.Save(glm::rotate(model.Top(), glm::radians(-90.0f), glm::vec3(0.0,1.0,0.0)));
        shader.setMat4("model", model.Top());
        shader.setBool("shader",false);
        glBindVertexArray(lattice_line.VAO);
        glDrawArrays(GL_LINES, 0, world.lattice_line.size());
        model.Pop();
    }
    // if(showVoxel){
    //     model.Push();
    //     shader.setMat4("model", model.Top());
    //     shader.setBool("shader",true);
    //     shader.setBool("tex",false);
    //     glBindVertexArray(voxel.VAO);
    //     glDrawArrays(GL_TRIANGLES, 0, world.voxel.size());
    //     model.Pop();
    // }

}
void Model_create(Shader shader){
    if(showVoxel){
        model.Push();
        model.Save(glm::rotate(model.Top(), glm::radians(-90.0f), glm::vec3(0.0,1.0,0.0)));
        shader.setMat4("model", model.Top());
        shader.setBool("tex",false);
        glBindVertexArray(voxel.VAO);
        glDrawArrays(GL_TRIANGLES, 0, world.voxel.size());
        model.Pop();
    }

}
void Model_lightCube_create(Shader shader){

    model.Push();
    model.Save(glm::translate(model.Top(),lightPos));
    model.Save(glm::scale(model.Top(), glm::vec3( 0.2f, 0.2f, 0.2f)));
    shader.setMat4("model", model.Top());
    glBindVertexArray(lightcube.VAO);
    glDrawArrays(GL_TRIANGLES, 0, world.lightcube.size());
    model.Pop();

}
void runthreadSomIter(){
    const LatData* latticeData = Lattice_Struct_Use();
	while(latticeData->iter < latticeData->max_iter && startSOM){
		SOM_IterateOnce();			
	}
}
void createThread(){
	if (t1.joinable()) {
		t1.join();
	}
	t1 = thread(runthreadSomIter);
	
}
void Model_del(){
    SOM_Destroy();
    destroy_world();
    cube.Item_del();
    ground.Item_del();
    lightcube.Item_del();
    voxel.Item_del();
    lattice_line.Item_del();
    lattice_plane.Item_del();
}

void Model_mapping(){
    const LatData* latticeData = Lattice_Struct_Use();
    int shapeNum = 1;
    if(latticeData->shapeLattice == 4) shapeNum = 5;
    // for(int n = 2216; n < 2217; n++){// voxel
    for(int n = 0; n < rawmodel.bounderNum; n++){// voxel
        double v_x = rawmodel.bounderVoxelData[n].bounderVoxelLocate.x;
        double v_y = rawmodel.bounderVoxelData[n].bounderVoxelLocate.y;
        double v_z = rawmodel.bounderVoxelData[n].bounderVoxelLocate.z;
        double minDist = 100000;
        glm::ivec3 minLatticeCoord = {0,0,0};
        //lattice
        for(int k = 0; k < shapeNum; k++){
            for(int j = 0; j < latticeData->map_height; j++){
                for(int i = 0; i < latticeData->map_width; i++){
            
                    double l_x = latticeData->lattice[k][j][i].x;
                    double l_y = latticeData->lattice[k][j][i].y;
                    double l_z = latticeData->lattice[k][j][i].z;

                    double nowDist = (l_x-v_x)*(l_x-v_x) + (l_y-v_y)*(l_y-v_y) + (l_z-v_z)*(l_z-v_z);
                    if(nowDist < minDist){ // find minDist between voxel point and lattice point
                        minDist = nowDist;
                        minLatticeCoord = {i, j, k};
                        // log_info("\nminDist : %f, minLatticeCoord : %i, %i, %i\nvoxel : %f, %f, %f, lattice : %f, %f, %f", 
                        // minDist, minLatticeCoord.x, minLatticeCoord.y, minLatticeCoord.z, v_x, v_y, l_x, l_y, l_z);
                    }
                }
            }
        }
        // double l_x = latticeData->lattice[minLatticeCoord.z][minLatticeCoord.y][minLatticeCoord.x].x;
        // double l_y = latticeData->lattice[minLatticeCoord.z][minLatticeCoord.y][minLatticeCoord.x].y;
        // double l_z = latticeData->lattice[minLatticeCoord.z][minLatticeCoord.y][minLatticeCoord.x].z;
        // log_info("\nminDist : %f, minLatticeCoord : %i, %i, %i\nvoxel : %f, %f, %f, lattice : %f, %f, %f", 
        // minDist, minLatticeCoord.x, minLatticeCoord.y, minLatticeCoord.z, v_x, v_y, v_z, l_x, l_y, l_z);
        glm::fvec2 trueMinLatticeCoord = findMinDistPrecisePos(latticeData, minDist, {v_x, v_y, v_z}, minLatticeCoord, n);
        // log_info("trueminLatticeCoord : %f, %f", trueMinLatticeCoord.x, trueMinLatticeCoord.y);
        // find the color of minDist lattice
        glm::fvec2 trueMinLatticeCoordRate = {trueMinLatticeCoord.x/latticeData->map_width, trueMinLatticeCoord.y/latticeData->map_height};
        // log_info("trueminLatticeCoordRate : %f, %f\n\n", trueMinLatticeCoordRate.x, trueMinLatticeCoordRate.y);
        // glm::ivec2 imageRate = {(int)(trueMinLatticeCoordRate.x*(double)image_height), (int)(trueMinLatticeCoordRate.y*(double)image_width)};
        glm::ivec2 imageRate = {(int)(trueMinLatticeCoordRate.x*(double)image_width), (int)(trueMinLatticeCoordRate.y*(double)image_height)};
        // log_info("%f * %i\nimageRate : %i, %i\nimage: {%i, %i, %i}\n\n", 
        // trueMinLatticeCoordRate.y, image_height, imageRate.x, imageRate.y, image[imageRate.y][imageRate.x].x, image[imageRate.y][imageRate.x].y, image[imageRate.y][imageRate.x].z);
        // glm::ivec3 imageColor = image[imageRate.x][imageRate.y];
        rawmodel.bounderVoxelData[n].bounderVoxelColor = image[imageRate.y][imageRate.x];

    }
    renew_voxel_color(rawmodel.bounderVoxelData, rawmodel.bounderNum);
    voxel.renewVBO(world.voxel);
    log_info("end: model mapping\n");
}
glm::fvec2 findMinDistPrecisePos(const LatData* latticeData, double mid, glm::fvec3 voxelPos, glm::ivec3 minLatticeCoord, int de){
    
    glm::fvec3 twoDcoord[4] = {minLatticeCoord, minLatticeCoord, minLatticeCoord, minLatticeCoord};
    glm::fvec3 threeDcoord[4];
    double minDist = mid;
    int impair[4][2] = {{1,1} ,{-1,1}, {-1,-1}, {1,-1}};
    
    for(int i = 0; i < 4; i++){
        // find triangle(o,a1,a2)
        if(minLatticeCoord.x+impair[i][0] < 0 || minLatticeCoord.x+impair[i][0] > latticeData->map_width-1 || minLatticeCoord.y+impair[i][1] < 0 || minLatticeCoord.y+impair[i][1] > latticeData->map_height-1){
           continue;
        }
        glm::fvec3 a1 = latticeData->lattice[minLatticeCoord.z][minLatticeCoord.y][minLatticeCoord.x+impair[i][0]];
        glm::fvec3 a2 = latticeData->lattice[minLatticeCoord.z][minLatticeCoord.y+impair[i][1]][minLatticeCoord.x];
        glm::fvec3 o = threeDcoord[i] = latticeData->lattice[minLatticeCoord.z][minLatticeCoord.y][minLatticeCoord.x];
        glm::fvec3 p = voxelPos;

        // Project the point p onto the plane where the triangle is located
        glm::fvec3 vector_n = glm::normalize(crossPruduct(a1-o, a2-o));
        glm::fvec3 vector_p = p-o;

        glm::fvec3 vector_d = (-1*innerProduct(vector_n, vector_p))*vector_n;

        glm::fvec3 vector_projp = vector_p + vector_d;
        glm::fvec3 projp = o + vector_projp;


        // ensure the point is in the triangle
        glm::fvec3 cross1 = glm::normalize(crossPruduct(o-projp, a1-projp));
        glm::fvec3 cross2 = glm::normalize(crossPruduct(a1-projp, a2-projp));
        glm::fvec3 cross3 = glm::normalize(crossPruduct(a2-projp, o-projp));
        // log_info("%d\ncross1 : %f, %f, %f\ncross2 : %f, %f, %f\ncross3 : %f, %f, %f",
        // i, cross1.x, cross1.y, cross1.z, cross2.x, cross2.y, cross2.z, cross3.x, cross3.y, cross3.z);
        if(cross1.x*cross2.x < 0.0 || cross1.x*cross3.x < 0.0 || cross2.x*cross3.x < 0.0){
            continue;
        }
        
        // compute dist of point to triangle  
        glm::fvec3 rate = pointTotriangle(o, a1, a2, projp, vector_n);

        twoDcoord[i].x = rate[0]*minLatticeCoord.x + rate[1]*(minLatticeCoord.x+impair[i][0]) + rate[2]*minLatticeCoord.x;
        twoDcoord[i].y = rate[0]*minLatticeCoord.y + rate[1]*minLatticeCoord.y + rate[2]*(minLatticeCoord.y+impair[i][1]);
        threeDcoord[i] = rate[0]*o + rate[1]*a1 + rate[2]*a2;
        // log_info("finalcoord = {%f, %f}", finalcoord.x, finalcoord.y);
        // log_info("\no: %f, %f, %f\na1: %f, %f, %f\na2: %f, %f, %f\nprojp: %f, %f, %f\nrate: %f, %f, %f\nfinalcoord: %f, %f",
        // o.x, o.y, o.z, a1.x, a1.y, a1.z, a2.x, a2.y, a2.z, projp.x, projp.y, projp.z, rate.x, rate.y, rate.z, finalcoord.x, finalcoord.y);

    }
    int finalNum = 0;
    for(int j = 0; j < 4; j++){
        double a = threeDcoord[j].x - voxelPos.x;
        double b = threeDcoord[j].y - voxelPos.y;
        double c = threeDcoord[j].z - voxelPos.z;

        double tmpDist = a*a + b*b + c*c;
        if(tmpDist <= mid){
            mid = tmpDist;
            finalNum = j;
        }          
        
    }

    return twoDcoord[finalNum]; 

}

glm::fvec3 pointTotriangle(glm::fvec3 o, glm::fvec3 a1, glm::fvec3 a2, glm::fvec3 projp, glm::fvec3 vector_n){

    // compute center of gravity 
    glm::fvec3 rate;
    float total_volume = abs(innerProduct(crossPruduct(a1-o, a2-o),vector_n));
    rate[0] = abs(innerProduct(crossPruduct(a1-projp, a2-projp),vector_n)/ total_volume);
    rate[1] = abs(innerProduct(crossPruduct(a1-projp, o-projp),vector_n)/ total_volume);
    rate[2] = abs(innerProduct(crossPruduct(a2-projp, o-projp),vector_n)/ total_volume);

    if(rate[2] - (1-rate[0]-rate[1]) > 0.001){
        log_error("num = %f, error compute center of gravity coordinates!!!\nratenum : %f, %f, %f\ntotal volume : %f"
        , rate[2] - (1-rate[0]-rate[1]), rate[0], rate[1], rate[2], total_volume);
    }
    return rate;
}

glm::fvec3 crossPruduct(glm::fvec3 a, glm::fvec3 b){
    glm::fvec3 c;
    c.x = a.y*b.z - a.z*b.y;
    c.y = -1*(a.x*b.z - a.z*b.x);
    c.z = a.x*b.y - a.y*b.x;

    return c;
}
float innerProduct(glm::fvec3 a, glm::fvec3 b){
    return ((a.x*b.x) + (a.y*b.y) + (a.z*b.z));
}
/*
    

    // find the 4 triangle around the minDist point 
    double leftDist = mid, rightDist = mid, topDist = mid, downDist = mid;
    double v_x = voxelPos.x;
    double v_y = voxelPos.y;
    double v_z = voxelPos.z;
    if(minLatticeCoord.x != 0){//left
        double l_lx = latticeData->lattice[minLatticeCoord.z][minLatticeCoord.y][minLatticeCoord.x-1].x;
        double l_ly = latticeData->lattice[minLatticeCoord.z][minLatticeCoord.y][minLatticeCoord.x-1].y;
        double l_lz = latticeData->lattice[minLatticeCoord.z][minLatticeCoord.y][minLatticeCoord.x-1].z;
        leftDist = (l_lx-v_x)*(l_lx-v_x) + (l_ly-v_y)*(l_ly-v_y) + (l_lz-v_z)*(l_lz-v_z);
    }
    if(minLatticeCoord.x != latticeData->map_width-1){//right
        double l_rx = latticeData->lattice[minLatticeCoord.z][minLatticeCoord.y][minLatticeCoord.x+1].x;
        double l_ry = latticeData->lattice[minLatticeCoord.z][minLatticeCoord.y][minLatticeCoord.x+1].y;
        double l_rz = latticeData->lattice[minLatticeCoord.z][minLatticeCoord.y][minLatticeCoord.x+1].z;
        rightDist = (l_rx-v_x)*(l_rx-v_x) + (l_ry-v_y)*(l_ry-v_y) + (l_rz-v_z)*(l_rz-v_z);
    }
    if(minLatticeCoord.y != 0){//down
        double l_dx = latticeData->lattice[minLatticeCoord.z][minLatticeCoord.y-1][minLatticeCoord.x].x;
        double l_dy = latticeData->lattice[minLatticeCoord.z][minLatticeCoord.y-1][minLatticeCoord.x].y;
        double l_dz = latticeData->lattice[minLatticeCoord.z][minLatticeCoord.y-1][minLatticeCoord.x].z;
        downDist = (l_dx-v_x)*(l_dx-v_x) + (l_dy-v_y)*(l_dy-v_y) + (l_dz-v_z)*(l_dz-v_z);
    }
    if(minLatticeCoord.y != latticeData->map_height-1){//top
        double l_tx = latticeData->lattice[minLatticeCoord.z][minLatticeCoord.y+1][minLatticeCoord.x].x;
        double l_ty = latticeData->lattice[minLatticeCoord.z][minLatticeCoord.y+1][minLatticeCoord.x].y;
        double l_tz = latticeData->lattice[minLatticeCoord.z][minLatticeCoord.y+1][minLatticeCoord.x].z;
        topDist = (l_tx-v_x)*(l_tx-v_x) + (l_ty-v_y)*(l_ty-v_y) + (l_tz-v_z)*(l_tz-v_z);
    }
    
    // find which triangle is most close
    glm::ivec3 coord = minLatticeCoord;
    // -----
    if(leftDist < mid){
        coord.x -= 1;
    }
    if(rightDist < mid){
        coord.x += 1;
    }
    // |||||
    if(topDist < mid){
        coord.y += 1;
    }
    if(downDist < mid){
        coord.y -= 1;
    }
    log_info("\ncoord: %i, %i\nminCoord : %i, %i\ntop: %f, down: %f, left: %f, right: %f", 
    coord.x, coord.y, minLatticeCoord.x, minLatticeCoord.y, topDist, downDist, leftDist, rightDist);
    // find the true point, which is mindist
    glm::fvec2 finalcoord = {minLatticeCoord.x, minLatticeCoord.y};
    if(coord == minLatticeCoord) return finalcoord;
    if(coord.x == minLatticeCoord.x){
        finalcoord.y = ((double)coord.y + (double)minLatticeCoord.y)/ 2.0;
        return finalcoord;
    }
    if(coord.y == minLatticeCoord.y){
        finalcoord.x = ((double)coord.x + (double)minLatticeCoord.x)/ 2.0;

        return finalcoord;
    }
    // find point to triangle dist
    int impair[4][2] = {{1,1} ,{-1,1}, {-1,-1}, {1,-1}};
    int now_impair[2] = {0,0};
    if(coord.x > minLatticeCoord.x && coord.y > minLatticeCoord.y){
        now_impair[0] = impair[0][0];
        now_impair[1] = impair[0][1];
    }else if(coord.x < minLatticeCoord.x && coord.y > minLatticeCoord.y){
        now_impair[0] = impair[1][0];
        now_impair[1] = impair[1][1];
    }else if(coord.x < minLatticeCoord.x && coord.y < minLatticeCoord.y){
        now_impair[0] = impair[2][0];
        now_impair[1] = impair[2][1];
    }else if(coord.x > minLatticeCoord.x && coord.y < minLatticeCoord.y){
        now_impair[0] = impair[3][0];
        now_impair[1] = impair[3][1];
    }else{
        log_error("coord = {%f, %f, %f}, minLatticeCoord = {%f, %f, %f}\n", 
            coord.x,coord.y, coord.z, minLatticeCoord.x, minLatticeCoord.y, minLatticeCoord.z);
    }
    
    glm::fvec3 o = latticeData->lattice[minLatticeCoord.z][minLatticeCoord.y][minLatticeCoord.x];
    glm::fvec3 a1 = latticeData->lattice[minLatticeCoord.z][minLatticeCoord.y][minLatticeCoord.x+now_impair[0]];
    glm::fvec3 a2 = latticeData->lattice[minLatticeCoord.z][minLatticeCoord.y+now_impair[1]][minLatticeCoord.x];
    glm::fvec3 p = voxelPos;

    glm::fvec3 rate = pointTotriangle(o, a1, a2, p);

    finalcoord.x = rate[0]*minLatticeCoord.x + rate[1]*(minLatticeCoord.x+now_impair[0]) + rate[2]*minLatticeCoord.x;
    finalcoord.y = rate[0]*minLatticeCoord.y + rate[1]*minLatticeCoord.y + rate[2]*(minLatticeCoord.y+now_impair[1]);
    return finalcoord; 

*/