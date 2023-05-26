#include "Drawmodel.h"
model_cls drawModel;
void createThread();
void runthreadSomIter();
thread t1;
bool startSOM = false;


model_cls::model_cls(){
    glm::vec3 lightPos = glm::vec3(50.0,50.0,50.0);
    Camera camera(glm::vec3(0.0f, 5.0f, 15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}
model_cls::~model_cls(){
    destroy_world();
    cube.Item_del();
    ground.Item_del();
    lightcube.Item_del();
    voxel.Item_del();
    lattice_line.Item_del();
    lattice_plane.Item_del();
}

void model_cls::Shader_Create()
{
    rawmodel.LoadFile("raw/vase01.inf", "raw/vase01.raw");

    som.SOM_Create(rawmodel.Voxel_Position(), rawmodel.voxelModel.num, rawmodel.voxelModel.size);
    create_world(rawmodel.voxelModel);

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
    axis = Item(world.axis);
	Shader_init(0, true);
}
void model_cls::Modify_position(int x, int y, int z){
    // modify camera
    rate = max(max(x,y),z) / 2.0;
    camera.modifyPositionAndmoveSpeed(glm::vec3(x / -2.0, y / 2.0, z * 4.0), rate);

    // modify light
    lightPos = glm::vec3(x, y * 1.3, z * 2.0);
}
void model_cls::Shader_Use(){
    // som iter
    const LatData_t* latticeData = som.Lattice_get();
    if(latticeData->iter < latticeData->finalIter && startSOM){
        // som.SOM_IterateOnce();
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
void model_cls::Shader_init(int n, bool settex){
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
void model_cls::ViewProjection_Create(int n){

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
        shadowProj.Save(glm::perspective(glm::radians(90.0f), (float)tex.shadowTex.width / (float)tex.shadowTex.height, near_plane, far_plane));

        shadowTransforms.clear();
        shadowTransforms.push_back(shadowProj.Top() * glm::lookAt(lightPos, lightPos + glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)));
        shadowTransforms.push_back(shadowProj.Top() * glm::lookAt(lightPos, lightPos + glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)));
        shadowTransforms.push_back(shadowProj.Top() * glm::lookAt(lightPos, lightPos + glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)));
        shadowTransforms.push_back(shadowProj.Top() * glm::lookAt(lightPos, lightPos + glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)));
        shadowTransforms.push_back(shadowProj.Top() * glm::lookAt(lightPos, lightPos + glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)));
        shadowTransforms.push_back(shadowProj.Top() * glm::lookAt(lightPos, lightPos + glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f)));

    }
}
void model_cls::ourShader_model(){
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
   	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    tex.bindTexture(0,0);//texture
    tex.bindTexture(1,1);//depthtexture
    Model_Floor_Create(ourShader);
    Model_create(ourShader);
    Model_create_noshadow(ourShader);
}
void model_cls::lightShader_model(){
    Model_lightCube_create(lightShader);
}
void model_cls::depthShader_model(){
    glViewport(0, 0, tex.shadowTex.width, tex.shadowTex.height);
    glBindFramebuffer(GL_FRAMEBUFFER, tex.shadowTex.depthFBO);
        glClear(GL_DEPTH_BUFFER_BIT);
        tex.bindTexture(0,0);
        Model_create(depthShader);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void model_cls::Model_Floor_Create(Shader shader){
    // axis
    model.Push();
    shader.setBool("tex",false);
    shader.setBool("shader",false);
    // model.Save(glm::rotate(model.Top(), glm::radians(-90.0f), glm::vec3(0.0,1.0,0.0)));
    model.Save(glm::scale(model.Top(), glm::vec3( 20.0f, 20.0f, 20.0f)));
    shader.setMat4("model", model.Top());
    glBindVertexArray(axis.VAO);
    glDrawArrays(GL_LINES, 0, world.axis.size());
    model.Pop();
    // floor
    model.Push();
    model.Save(glm::scale(model.Top(), glm::vec3( 20000.0f, 1.0f, 20000.0f)));
    model.Save(glm::translate(model.Top(), glm::vec3(-0.5f, 0.0f, -0.5)));
    shader.setMat4("model", model.Top());
    shader.setBool("tex",false);
    shader.setBool("shader",true);
    glBindVertexArray(ground.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    model.Pop();

}
void model_cls::Model_create_noshadow(Shader shader){
    if(showLatticePlane){
        model.Push();
        // model.Save(glm::rotate(model.Top(), glm::radians(-90.0f), glm::vec3(0.0,1.0,0.0)));
        shader.setMat4("model", model.Top());
        if(texshow)
            shader.setBool("tex", true);
        else
            shader.setBool("tex", false);
        shader.setBool("shader",false);
        glBindVertexArray(lattice_plane.VAO);
        glDrawArrays(GL_TRIANGLES, 0, world.lattice_plane.size());
        model.Pop();
    }

    if(showLatticeLine){
        model.Push();
        // model.Save(glm::rotate(model.Top(), glm::radians(-90.0f), glm::vec3(0.0,1.0,0.0)));
        shader.setMat4("model", model.Top());
        if(texshow)
            shader.setBool("tex", true);
        else
            shader.setBool("tex", false);
        shader.setBool("shader",false);
        glBindVertexArray(lattice_line.VAO);
        glDrawArrays(GL_LINES, 0, world.lattice_line.size());
        model.Pop();
    }

}
void model_cls::Model_create(Shader shader){
    if(showVoxel){
        model.Push();
        // model.Save(glm::rotate(model.Top(), glm::radians(-90.0f), glm::vec3(0.0,1.0,0.0)));
        shader.setMat4("model", model.Top());
        shader.setBool("tex",false);
        shader.setBool("shader",false);
        glBindVertexArray(voxel.VAO);
        glDrawArrays(GL_TRIANGLES, 0, world.voxel.size());
        model.Pop();
    }

}
void model_cls::Model_lightCube_create(Shader shader){

    model.Push();
    model.Save(glm::translate(model.Top(),lightPos));
    model.Save(glm::scale(model.Top(), glm::vec3( 0.2f, 0.2f, 0.2f)));
    shader.setMat4("model", model.Top());
    glBindVertexArray(lightcube.VAO);
    glDrawArrays(GL_TRIANGLES, 0, world.lightcube.size());
    model.Pop();

}
void runthreadSomIter(){
    const LatData_t* latticeData = som.Lattice_get();
	while(latticeData->iter < latticeData->finalIter && startSOM){
		som.SOM_IterateOnce();
	}
}
void createThread(){
	if (t1.joinable()) {
		t1.join();
	}
	t1 = thread(runthreadSomIter);

}

void model_cls::Model_mapping(){
    const LatData_t* latticeData = som.Lattice_get();
    for(int n = 0; n < rawmodel.voxelModel.num; n++){// voxel
        double v_x = rawmodel.voxelModel.voxel[n].locate.x+0.5;
        double v_y = rawmodel.voxelModel.voxel[n].locate.y+0.5;
        double v_z = rawmodel.voxelModel.voxel[n].locate.z+0.5;
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
        glm::fvec2 trueMinLatticeCoordRate = {trueMinLatticeCoord.x/(latticeData->width-1), trueMinLatticeCoord.y/(latticeData->height-1)};
        glm::ivec2 imageRate = {(int)(trueMinLatticeCoordRate.x*(double)(tex.imageTex.width-1)), (int)(trueMinLatticeCoordRate.y*(double)(tex.imageTex.height-1))};

        rawmodel.voxelModel.voxel[n].color = tex.imageTex.image[imageRate.y][imageRate.x];
    }
    renew_voxel_color(rawmodel.voxelModel);
    voxel.renewVBO(world.voxel);
    log_info("end: model mapping\n");
}
glm::fvec2 model_cls::findMinDistPrecisePos(const LatData_t* latticeData, double mid, glm::fvec3 voxelPos, glm::ivec3 minLatticeCoord, int de){

    glm::fvec3 twoDcoord = minLatticeCoord;

    double minDist = mid;
    int impair[9][2] = {{1, 0}, {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}, {0,-1}, {1,-1}, {1, 0}};
    som.debugThreeCoord.push_back(latticeData->lattice[minLatticeCoord.z][minLatticeCoord.y][minLatticeCoord.x]);

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

        som.debugThreeCoord.pop_back();
        som.debugThreeCoord.push_back(projp);

        }

    return twoDcoord;

}
glm::fvec3 model_cls::outerProjp(glm::fvec3 o, glm::fvec3 a1, glm::fvec3 a2, glm::fvec3 projp, glm::fvec3 p){

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
glm::fvec3 model_cls::pointTotriangle(glm::fvec3 o, glm::fvec3 a1, glm::fvec3 a2, glm::fvec3 projp, glm::fvec3 vector_n){

    // compute center of gravity
    glm::fvec3 ratio;
    float total_volume = innerProduct(crossPruduct(a1-o, a2-o),vector_n);
    ratio[0] = innerProduct(crossPruduct(a1-projp, a2-projp),vector_n)/ total_volume;
    ratio[1] = innerProduct(crossPruduct(a2-projp, o-projp),vector_n)/ total_volume;
    ratio[2] = 1.0 - ratio[1] - ratio[0];

    return ratio;
}

glm::fvec3 model_cls::crossPruduct(glm::fvec3 a, glm::fvec3 b){
    glm::fvec3 c;
    c.x = a.y*b.z - a.z*b.y;
    c.y = -1*(a.x*b.z - a.z*b.x);
    c.z = a.x*b.y - a.y*b.x;

    return c;
}
float model_cls::innerProduct(glm::fvec3 a, glm::fvec3 b){
    return ((a.x*b.x) + (a.y*b.y) + (a.z*b.z));
}
