#include "Drawmodel.h"
model_cls drawModel;
void createThread();
void runthreadSomIter();
thread t1;
bool startSOM = false;


model_cls::model_cls(){
    glm::vec3 lightPos = glm::vec3(50.0,50.0,50.0);
    Camera camera(glm::vec3(0.0f, 5.0f, 15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    int layerNum = rawmodel.voxelModel.somChioceLayerNum;
    somVoxel = (Item*)malloc(sizeof(Item) * layerNum);
    lattice_line = (Item*)malloc(sizeof(Item) * layerNum);
    lattice_plane = (Item*)malloc(sizeof(Item) * layerNum);
    showEachLayer = (bool*)malloc(sizeof(bool) * layerNum);

    for(int layer = 0; layer < layerNum; layer++){
        showEachLayer[layer] = true;
    }
    // startSOM = (bool*)malloc(sizeof(bool) * layerNum);

}
model_cls::~model_cls(){
    destroy_world();
    cube.Item_del();
    ground.Item_del();
    lightcube.Item_del();
    // voxel.Item_del();
    innerVoxel.Item_del();
    outerVoxel.Item_del();
    // lattice_line.Item_del();
    // lattice_plane.Item_del();

}

void model_cls::Shader_Create()
{
    // rawmodel.LoadFile("raw/donut.inf", "raw/donut.raw");
    rawmodel.LoadFile("raw/dist/ball67_dist.inf", "raw/dist/ball67_dist.raw");
    create_mutli_som(rawmodel.voxelModel.somChioceLayerNum);

    for(int layer = 0; layer < rawmodel.voxelModel.somChioceLayerNum; layer++){
        int voxelNum = rawmodel.voxelModel.num[layer];
        glm::ivec3 voxelMaxsize = rawmodel.voxelModel.maxsize[layer];
        glm::ivec3 voxelMinsize = rawmodel.voxelModel.minsize[layer];
        som[layer].SOM_Create(rawmodel.Voxel_Position(layer), voxelNum, voxelMaxsize, voxelMinsize, 1, layer);

    }
    create_world(rawmodel.voxelModel);

    Modify_position(rawmodel.infdata.resolution[0], rawmodel.infdata.resolution[1], rawmodel.infdata.resolution[2]);

    ourShader = Shader("shader/shader.vs", "shader/shader.fs");
    lightShader = Shader("shader/lightShader.vs", "shader/lightShader.fs");
    depthShader = Shader("shader/depthShader.vs", "shader/depthShader.fs", "shader/depthShader.gs");

    cube = Item(world.cube);
    ground = Item((world.square));
    lightcube = Item(world.lightcube);
    // voxel = Item(world.voxel);
    innerVoxel = Item(world.innerVoxel);
    outerVoxel = Item(world.outerVoxel);
    axis = Item(world.axis);
    for(int layer = 0; layer < rawmodel.voxelModel.somChioceLayerNum; layer++){
        somVoxel[layer] = Item(world.somVoxel[layer]);
        lattice_line[layer] = Item(world.l_lattice_line[layer]);
        lattice_plane[layer] = Item(world.l_lattice_plane[layer]);
    }
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
    for(int layer = 0; layer < rawmodel.voxelModel.somChioceLayerNum; layer++){
        const LatData_t* latticeData = som[layer].Lattice_get();
        if(latticeData->iter < latticeData->finalIter && startSOM){
            // som.SOM_IterateOnce();
            renew_world(rawmodel.voxelModel.somChioceLayerNum);
            lattice_line[layer].renewVBO(world.l_lattice_line[layer]);
            lattice_plane[layer].renewVBO(world.l_lattice_plane[layer]);
        }
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
        for(int layer = 0; layer < rawmodel.voxelModel.somChioceLayerNum; layer++){
            if(showEachLayer[layer]){
                model.Push();
                // model.Save(glm::rotate(model.Top(), glm::radians(-90.0f), glm::vec3(0.0,1.0,0.0)));
                shader.setMat4("model", model.Top());
                if(texshow)
                    shader.setBool("tex", true);
                else
                    shader.setBool("tex", false);
                shader.setBool("shader",false);
                glBindVertexArray(lattice_plane[layer].VAO);
                glDrawArrays(GL_TRIANGLES, 0, world.lattice_plane.size());
                model.Pop();
            }
        }
    }

    if(showLatticeLine){
        for(int layer = 0; layer < rawmodel.voxelModel.somChioceLayerNum; layer++){
            if(showEachLayer[layer]){
                model.Push();
                // model.Save(glm::rotate(model.Top(), glm::radians(-90.0f), glm::vec3(0.0,1.0,0.0)));
                shader.setMat4("model", model.Top());
                if(texshow)
                    shader.setBool("tex", true);
                else
                    shader.setBool("tex", false);
                shader.setBool("shader",false);
                glBindVertexArray(lattice_line[layer].VAO);
                glDrawArrays(GL_LINES, 0, world.lattice_line.size());
                model.Pop();
            }
        }
    }

}
void model_cls::Model_create(Shader shader){
    if(showVoxel){
        if(showOutSomIn[0]){
            model.Push();
            // model.Save(glm::rotate(model.Top(), glm::radians(-90.0f), glm::vec3(0.0,1.0,0.0)));
            shader.setMat4("model", model.Top());
            shader.setBool("tex",false);
            shader.setBool("shader",true);
            glBindVertexArray(outerVoxel.VAO);
            glDrawArrays(GL_TRIANGLES, 0, world.outerVoxel.size());
            model.Pop();
        }
        if(showOutSomIn[1]){
            for(int layer = 0; layer < rawmodel.voxelModel.somChioceLayerNum; layer++){
                if(showEachLayer[layer]){
                    model.Push();
                    // model.Save(glm::rotate(model.Top(), glm::radians(-90.0f), glm::vec3(0.0,1.0,0.0)));
                    shader.setMat4("model", model.Top());
                    shader.setBool("tex",false);
                    shader.setBool("shader",true);
                    glBindVertexArray(somVoxel[layer].VAO);
                    glDrawArrays(GL_TRIANGLES, 0, world.voxel.size());
                    model.Pop();

                }
            }
        }
        if(showOutSomIn[2]){
            model.Push();
            // model.Save(glm::rotate(model.Top(), glm::radians(-90.0f), glm::vec3(0.0,1.0,0.0)));
            cout << "ll" << endl;
            shader.setMat4("model", model.Top());
            cout << "ll" << endl;
            shader.setBool("tex",false);
            shader.setBool("shader",true);
            glBindVertexArray(innerVoxel.VAO);
            glDrawArrays(GL_TRIANGLES, 0, world.innerVoxel.size());
            model.Pop();
        }
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
    for(int layer = 0; layer < rawmodel.voxelModel.somChioceLayerNum; layer++){
        const LatData_t* latticeData = som[layer].Lattice_get();
        while(latticeData->iter < latticeData->finalIter && startSOM){
            som[layer].SOM_IterateOnce();
        }
    }
}
void createThread(){
	if (t1.joinable()) {
		t1.join();
	}
	t1 = thread(runthreadSomIter);

}

void model_cls::Model_mapping(){
        carve.voxel_mapping();

        renew_voxel_color(rawmodel.voxelModel);
    for(int layer = 0; layer < rawmodel.voxelModel.somChioceLayerNum; layer++){
        somVoxel[layer].renewVBO(world.somVoxel[layer]);
        cout << world.somVoxel[layer].size()<<endl;
    }
    log_info("end: model mapping\n");
}
