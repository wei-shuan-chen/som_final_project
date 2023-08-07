#include "Drawmodel.h"
model_cls drawModel;
void createThread();
void runthreadSomIter();
thread t1;
bool startSOM = false;


model_cls::model_cls(){
    glm::vec3 lightPos = glm::vec3(camera.Position.x,camera.Position.x,camera.Position.x);
    Camera camera(glm::vec3(0.0f, 5.0f, 15.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    int layerNum = rawmodel.voxelModel.somChioceLayerNum;
    somVoxel = (Item**)malloc(sizeof(Item*) * layerNum);
    lattice_line = (Item**)malloc(sizeof(Item*) * layerNum);
    lattice_plane = (Item**)malloc(sizeof(Item*) * layerNum);
    showEachPart = (bool**)malloc(sizeof(bool*) * layerNum);

    int blockNum = rawmodel.voxelModel.blockNum;
    for(int layer = 0; layer < layerNum; layer++){
        showEachPart[layer] = (bool*)malloc(sizeof(bool) * blockNum);
        somVoxel[layer] = (Item*)malloc(sizeof(Item)*blockNum);
        lattice_line[layer] = (Item*)malloc(sizeof(Item)*blockNum);
        lattice_plane[layer] = (Item*)malloc(sizeof(Item)*blockNum);
        for(int block = 0; block < blockNum; block++){
            showEachPart[layer][block] = true;
        }
    }
    texture_m.Save(glm::translate(texture_m.Top(), glm::vec3(0.5f, 0.5f, 0.0f)));
    texture_m.Push();
}
model_cls::~model_cls(){
    destroy_world();
    boundingbox.Item_del();
    ground.Item_del();
    lightcube.Item_del();
    innerVoxel.Item_del();
    outerVoxel.Item_del();

    int layerNum = rawmodel.voxelModel.somChioceLayerNum;
    int blockNum = rawmodel.voxelModel.blockNum;
    for(int layer = 0; layer < layerNum; layer++){
        for(int block = 0; block < blockNum; block++){
            somVoxel[layer][block].Item_del();
            lattice_line[layer][block].Item_del();
            lattice_plane[layer][block].Item_del();
        }
    }
}

void model_cls::Shader_Create()
{
    rawmodel.LoadFile("raw/input/vase_dist.inf", "raw/input/vase_df.raw");
    create_mutli_som(rawmodel.voxelModel.somChioceLayerNum, rawmodel.voxelModel.blockNum);

    for(int layer = 0; layer < rawmodel.voxelModel.somChioceLayerNum; layer++){
        for(int block = 0; block < rawmodel.voxelModel.blockNum; block++){
            int voxelNum = rawmodel.voxelModel.num[layer][block];
            glm::ivec3 voxelMaxsize = rawmodel.voxelModel.maxsize[layer][block];
            glm::ivec3 voxelMinsize = rawmodel.voxelModel.minsize[layer][block];
            som[layer][block].SOM_Create(rawmodel.Voxel_Position(layer, block), voxelNum, voxelMaxsize, voxelMinsize, 0);

        }
    }

    create_world(rawmodel.voxelModel);
    Modify_position(rawmodel.infdata.resolution[0], rawmodel.infdata.resolution[1], rawmodel.infdata.resolution[2]);

    rayShader = Shader("shader/rayShader.vs", "shader/rayShader.fs");
    shader = Shader("shader/shader.vs", "shader/shader.fs");
    depthShader = Shader("shader/depthShader.vs", "shader/depthShader.fs", "shader/depthShader.gs");

    boundingbox = Item(world.cube);
    ground = Item((world.square));
    lightcube = Item(world.cube);
    innerVoxel = Item(world.innerVoxel);
    outerVoxel = Item(world.outerVoxel);
    axis = Item(world.axis);
    for(int layer = 0; layer < rawmodel.voxelModel.somChioceLayerNum; layer++){
        for(int block = 0; block < rawmodel.voxelModel.blockNum; block++){
            somVoxel[layer][block] = Item(world.somVoxel[layer][block]);
            lattice_line[layer][block] = Item(world.l_lattice_line[layer][block]);
            lattice_plane[layer][block] = Item(world.l_lattice_plane[layer][block]);

        }
    }
	Shader_init(0, true);
	Shader_init(1, true);

}
void model_cls::Modify_position(int x, int y, int z){
    // modify camera
    rate = max(max(x,y),z) / 4.0;
    camera.modifyPositionAndmoveSpeed(glm::vec3(x / -2.0, y / 2.0, z * 2.0), rate);

    // modify light
    lightPos = glm::vec3(x, y * 1.3, z * 2.0);
}
void model_cls::Shader_Use(GLFWwindow *window){
    // som iter
    int blockNum = rawmodel.voxelModel.blockNum;
    int layerNum = rawmodel.voxelModel.somChioceLayerNum;
    for(int layer = 0; layer < layerNum; layer++){
        for(int block = 0; block < blockNum; block++){
            const LatData_t* latticeData = som[layer][block].Lattice_get();
            if(latticeData->iter < latticeData->finalIter && startSOM){
                // som.SOM_IterateOnce();
                renew_world(layerNum, blockNum, texture_m);
                lattice_line[layer][block].renewVBO(world.l_lattice_line[layer][block]);
                lattice_plane[layer][block].renewVBO(world.l_lattice_plane[layer][block]);
            }

        }
    }
    //depth shader
    ViewProjection_Create(2);
    Shader_init(2, true);
    depthShader_model(window);
    //our shader
    Shader_init(0, false);
    ViewProjection_Create(0);
    rayShader_model(window);
    //light shader
    Shader_init(1, false);
    ViewProjection_Create(1);
    shader_model();
}
void model_cls::Lattice_renew( int layer, int block){
    int blockNum = rawmodel.voxelModel.blockNum;
    int layerNum = rawmodel.voxelModel.somChioceLayerNum;
    renew_world(layerNum, blockNum, texture_m);
    lattice_line[layer][block].renewVBO(world.l_lattice_line[layer][block]);
    lattice_plane[layer][block].renewVBO(world.l_lattice_plane[layer][block]);
}
void model_cls::Voxel_block_renew(){
    int blockNum = rawmodel.voxelModel.blockNum;
    int layerNum = rawmodel.voxelModel.somChioceLayerNum;

    renew_voxel(rawmodel.voxelModel);
    renew_world(layerNum, blockNum, texture_m);
    for(int layer = 0; layer < layerNum; layer++){
        for(int block = 0; block < blockNum; block++){
            lattice_line[layer][block].renewVBO(world.l_lattice_line[layer][block]);
            lattice_plane[layer][block].renewVBO(world.l_lattice_plane[layer][block]);
            somVoxel[layer][block].renewVBO(world.somVoxel[layer][block]);
        }
    }

}
void model_cls::Shader_init(int n, bool settex){
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    // glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    if(n == 0){
        rayShader.use();
        if(settex){
            rayShader.setInt("shadowMap", 3);
            rayShader.setInt("intensityMap", 4);
            rayShader.setInt("colorMap", 5);
            rayShader.setFloat("bias", 1.0);
        }
    }else if(n == 1){
        shader.use();
        if(settex){
            shader.setInt("texturemap0", 0);
            shader.setInt("texturemap1", 1);
            shader.setInt("texturemap2", 2);
        }
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
        // projection.Save(glm::ortho(0.0f, (float)SCR_WIDTH, 0.0f, (float)SCR_HEIGHT, near_plane, far_plane));
        projection.Save(glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, near_plane, far_plane));
        rayShader.setMat4("view", view.Top());
        rayShader.setMat4("projection", projection.Top());
        rayShader.setVec3("viewPos", camera.Position);
        rayShader.setVec3("lightPos", lightPos);

        rayShader.setFloat("far_plane", far_plane);
    }else if(n == 1){
        shader.setMat4("view", view.Top());
        shader.setMat4("projection", projection.Top());
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
void model_cls::rayShader_model(GLFWwindow *window){
    glfwGetFramebufferSize(window, &SCR_WIDTH, &SCR_HEIGHT);
    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
   	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    tex.bindTexture(3);//depthtexture
    tex.bindTexture(4);
    tex.bindTexture(5);
    Model_bound_create(rayShader);
    Model_Floor_Create(rayShader);
}
void model_cls::shader_model(){
    Model_create_lattice_shadow(shader);
    Model_lightCube_create(shader);
}
void model_cls::depthShader_model(GLFWwindow *window){
    glfwGetFramebufferSize(window, &SCR_WIDTH, &SCR_HEIGHT);
    glViewport(0, 0, tex.shadowTex.width, tex.shadowTex.height);
    glBindFramebuffer(GL_FRAMEBUFFER, tex.shadowTex.depthFBO);
        glClear(GL_DEPTH_BUFFER_BIT);
        Model_create(depthShader);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void model_cls::Model_Floor_Create(Shader shader){
    // axis
    // model.Push();
    // // model.Save(glm::rotate(model.Top(), glm::radians(-90.0f), glm::vec3(0.0,1.0,0.0)));
    // model.Save(glm::scale(model.Top(), glm::vec3( 20.0f, 20.0f, 20.0f)));
    // shader.setMat4("model", model.Top());
    // glBindVertexArray(axis.VAO);
    // glDrawArrays(GL_LINES, 0, world.axis.size());
    // model.Pop();
    // floor
    model.Push();
    model.Save(glm::scale(model.Top(), glm::vec3( 20000.0f, 1.0f, 20000.0f)));
    model.Save(glm::translate(model.Top(), glm::vec3(-0.5f, 0.0f, -0.5)));
    shader.setMat4("model", model.Top());
    shader.setBool("ray", false);
    glBindVertexArray(ground.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    model.Pop();

}
void model_cls::Model_create_lattice_shadow(Shader shader){
    model.Push();
    model.Save(glm::scale(model.Top(), glm::vec3( 0.5f, 0.5f, 0.5f)));
    // model.Save(glm::rotate(model.Top(), glm::radians(-90.0f), glm::vec3(0.0,1.0,0.0)));
    shader.setMat4("model", model.Top());
    if(texshow) shader.setBool("tex", true);
    else shader.setBool("tex", false);

    int blockNum = rawmodel.voxelModel.blockNum;
    int layerNum = rawmodel.voxelModel.somChioceLayerNum;
    for(int layer = 0; layer < layerNum; layer++){
        for(int block = 0; block < blockNum; block++){

            int texType = rawmodel.voxelModel.somVoxel[layer][block]->textype;
            shader.setInt("texType", texType);
            tex.bindTexture(texType);//texture
            if(showEachPart[layer][block]){
                if(showLatticePlane){
                    glBindVertexArray(lattice_plane[layer][block].VAO);
                    glDrawArrays(GL_TRIANGLES, 0, world.l_lattice_plane[layer][block].size());
                }
                if(showLatticeLine){
                    glBindVertexArray(lattice_line[layer][block].VAO);
                    glDrawArrays(GL_LINES, 0, world.l_lattice_line[layer][block].size());
                }
            }
        }
    }
    model.Pop();
}
void  model_cls::Model_bound_create(Shader shader){
    model.Push();
    float x_s = rawmodel.infdata.resolution[1]/2.0;
    float y_s = rawmodel.infdata.resolution[2]/2.0;
    float z_s = rawmodel.infdata.resolution[0]/2.0;
    model.Save(glm::scale(model.Top(), glm::vec3(x_s, y_s, z_s)));
    shader.setVec3("modelSize", glm::vec3(x_s, y_s, z_s));//vector_matrix(model.Top(), glm::fvec4(rawmodel.infdata.resolution, 1.0)));
    shader.setBool("ray", true);

    if(showVoxel){
        shader.setMat4("model", model.Top());
        glBindVertexArray(boundingbox.VAO);
        glDrawArrays(GL_TRIANGLES, 0, world.cube.size());
    }
    model.Pop();
}
void model_cls::Model_create(Shader shader){
    model.Push();
    model.Save(glm::scale(model.Top(), glm::vec3( 0.5,0.5, 0.5)));
    shader.setVec3("modelSize", glm::vec3( 0.5,0.5, 0.5));
    shader.setBool("ray", false);
    shader.setMat4("model", model.Top());
    if(showVoxel){
        if(showOutSomIn[0]){
            glBindVertexArray(outerVoxel.VAO);
            glDrawArrays(GL_TRIANGLES, 0, world.outerVoxel.size());
        }
        if(showOutSomIn[1]){
            int blockNum = rawmodel.voxelModel.blockNum;
            int layerNum = rawmodel.voxelModel.somChioceLayerNum;
            for(int layer = 0; layer < layerNum; layer++){
                for(int block = 0; block < blockNum; block++){
                    if(showEachPart[layer][block]){
                        glBindVertexArray(somVoxel[layer][block].VAO);
                        glDrawArrays(GL_TRIANGLES, 0, world.somVoxel[layer][block].size());
                    }
                }
            }
        }
        if(showOutSomIn[2]){
            glBindVertexArray(innerVoxel.VAO);
            glDrawArrays(GL_TRIANGLES, 0, world.innerVoxel.size());
        }
    }
    model.Pop();
}
void model_cls::Model_lightCube_create(Shader shader){

    model.Push();
    model.Save(glm::translate(model.Top(),lightPos));
    model.Save(glm::scale(model.Top(), glm::vec3( 0.2f, 0.2f, 0.2f)));
    shader.setMat4("model", model.Top());
    shader.setBool("tex", false);
    glBindVertexArray(lightcube.VAO);
    glDrawArrays(GL_TRIANGLES, 0, world.lightcube.size());
    model.Pop();

}
void runthreadSomIter(){
    int blockNum = rawmodel.voxelModel.blockNum;
    int layerNum = rawmodel.voxelModel.somChioceLayerNum;
    for(int layer = 0; layer < layerNum; layer++){
        for(int block = 0; block < blockNum; block++){
            if(drawModel.showEachPart[layer][block]){
                LatData_t* latticeData = som[layer][block].Lattice_get();
                latticeData->iter = 0;
                while(latticeData->iter < latticeData->finalIter && startSOM){
                    som[layer][block].SOM_IterateOnce();
                }
            }
        }
    }
}
void createThread(){
	if (t1.joinable()) {
		t1.join();
	}
	t1 = thread(runthreadSomIter);

}
glm::fvec3 model_cls::vector_matrix(glm::mat4 matrix, glm::fvec4 vec){
    glm::fvec4 tmp = {0.0, 0.0, 0.0, 0.0};
    glm::fvec3 ans;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            tmp[i] += matrix[j][i]*vec[j];
        }
    }
    for(int i = 0; i < 3; i++){
        ans[i] = tmp[i]/tmp[3];
    }
    return ans;
}
void model_cls::Model_mapping(){

    int blockNum = rawmodel.voxelModel.blockNum;
    int layerNum = rawmodel.voxelModel.somChioceLayerNum;
    for(int layer = 0; layer < layerNum; layer++){
        for(int block = 0; block < blockNum; block++){
            if(showEachPart[layer][block]){
                carve.voxel_mapping(layer, block, texture_m);

                renew_voxel(rawmodel.voxelModel);
                somVoxel[layer][block].renewVBO(world.somVoxel[layer][block]);
            }
        }
    }
    log_info("end: model mapping\n");
}
