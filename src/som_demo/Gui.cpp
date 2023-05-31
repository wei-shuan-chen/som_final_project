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


    const LatData_t* latticeData = som.Lattice_get();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();
    // ImGui::ShowDemoWindow();
    ImGui::Begin("SOM_3D_voxel");
    if (ImGui::BeginTabBar("##tabs", ImGuiTabBarFlags_None))
    {
        if (ImGui::BeginTabItem("information"))
        {
            ImGui::Text("iter : %d",latticeData->iter);
            ImGui::Text("radius, %f", latticeData->radius);
            ImGui::Text("learning_rate, %f", latticeData->learningRate);

            if(ImGui::Button("Start")) {
                startSOM = true;
                cout << "start" << endl;
                createThread();
            }
            if(ImGui::Button("curve")){
                drawModel.Model_mapping();
            }
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("adjustment"))
        {
            static int texnum = 0;
            const char* tex_types[2] = { "false", "true"};
            const char* tex_type = (texnum >= 0 && texnum < 2) ? tex_types[texnum] : "Unknown";
            ImGui::SliderInt("texture show", &texnum, 0, 1, tex_type);
            if(texnum == 0) texshow = false;
            else texshow = true;

            ImGui::Text("\nsom_layer");

            static bool selection[4] = { true, true, true, true};
            const char* shapes[4] = { "Layer 0", "Layer 1", "Layer 2", "Layer 3"};
            for(int layer = 0; layer < rawmodel.voxelModel.somChioceLayerNum; layer++){
                ImGui::Selectable(shapes[layer],&selection[layer]);
            }

            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    // ImGui::Combo("init lattice shape", &shape, shapes, IM_ARRAYSIZE(shapes));

    // if(ImGui::Button("Again")){
    //     startSOM = false;
    // }

    ImGui::End();
}
void imgui_end(){

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
