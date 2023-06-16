#include "Gui.h"

void imgui_init(GLFWwindow *window);
void imgui_create();
void imgui_end();
static int shape = -1;
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
    // if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
    // {
        // if (ImGui::BeginTabItem("information"))
        // {
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

            static bool selection[8] = { true, true, true, true, true, true, true, true};
            const char* shapes[8] = { "Layer 0", "Layer 1", "Layer 2", "Layer 3", "Layer 4", "Layer 5", "Layer 6", "Layer 7"};
            static int* tex = (int*)calloc(rawmodel.voxelModel.somChioceLayerNum, sizeof(int));
            static int* lat = (int*)calloc(rawmodel.voxelModel.somChioceLayerNum, sizeof(int));
            for(int layer = 0; layer < rawmodel.voxelModel.somChioceLayerNum; layer++){
                ImGui::Selectable(shapes[layer],&selection[layer]);

                const LatData_t* latticeData = som[layer].Lattice_get();
                if (ImGui::CollapsingHeader(shapes[layer]))
                {
                    // SurfaceVoxel.h    texTypeNum = 3
                    ImGui::Text("texture");
                    ImGui::RadioButton("hive", &tex[layer], 0); ImGui::SameLine();
                    ImGui::RadioButton("small hive", &tex[layer], 1); ImGui::SameLine();
                    ImGui::RadioButton("wb", &tex[layer], 2);

                    ImGui::Text("lattice");
                    ImGui::RadioButton("plane", &lat[layer], 0); ImGui::SameLine();
                    ImGui::RadioButton("cylinder", &lat[layer], 1); ImGui::SameLine();
                    ImGui::RadioButton("donut", &lat[layer], 2); ImGui::SameLine();
                    ImGui::RadioButton("ball", &lat[layer], 3);

                    ImGui::Text("iter : %d",latticeData->iter);
                    ImGui::Text("radius, %f", latticeData->radius);
                    ImGui::Text("learning_rate, %f", latticeData->learningRate);

                }
                if(lat[layer] != som[layer].latticeData.type){
                    drawModel.Lattice_renew(lat[layer], layer);
                }
                rawmodel.voxelModel.somVoxel[layer]->textype = tex[layer];
                drawModel.showEachLayer[layer] = selection[layer];
            }

        //     ImGui::EndTabItem();
        // }

        // if (ImGui::BeginTabItem("adjustment"))
        // {

        //     ImGui::EndTabItem();
        // }

        // ImGui::EndTabBar();
    // }


    ImGui::End();
}
void imgui_end(){

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
