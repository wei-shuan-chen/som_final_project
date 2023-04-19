#include "Gui.h"

void imgui_init(GLFWwindow *window);
void imgui_create();
void imgui_end();
static int shape = -1;

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

    const char* shapes[] = { "random cylinder", "cylinder", "random flat", "flat", "halfball", "donut" };
    
    const LatData* latticeData = Lattice_Struct_Use();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
   
    ImGui::NewFrame();
    // ImGui::ShowDemoWindow();
    ImGui::Begin("SOM_3D_voxel");
    ImGui::Text("iter : %d",latticeData->iter);
    ImGui::Text("radius, %f", latticeData->neighbor);
    ImGui::Text("learning_rate, %f", latticeData->learning_rate);
    ImGui::Combo("init lattice shape", &shape, shapes, IM_ARRAYSIZE(shapes)); 
    if(ImGui::Button("Start")) {
        startSOM = true;
        cout << "start" << endl;
        createThread();
    }
    if(ImGui::Button("Mapping")){
        Model_mapping();
    }
    if(ImGui::Button("Again")){
        startSOM = false; 
    }

    ImGui::End();
}
int shape_init(){
    return shape;
}
void imgui_end(){
    				
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
