#include "Gui.h"

void imgui_init(GLFWwindow *window);
void imgui_create();
void imgui_end();
void imgui_funcbuttom();
void imgui_funcsom();
bool texshow = false;
void imgui_init(GLFWwindow *window){
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    ImGui::StyleColorsLight();
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}
void imgui_create(){

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();
    ImGui::ShowDemoWindow();
    ImGui::Begin("SOM_3D_voxel");
    imgui_funcbuttom();
    imgui_funcsom();

    ImGui::End();
}
void imgui_funcbuttom(){
    if(ImGui::Button("Start")) {
        startSOM = true;
        cout << "start" << endl;
        createThread();
    }

    ImGui::SameLine();
    if(ImGui::Button("curve")){
        drawModel.Model_mapping();
    }

    ImGui::SameLine();
    static int texnum = 0;
    const char* tex_types[2] = { "false", "true"};
    const char* tex_type = (texnum >= 0 && texnum < 2) ? tex_types[texnum] : "Unknown";
    ImGui::SliderInt("texture show", &texnum, 0, 1, tex_type);
    if(texnum == 0) texshow = false;
    else texshow = true;

    static int* blocker = (int*)calloc(rawmodel.voxelModel.blockNum, sizeof(int));
    const char* blockerNum[5] = {"block0", "block1", "block2", "block3", "block4"};
    for(int b = 1; b < rawmodel.voxelModel.blockNum; b++){
        if(blocker[b] == 0) blocker[b] = rawmodel.voxelModel.blockLocate[b];
        int left, right;
        left = rawmodel.voxelModel.blockLocate[b-1];
        right = rawmodel.voxelModel.blockLocate[b+1];

        ImGui::SliderInt(blockerNum[b], &blocker[b], left, right);
        if(blocker[b] != rawmodel.voxelModel.blockLocate[b]) {
            rawmodel.voxelModel.blockLocate[b] = blocker[b];
            rawmodel.Voxel_block_set();
            int blockNum = rawmodel.voxelModel.blockNum;
            int layerNum = rawmodel.voxelModel.somChioceLayerNum;
            for(int layer = 0; layer < layerNum; layer++){
                for(int block = 0; block < blockNum; block++){
                    int voxelNum = rawmodel.voxelModel.num[layer][block];
                    glm::ivec3 voxelMaxsize = rawmodel.voxelModel.maxsize[layer][block];
                    glm::ivec3 voxelMinsize = rawmodel.voxelModel.minsize[layer][block];
                    som[layer][block].Lattice_block_set(rawmodel.Voxel_Position(layer, block), voxelNum, voxelMaxsize, voxelMinsize);
                }
            }
            drawModel.Voxel_block_renew();
        }
    }

}
void imgui_funcsom(){
    int layerNum = rawmodel.voxelModel.somChioceLayerNum;
    int blockNum = rawmodel.voxelModel.blockNum;
    static bool init = true;

    const char* collapsingHeaderName[8][5] = {
        {"Layer 0 block 0", "Layer 0 block 1", "Layer 0 block 2", "Layer 0 block 3", "Layer 0 block 4"},
        {"Layer 1 block 0", "Layer 1 block 1", "Layer 1 block 2", "Layer 1 block 3", "Layer 1 block 4"},
        {"Layer 2 block 0", "Layer 2 block 1", "Layer 2 block 2", "Layer 2 block 3", "Layer 2 block 4"},
        {"Layer 3 block 0", "Layer 3 block 1", "Layer 3 block 2", "Layer 3 block 3", "Layer 3 block 4"},
        {"Layer 4 block 0", "Layer 4 block 1", "Layer 4 block 2", "Layer 4 block 3", "Layer 4 block 4"},
        {"Layer 5 block 0", "Layer 5 block 1", "Layer 5 block 2", "Layer 5 block 3", "Layer 5 block 4"},
        {"Layer 6 block 0", "Layer 6 block 1", "Layer 6 block 2", "Layer 6 block 3", "Layer 6 block 4"},
        {"Layer 7 block 0", "Layer 7 block 1", "Layer 7 block 2", "Layer 7 block 3", "Layer 7 block 4"},
    };
    static bool selection[8][5] ={
        {true, true, true, true, true},
        {true, true, true, true, true},
        {true, true, true, true, true},
        {true, true, true, true, true},
        {true, true, true, true, true},
        {true, true, true, true, true},
        {true, true, true, true, true},
        {true, true, true, true, true}
    };
    static int** tex = (int**)malloc(layerNum * sizeof(int*));
    static int** texRotate = (int**)malloc(layerNum * sizeof(int*));
    static glm::fvec2** texScale = (glm::fvec2**)malloc(layerNum * sizeof(glm::fvec2*));
    static glm::fvec2** texTranslate = (glm::fvec2**)malloc(layerNum * sizeof(glm::fvec2*));
    static int** lat = (int**)malloc(layerNum * sizeof(int*));
    static int** resolution = (int**)malloc(layerNum * sizeof(int*));
    static int** iter = (int**)malloc(layerNum * sizeof(int*));
    static float** radius = (float**)malloc(layerNum * sizeof(float*));
    static float** rate = (float**)malloc(layerNum * sizeof(float*));
    if(init){
        for(int layer = 0; layer < layerNum; layer++){
            tex[layer] = (int*)calloc(blockNum, sizeof(int));
            texRotate[layer] = (int*)calloc(blockNum, sizeof(int));
            texTranslate[layer] = (glm::fvec2*)calloc(blockNum, sizeof(glm::fvec2));
            texScale[layer] = (glm::fvec2*)calloc(blockNum, sizeof(glm::fvec2));
            lat[layer] = (int*)calloc(blockNum, sizeof(int));
            resolution[layer] = (int*)calloc(blockNum, sizeof(int));
            iter[layer] = (int*)calloc(blockNum, sizeof(int));
            radius[layer] = (float*)calloc(blockNum, sizeof(float));
            rate[layer] = (float*)calloc(blockNum, sizeof(float));
            for(int block = 0; block < blockNum; block++){
                texScale[layer][block].x = 1.0;
                texScale[layer][block].y = 1.0;
            }
        }
        init = false;
    }
    for(int layer = 0; layer < layerNum; layer++){
        for(int block = 0; block < blockNum; block++){

            ImGui::Selectable(collapsingHeaderName[layer][block],&selection[layer][block]);
            const LatData_t* latticeData = som[layer][block].Lattice_get();
            if (ImGui::CollapsingHeader(collapsingHeaderName[layer][block]))
            {
                // SurfaceVoxel.h    texTypeNum = 3
                ImGui::Text("texture");
                ImGui::RadioButton("hive", &tex[layer][block], 0); ImGui::SameLine();
                ImGui::RadioButton("pattern", &tex[layer][block], 1); ImGui::SameLine();
                ImGui::RadioButton("wb", &tex[layer][block], 2);
                ImGui::Text("- translate");
                ImGui::SliderFloat("x", &texTranslate[layer][block].x, -1, 1);
                ImGui::SliderFloat("y", &texTranslate[layer][block].y, -1, 1);
                ImGui::Text("- scale");
                ImGui::InputFloat("x ", &texScale[layer][block].x);
                ImGui::InputFloat("y ", &texScale[layer][block].y);
                ImGui::Text("- rotate");
                ImGui::SliderInt("degree", &texRotate[layer][block], 0, 360);

                ImGui::Text("lattice");
                ImGui::RadioButton("plane", &lat[layer][block], 0); ImGui::SameLine();
                ImGui::RadioButton("cylinder", &lat[layer][block], 1); ImGui::SameLine();
                ImGui::RadioButton("donut", &lat[layer][block], 2); ImGui::SameLine();
                ImGui::RadioButton("ball", &lat[layer][block], 3);

                ImGui::InputInt("input lattice size", &resolution[layer][block]);
                ImGui::Text("iter : %d",latticeData->iter); ImGui::SameLine();
                ImGui::InputInt("input finalIter", &iter[layer][block]);
                ImGui::Text("radius: %f", latticeData->radius); ImGui::SameLine();
                ImGui::InputFloat("input initRadius", &radius[layer][block]);
                ImGui::Text("learning_rate: %f", latticeData->learningRate); ImGui::SameLine();
                ImGui::InputFloat("input initRate", &rate[layer][block]);


            }
            if(resolution[layer][block] == 0) resolution[layer][block] = latticeData->width;
            if(iter[layer][block] == 0) iter[layer][block] = latticeData->finalIter;
            if(radius[layer][block] == 0) radius[layer][block] = latticeData->initRadius;
            if(rate[layer][block] == 0) rate[layer][block] = latticeData->initLearningRate;

            if(iter[layer][block] != latticeData->finalIter) som[layer][block].Lattice_iter_set(iter[layer][block]);
            if(radius[layer][block] != latticeData->initRadius) som[layer][block].Lattice_radius_set(radius[layer][block]);
            if(rate[layer][block] != latticeData->initLearningRate) som[layer][block].Lattice_rate_set(rate[layer][block]);
            if(resolution[layer][block] != latticeData->width){
                glm::ivec3 voxelMaxsize = rawmodel.voxelModel.maxsize[layer][block];
                glm::ivec3 voxelMinsize = rawmodel.voxelModel.minsize[layer][block];
                som[layer][block].Lattice_resolution_set(resolution[layer][block], voxelMaxsize, voxelMinsize);
                drawModel.Lattice_renew(layer, block);
            }
            if(lat[layer][block] != latticeData->type){
                glm::ivec3 voxelMaxsize = rawmodel.voxelModel.maxsize[layer][block];
                glm::ivec3 voxelMinsize = rawmodel.voxelModel.minsize[layer][block];
                som[layer][block].Lattice_type_set(lat[layer][block], voxelMaxsize, voxelMinsize);
                drawModel.Lattice_renew(layer, block);
            }
            int d_angle = drawModel.texInfo.angle;
            int t_angle = texRotate[layer][block];
            glm::fvec2 d_trans = drawModel.texInfo.translate;
            glm::fvec2 t_trans = texTranslate[layer][block];
            glm::fvec2 d_scale = drawModel.texInfo.scale;
            glm::fvec2 t_scale = texScale[layer][block];
            if(d_angle != t_angle || d_trans != t_trans || d_scale != t_scale){
                drawModel.texInfo.angle = texRotate[layer][block];
                drawModel.texInfo.translate = texTranslate[layer][block];
                drawModel.texInfo.scale = texScale[layer][block];

                drawModel.texture_m.Pop();
                drawModel.texture_m.Push();
                drawModel.texture_m.Save(glm::scale(drawModel.texture_m.Top(), glm::vec3(1.0/t_scale.x, 1.0/t_scale.y, 0.0)));
                drawModel.texture_m.Save(glm::translate(drawModel.texture_m.Top(), glm::vec3(-t_trans.x, -t_trans.y, 0.0f)));
                drawModel.texture_m.Save(glm::rotate(drawModel.texture_m.Top(), glm::radians((float)t_angle), glm::vec3(0.0,0.0,1.0)));

                drawModel.Lattice_renew(layer, block);
            }
            rawmodel.voxelModel.somVoxel[layer][block]->textype = tex[layer][block];
            drawModel.showEachPart[layer][block] = selection[layer][block];
        }
    }
}
void imgui_end(){

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
