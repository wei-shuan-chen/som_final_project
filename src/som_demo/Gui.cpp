#include "Gui.h"

TransferFunctionWidget rgba(tex.colormapTex.color + 1);
void imgui_init(GLFWwindow *window);
void imgui_create();
void imgui_end();
void imgui_funcbuttom();
void imgui_roi();
void imgui_funcsom();
void imgui_funcpsom();
bool texshow = false;
int weightType_gui = POS;
int som_psom = 0;
// static float f_translate[3] = {0.0f, 70.0f, 0.0f};
// static float f_scale[3] = {100.0f, 50.0f, 100.0f};
static float f_translate[3] = {0.0f, 00.0f, 0.0f};
static float f_scale[3] = {300.0f, 500.0f, 300.0f};
static glm::mat3x3 m_inverse;
bool curve = false;
void imgui_init(GLFWwindow *window)
{
    // GL 3.0 + GLSL 130
    const char *glsl_version = "#version 130";
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO &io = ImGui::GetIO();
    (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();
    //  Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}
void imgui_create()
{

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    ImGui::NewFrame();
    // ImGui::ShowDemoWindow();
    ImGui::Begin("SOM_3D_voxel");
    imgui_funcbuttom();
    imgui_roi();
    if (som_psom == SHOWSOM)
    {
        imgui_funcsom();
    }
    if (som_psom == SHOWPSOM)
    {
        imgui_funcpsom();
    }

    ImGui::End();
    // ImGui::Begin("TransferFunction");
    // if (rgba.Render() || tex.colormapTex.data[0] == -1)
    // {
    //     tex.updata_colorMap(rgba.TransferFunction());
    // }
    // ImGui::End();
}
void imgui_funcbuttom()
{
    if (ImGui::Button("Start"))
    {
        // if(som_psom == SOM ||(som_psom == PSOM && rawmodel.voxelModel.psomVoxel.size() >= 0)){

        startSOM = true;
        if (weightType_gui == POS)
            cout << "start position" << endl;
        if (weightType_gui == TEX)
            cout << "start texture" << endl;
        createvoxelThread();
    }
    ImGui::SameLine();

    curve = false;
    if (ImGui::Button("carve"))
    {
        curve = true;
    }
    ImGui::SameLine();
    if (ImGui::Button("load raw"))
    {
        rawmodel.LoadOutputFile("raw/output/vase3D.raw");
    }

    // chice weight type(pos or tex)
    static int wnum = 0;
    const char *w_types[2] = {"POS", "TEX"};
    const char *w_type = (wnum >= 0 && wnum < 2) ? w_types[wnum] : "Unknown";
    ImGui::SliderInt("weight chioce", &wnum, 0, 1, w_type);
    if (wnum == 0)
        weightType_gui = POS;
    else
        weightType_gui = TEX;

    /// show texture on lattice
    static int texnum = 0;
    const char *tex_types[2] = {"false", "true"};
    const char *tex_type = (texnum >= 0 && texnum < 2) ? tex_types[texnum] : "Unknown";
    ImGui::SliderInt("texture show", &texnum, 0, 1, tex_type);
    if (texnum == 0)
        texshow = false;
    else
        texshow = true;

    // lattice to texture filtering
    static int lt_filnum = 0;
    const char *lt_fil_types[2] = {"linear", "nearest"};
    const char *lt_fil_type = (lt_filnum >= 0 && lt_filnum < 2) ? lt_fil_types[lt_filnum] : "Unknown";
    ImGui::SliderInt("filter (texture to lattice)", &lt_filnum, 0, 1, lt_fil_type);
    if (lt_filnum == LINEAR)
        carve.latticeTextureFilter = LINEAR;
    else
        carve.latticeTextureFilter = NEAREST;
    // lattice to voxel filtering
    static int lv_filnum = 0;
    const char *lv_fil_types[2] = {"linear", "nearest"};
    const char *lv_fil_type = (lv_filnum >= 0 && lv_filnum < 2) ? lv_fil_types[lv_filnum] : "Unknown";
    ImGui::SliderInt("filter (voxel to lattice)", &lv_filnum, 0, 1, lv_fil_type);
    if (lv_filnum == LINEAR)
        carve.latticeVoxelFilter = LINEAR;
    else
        carve.latticeVoxelFilter = NEAREST;
    // // som or psom
    // static int somnum = SHOWSOM;
    // const char *som_types[2] = {"som", "psom"};
    // const char *som_type = (somnum >= 0 && somnum < 2) ? som_types[somnum] : "Unknown";
    // ImGui::SliderInt("som / psom", &somnum, 0, 1, som_type);
    // if (somnum == SHOWSOM)
    //     som_psom = SHOWSOM;
    // else
    //     som_psom = SHOWPSOM;

    static int showType = 0;
    ImGui::RadioButton("texturing", &showType, 0);
    ImGui::SameLine();
    ImGui::RadioButton("yin carveing", &showType, 1);
    ImGui::SameLine();
    ImGui::RadioButton("yan carveing", &showType, 2);
    if (showType != showVoxelType)
    {
        showVoxelType = showType;
        drawModel.Voxel_renew();
        // renew_voxel(rawmodel.voxelModel);

    }
}
void imgui_roi()
{
    static int b_s_ps = SHOWSOM;
    static glm::mat3x3 m_axis = {1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0};
    static glm::vec3 v_translate = {0.0, 0.0, 0.0};
    static float x_axis[3] = {1.0f, 0.0f, 0.0f};
    static float y_axis[3] = {0.0f, 1.0f, 0.0f};
    static float z_axis[3] = {0.0f, 0.0f, 1.0f};
    // static float x_axis[3] = {1.0f, 0.1f, 0.0f};
    // static float y_axis[3] = {-1.0f, 2.0f, -3.0f};
    // static float z_axis[3] = {0.0f, 0.4f, 1.0f};
    ImGui::Text("ROI axis");
    ImGui::InputFloat3("x_axis", x_axis);
    ImGui::InputFloat3("y_axis", y_axis);
    ImGui::InputFloat3("z_axis", z_axis);
    ImGui::InputFloat3("translate", f_translate);
    ImGui::InputFloat3("scale", f_scale);

    glm::mat3x3 m_tmp = {x_axis[0] * f_scale[0], y_axis[0] * f_scale[1], z_axis[0] * f_scale[2],
                         x_axis[1] * f_scale[0], y_axis[1] * f_scale[1], z_axis[1] * f_scale[2],
                         x_axis[2] * f_scale[0], y_axis[2] * f_scale[1], z_axis[2] * f_scale[2]};
    bool c[2] = {false, false};
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (m_axis[i][j] != m_tmp[i][j])
            {
                c[0] = true;
                m_axis[i][j] = m_tmp[i][j];
            }
        }
        if (v_translate[i] != f_translate[i])
        {
            c[1] = true;
            v_translate[i] = f_translate[i];
        }
    }
    if (c[1] || c[0])
    {
        int layerNum = rawmodel.voxelModel.somChioceLayerNum;
        int blockNum = rawmodel.voxelModel.blockNum;
        m_inverse = math.inverseMatrix3(m_axis);
        // for(int i = 0; i < 3; i++){
        //     for(int j= 0; j < 3; j++){
        //         cout << m_axis[i][j]<<" ";
        //     }
        //     cout <<"\n";
        // }
        // cout <<"\ninverse\n";
        // for(int i = 0; i < 3; i++){
        //     for(int j= 0; j < 3; j++){
        //         cout << m_inverse[i][j]<<" ";
        //     }
        //     cout <<"\n";
        // }
        // cout <<"\n\n";
        drawModel.psom_axis_renew(m_axis, v_translate);
        if (som_psom == SHOWSOM || b_s_ps == SHOWPSOM)
        {
            b_s_ps = SHOWSOM;
            bool renew = rawmodel.choice_somvoxel(m_inverse, f_translate, f_scale, true);
            if (renew)
            {
                for (int layer = 0; layer < layerNum; layer++)
                {
                    for (int block = 0; block < blockNum; block++)
                    {
                        int voxelNum = rawmodel.voxelModel.voxelnum[layer][block];

                        glm::ivec3 voxelMaxsize = rawmodel.voxelModel.maxsize[layer][block];
                        glm::ivec3 voxelMinsize = rawmodel.voxelModel.minsize[layer][block];
                        som[layer][block].Lattice_pos_set(rawmodel.Voxel_Position(layer, block), voxelNum, voxelMaxsize, voxelMinsize);
                        drawModel.Voxel_Lattice_renew();
                    }
                }
            }
        }
        if (som_psom == SHOWPSOM || b_s_ps == SHOWSOM)
        {
            b_s_ps = SHOWPSOM;
            bool renew = rawmodel.choice_psomvoxel(m_inverse, v_translate);
            if (renew)
            {
                std::vector<glm::ivec3> pvoxelPos = rawmodel.pVoxel_Position();
                int pvoxelNum = rawmodel.pvoxelModel.psomVoxel.size();
                psom.Lattice_pos_set(pvoxelPos, pvoxelNum, rawmodel.pvoxelModel.maxsize, rawmodel.pvoxelModel.minsize);
                drawModel.pVoxel_Lattice_renew();
            }
        }
    }
}
void imgui_funcpsom()
{
    static bool pinit = true;

    const LatData_t *latticeData = psom.Lattice_get();
    static int pcarnum = 0;
    const char *pcar_types[2] = {"false", "true"};
    const char *pcar_type = (pcarnum >= 0 && pcarnum < 2) ? pcar_types[pcarnum] : "Unknown";
    ImGui::SliderInt("pcarve show", &pcarnum, 0, 1, pcar_type);
    if (pcarnum == 0)
        carve.pcarve = false;
    else
        carve.pcarve = true;

    // texture matrix
    static float *ptexScale = (float *)calloc(3, sizeof(float));
    static float *ptexTranslate = (float *)calloc(3, sizeof(float));
    static int *ptexRotate = (int *)calloc(3, sizeof(int));
    static float *ptexResolution_w = (float *)calloc(2, sizeof(float));
    static float *ptexResolution_h = (float *)calloc(2, sizeof(float));
    static float *ptexResolution_d = (float *)calloc(2, sizeof(float));
    static int ptexWrap = 0;
    static int **anchor = (int **)malloc(sizeof(int *) * 8);
    if (pinit)
    {
        ptexScale[0] = 1;
        ptexScale[1] = 1;
        ptexScale[2] = 1;
        ptexResolution_w[1] = 1.0;
        ptexResolution_h[1] = 1.0;
        ptexResolution_d[1] = 1.0;
        pinit = false;

        for (int i = 0; i < 8; i++)
            anchor[i] = (int *)calloc(3, sizeof(int)); // zyx
        anchor[1][0] = latticeData->width - 1;
        anchor[2][1] = latticeData->height - 1;
        anchor[2][0] = latticeData->width - 1;
        anchor[3][1] = latticeData->height - 1;

        anchor[4][2] = latticeData->depth - 1;
        anchor[5][2] = latticeData->depth - 1;
        anchor[5][0] = latticeData->width - 1;
        anchor[6][2] = latticeData->depth - 1;
        anchor[6][1] = latticeData->height - 1;
        anchor[6][0] = latticeData->width - 1;
        anchor[7][2] = latticeData->depth - 1;
        anchor[7][1] = latticeData->height - 1;
    }
    // anchor point
    ImGui::Text("anchor point xyz");
    ImGui::InputInt3("000", anchor[0]);
    ImGui::InputInt3("001", anchor[1]);
    ImGui::InputInt3("011", anchor[2]);
    ImGui::InputInt3("010", anchor[3]);
    ImGui::InputInt3("100", anchor[4]);
    ImGui::InputInt3("101", anchor[5]);
    ImGui::InputInt3("111", anchor[6]);
    ImGui::InputInt3("110", anchor[7]);
    // texture wrapping
    ImGui::Text("texture wrap");
    ImGui::RadioButton("repeat p", &ptexWrap, 0);
    ImGui::SameLine();
    ImGui::RadioButton("border p", &ptexWrap, 1);
    // texture resolution
    ImGui::Text("texture resolution");
    ImGui::InputFloat2("width p", ptexResolution_w);
    ImGui::InputFloat2("height p", ptexResolution_h);
    ImGui::InputFloat2("depth p", ptexResolution_d);
    // texture matrix
    ImGui::Text("texture matrix");
    ImGui::SliderFloat3("translate_ptex", ptexTranslate, -1, 1);
    ImGui::InputFloat3("scale_ptex", ptexScale);
    ImGui::SliderInt3("rotate_ptex(hw dh dw)", ptexRotate, 0, 360);

    ImGui::Text("iter : %d", latticeData->iter[weightType_gui]);

    glm::ivec3 *p = latticeData->anchorEdgeP;
    bool anchor_c = false;
    for (int i = 0; i < 8; i++)
    {
        if (p[i][0] != anchor[i][0] || p[i][1] != anchor[i][1] || p[i][2] != anchor[i][2])
        {
            p[i][0] = anchor[i][0];
            p[i][1] = anchor[i][1];
            p[i][2] = anchor[i][2];
            anchor_c = true;
        }
    }
    if (anchor_c)
    {
        psom.Lattice_anchor_edge_set();
        drawModel.pLattice_renew();
    }
    if (curve)
    {
        glm::ivec3 t_angle = {ptexRotate[0], ptexRotate[1], ptexRotate[2]};
        glm::fvec3 t_trans = {ptexTranslate[0], ptexTranslate[1], ptexTranslate[2]};
        glm::fvec3 t_scale = {ptexScale[0], ptexScale[1], ptexScale[2]};
        tex.texMatrix3D.anglehw = t_angle[0];
        tex.texMatrix3D.angledh = t_angle[1];
        tex.texMatrix3D.angledw = t_angle[2];
        tex.texMatrix3D.translate = t_trans;
        tex.texMatrix3D.scale = t_scale;

        tex.texMatrix3D.resolution_w = {ptexResolution_w[0], ptexResolution_w[1]};
        tex.texMatrix3D.resolution_h = {ptexResolution_h[0], ptexResolution_h[1]};
        tex.texMatrix3D.resolution_d = {ptexResolution_d[0], ptexResolution_d[1]};
        tex.texMatrix3D.wrapType = ptexWrap;

        tex.texMatrix3D.texture_m.Push();
        tex.texMatrix3D.texture_m.Save(glm::scale(tex.texMatrix3D.texture_m.Top(), glm::vec3(1.0 / t_scale.x, 1.0 / t_scale.y, 1.0 / t_scale.z)));
        tex.texMatrix3D.texture_m.Save(glm::translate(tex.texMatrix3D.texture_m.Top(), glm::vec3(-t_trans.x, -t_trans.y, -t_trans.z)));
        tex.texMatrix3D.texture_m.Save(glm::rotate(tex.texMatrix3D.texture_m.Top(), glm::radians((float)t_angle[0]), glm::vec3(0.0, 0.0, 1.0)));
        tex.texMatrix3D.texture_m.Save(glm::rotate(tex.texMatrix3D.texture_m.Top(), glm::radians((float)t_angle[1]), glm::vec3(1.0, 0.0, 0.0)));
        tex.texMatrix3D.texture_m.Save(glm::rotate(tex.texMatrix3D.texture_m.Top(), glm::radians((float)t_angle[2]), glm::vec3(0.0, 1.0, 0.0)));

        drawModel.pVoxel_mapping();

        tex.texMatrix3D.texture_m.Pop();
    }
}

void imgui_funcsom()
{
    int layerNum = rawmodel.voxelModel.somChioceLayerNum;
    int blockNum = rawmodel.voxelModel.blockNum;
    static int *blocker = (int *)calloc(blockNum, sizeof(int));
    const char *blockerNum[5] = {"block0", "block1", "block2", "block3", "block4"};
    for (int b = 1; b < blockNum; b++)
    {
        if (blocker[b] != rawmodel.voxelModel.blockLocate[b])
            blocker[b] = rawmodel.voxelModel.blockLocate[b];
        int left, right;
        left = rawmodel.voxelModel.blockLocate[b - 1];
        right = rawmodel.voxelModel.blockLocate[b + 1];

        ImGui::SliderInt(blockerNum[b], &blocker[b], left, right);
        if (blocker[b] != rawmodel.voxelModel.blockLocate[b])
        {
            rawmodel.voxelModel.blockLocate[b] = blocker[b];
            rawmodel.choice_somvoxel(m_inverse, f_translate, f_scale, false);
            for (int layer = 0; layer < layerNum; layer++)
            {
                for (int block = 0; block < blockNum; block++)
                {
                    int voxelNum = rawmodel.voxelModel.voxelnum[layer][block];
                    glm::ivec3 voxelMaxsize = rawmodel.voxelModel.maxsize[layer][block];
                    glm::ivec3 voxelMinsize = rawmodel.voxelModel.minsize[layer][block];
                    som[layer][block].Lattice_pos_set(rawmodel.Voxel_Position(layer, block), voxelNum, voxelMaxsize, voxelMinsize);
                }
            }
            drawModel.Voxel_Lattice_renew();
        }
    }

    static bool init = true;

    const char *collapsingHeaderName[8][5] = {
        {"Layer 0 block 0", "Layer 0 block 1", "Layer 0 block 2", "Layer 0 block 3", "Layer 0 block 4"},
        {"Layer 1 block 0", "Layer 1 block 1", "Layer 1 block 2", "Layer 1 block 3", "Layer 1 block 4"},
        {"Layer 2 block 0", "Layer 2 block 1", "Layer 2 block 2", "Layer 2 block 3", "Layer 2 block 4"},
        {"Layer 3 block 0", "Layer 3 block 1", "Layer 3 block 2", "Layer 3 block 3", "Layer 3 block 4"},
        {"Layer 4 block 0", "Layer 4 block 1", "Layer 4 block 2", "Layer 4 block 3", "Layer 4 block 4"},
        {"Layer 5 block 0", "Layer 5 block 1", "Layer 5 block 2", "Layer 5 block 3", "Layer 5 block 4"},
        {"Layer 6 block 0", "Layer 6 block 1", "Layer 6 block 2", "Layer 6 block 3", "Layer 6 block 4"},
        {"Layer 7 block 0", "Layer 7 block 1", "Layer 7 block 2", "Layer 7 block 3", "Layer 7 block 4"},
    };
    static bool selection[8][5] = {
        {true, true, true, true, true},
        {true, true, true, true, true},
        {true, true, true, true, true},
        {true, true, true, true, true},
        {true, true, true, true, true},
        {true, true, true, true, true},
        {true, true, true, true, true},
        {true, true, true, true, true}};
    static int **texType = (int **)malloc(layerNum * sizeof(int *));
    static int **texWrap = (int **)malloc(layerNum * sizeof(int *));
    static int ***texUpEdge = (int ***)malloc(layerNum * sizeof(int **));
    static int ***texDownEdge = (int ***)malloc(layerNum * sizeof(int **));
    static int ***texAnchor = (int ***)malloc(layerNum * sizeof(int **));
    static int anchorTime = 500;
    static float ***texResolution_w = (float ***)malloc(layerNum * sizeof(float **));
    static float ***texResolution_h = (float ***)malloc(layerNum * sizeof(float **));
    static float ***texScale = (float ***)malloc(layerNum * sizeof(float **));
    static float ***texTranslate = (float ***)malloc(layerNum * sizeof(float **));
    static int **texRotate = (int **)malloc(layerNum * sizeof(int *));
    static int **lat = (int **)malloc(layerNum * sizeof(int *));
    static int **resolution = (int **)malloc(layerNum * sizeof(int *));
    static int **iter = (int **)malloc(layerNum * sizeof(int *));
    static float **radius = (float **)malloc(layerNum * sizeof(float *));
    static float **rate = (float **)malloc(layerNum * sizeof(float *));
    if (init)
    {
        for (int layer = 0; layer < layerNum; layer++)
        {
            texType[layer] = (int *)calloc(blockNum, sizeof(int));
            texWrap[layer] = (int *)calloc(blockNum, sizeof(int));
            texUpEdge[layer] = (int **)malloc(blockNum * sizeof(int *));
            texDownEdge[layer] = (int **)malloc(blockNum * sizeof(int *));
            texAnchor[layer] = (int **)malloc(blockNum * sizeof(int *));
            texResolution_w[layer] = (float **)malloc(blockNum * sizeof(float *));
            texResolution_h[layer] = (float **)malloc(blockNum * sizeof(float *));
            texTranslate[layer] = (float **)malloc(blockNum * sizeof(float *));
            texScale[layer] = (float **)malloc(blockNum * sizeof(float *));
            texRotate[layer] = (int *)calloc(blockNum, sizeof(int));
            lat[layer] = (int *)calloc(blockNum, sizeof(int));
            resolution[layer] = (int *)calloc(blockNum, sizeof(int));
            iter[layer] = (int *)calloc(blockNum, sizeof(int));
            radius[layer] = (float *)calloc(blockNum, sizeof(float));
            rate[layer] = (float *)calloc(blockNum, sizeof(float));
            for (int block = 0; block < blockNum; block++)
            {
                const LatData_t *latticeData = som[layer][block].Lattice_get();

                lat[layer][block] = 1;
                texTranslate[layer][block] = (float *)calloc(2, sizeof(float));
                texScale[layer][block] = (float *)calloc(2, sizeof(float));
                texScale[layer][block][0] = 1.0;
                texScale[layer][block][1] = 1.0;
                texUpEdge[layer][block] = (int *)calloc(4, sizeof(int));

                // texUpEdge[layer][block][0] = 2;
                // texUpEdge[layer][block][1] = 14;
                // texUpEdge[layer][block][2] = 12;
                // texUpEdge[layer][block][3] = 6;
                texUpEdge[layer][block][1] = latticeData->height - 1;
                texUpEdge[layer][block][2] = latticeData->width - 1;
                texUpEdge[layer][block][3] = latticeData->height - 1;
                texDownEdge[layer][block] = (int *)calloc(4, sizeof(int));
                // texDownEdge[layer][block][0] = 0;
                // texDownEdge[layer][block][1] = 4;
                // texDownEdge[layer][block][2] = 11;
                texDownEdge[layer][block][2] = latticeData->width - 1;
                // texDownEdge[layer][block][3] = 0;
                texAnchor[layer][block] = (int *)calloc(2, sizeof(int));
                texAnchor[layer][block][0] = (latticeData->width) / 2;
                texAnchor[layer][block][1] = (latticeData->height) / 2;

                texResolution_w[layer][block] = (float *)calloc(2, sizeof(float));
                texResolution_h[layer][block] = (float *)calloc(2, sizeof(float));
                texResolution_w[layer][block][0] = 0.0;
                texResolution_w[layer][block][1] = 1.0;
                texResolution_h[layer][block][0] = 0.0;
                texResolution_h[layer][block][1] = 1.0;
            }
        }
        init = false;
    }
    for (int layer = 0; layer < layerNum; layer++)
    {
        for (int block = 0; block < blockNum; block++)
        {

            ImGui::Selectable(collapsingHeaderName[layer][block], &selection[layer][block]);
            const LatData_t *latticeData = som[layer][block].Lattice_get();
            if (ImGui::CollapsingHeader(collapsingHeaderName[layer][block]))
            {
                // textureMap.h    texTypeNum = 3
                // texture pattern
                ImGui::Text("texture pattern");
                ImGui::RadioButton("hive", &texType[layer][block], 0);
                ImGui::SameLine();
                ImGui::RadioButton("pattern", &texType[layer][block], 1);
                ImGui::SameLine();
                ImGui::RadioButton("wb", &texType[layer][block], 2);
                // texture anchor edge point
                ImGui::Text("texture anchor edge point");
                ImGui::InputInt4("down", texDownEdge[layer][block]);
                ImGui::InputInt4("up", texUpEdge[layer][block]);
                // texture anchor point
                ImGui::Text("texture anchor point");
                ImGui::InputInt2("anchor", texAnchor[layer][block]);
                ImGui::InputInt("rand time", &anchorTime);
                // texture wrapping
                ImGui::Text("texture wrap");
                ImGui::RadioButton("repeat", &texWrap[layer][block], 0);
                ImGui::SameLine();
                ImGui::RadioButton("border", &texWrap[layer][block], 1);
                // texture resolution
                ImGui::Text("texture resolution");
                ImGui::InputFloat2("width", texResolution_w[layer][block]);
                ImGui::InputFloat2("height", texResolution_h[layer][block]);
                // texture matrix
                ImGui::Text("texture matrix");
                ImGui::SliderFloat2("translate_tex", texTranslate[layer][block], -1, 1);
                ImGui::InputFloat2("scale_tex", texScale[layer][block]);
                ImGui::SliderInt("rotate(degree)_tex", &texRotate[layer][block], 0, 360);

                ImGui::Text("lattice");
                ImGui::RadioButton("plane", &lat[layer][block], 0);
                ImGui::SameLine();
                ImGui::RadioButton("cylinder", &lat[layer][block], 1);
                ImGui::SameLine();
                ImGui::RadioButton("donut", &lat[layer][block], 2);
                ImGui::SameLine();
                ImGui::RadioButton("ball", &lat[layer][block], 3);

                ImGui::InputInt("input lattice size", &resolution[layer][block]);
                ImGui::Text("iter : %d", latticeData->iter[weightType_gui]);
                ImGui::SameLine();
                ImGui::InputInt("input finalIter", &iter[layer][block]);
                // ImGui::Text("iter(tex) : %d", latticeData->iter[1]);
                ImGui::Text("radius: %f", latticeData->initRadius[weightType_gui]);
                ImGui::SameLine();
                ImGui::InputFloat("input initRadius", &radius[layer][block]);
                ImGui::Text("learning_rate: %f", latticeData->initLearningRate[weightType_gui]);
                ImGui::SameLine();
                ImGui::InputFloat("input initRate", &rate[layer][block]);
            }
            if (resolution[layer][block] == 0)
                resolution[layer][block] = latticeData->width;
            if (iter[layer][block] == 0)
                iter[layer][block] = latticeData->finalIter[weightType_gui];
            if (radius[layer][block] == 0)
                radius[layer][block] = latticeData->initRadius[weightType_gui];
            if (rate[layer][block] == 0)
                rate[layer][block] = latticeData->initLearningRate[weightType_gui];

            if (iter[layer][block] != latticeData->finalIter[weightType_gui])
                som[layer][block].Lattice_iter_set(iter[layer][block]);
            if (radius[layer][block] != latticeData->initRadius[weightType_gui])
                som[layer][block].Lattice_radius_set(radius[layer][block]);
            if (rate[layer][block] != latticeData->initLearningRate[weightType_gui])
                som[layer][block].Lattice_rate_set(rate[layer][block]);
            if (resolution[layer][block] != latticeData->width)
            {
                int *tanc = texAnchor[layer][block];
                tanc[0] = (tanc[0] > resolution[layer][block] - 1) ? resolution[layer][block] - 1 : tanc[0];
                tanc[1] = (tanc[1] > resolution[layer][block] - 1) ? resolution[layer][block] - 1 : tanc[1];
                tanc[2] = 0;
                // cout << tanc[0] <<", "<<tanc[1]<<endl;
                // if(tanc[0] != texAnchor[layer][block][0] || tanc[1] != texAnchor[layer][block][1])
                som[layer][block].Lattice_anchor_set(tanc, anchorTime);
                texUpEdge[layer][block][1] = resolution[layer][block] - 1;
                texUpEdge[layer][block][2] = resolution[layer][block] - 1;
                texUpEdge[layer][block][3] = resolution[layer][block] - 1;
                texDownEdge[layer][block][2] = resolution[layer][block] - 1;
                glm::ivec3 voxelMaxsize = rawmodel.voxelModel.maxsize[layer][block];
                glm::ivec3 voxelMinsize = rawmodel.voxelModel.minsize[layer][block];
                som[layer][block].Lattice_resolution_set(resolution[layer][block], voxelMaxsize, voxelMinsize);
                drawModel.Lattice_renew(layer, block);
            }
            if (lat[layer][block] != latticeData->type)
            {
                glm::ivec3 voxelMaxsize = rawmodel.voxelModel.maxsize[layer][block];
                glm::ivec3 voxelMinsize = rawmodel.voxelModel.minsize[layer][block];
                som[layer][block].Lattice_type_set(lat[layer][block], voxelMaxsize, voxelMinsize);
                drawModel.Lattice_renew(layer, block);
                int a = 0;
            }
            // update anchor edge point
            glm::ivec3 *p = latticeData->anchorEdgeP;
            int *gui_dp = texDownEdge[layer][block];
            int *gui_up = texUpEdge[layer][block];
            if (gui_dp[0] != p[0].x || gui_dp[1] != p[0].y || gui_dp[2] != p[1].x || gui_dp[3] != p[1].y ||
                gui_up[0] != p[3].x || gui_up[1] != p[3].y || gui_up[2] != p[2].x || gui_up[3] != p[2].y)
            {
                p[0] = p[4] = {gui_dp[0], gui_dp[1], 0.0};
                p[1] = p[5] = {gui_dp[2], gui_dp[3], 0.0};
                p[2] = p[6] = {gui_up[2], gui_up[3], 0.0};
                p[3] = p[7] = {gui_up[0], gui_up[1], 0.0};
                som[layer][block].Lattice_anchor_edge_set();
                drawModel.Lattice_renew(layer, block);
            }
            // update anchor point
            glm::ivec3 lanc = latticeData->anchorP;
            int *tanc = texAnchor[layer][block];
            if (lanc[0] != tanc[0] || lanc[1] != tanc[1] || lanc[2] != tanc[2] || latticeData->anchorTime != anchorTime)
            {
                tanc[0] = (tanc[0] > resolution[layer][block]) ? resolution[layer][block] : tanc[0];
                tanc[1] = (tanc[1] > resolution[layer][block]) ? resolution[layer][block] : tanc[1];
                tanc[2] = 0;(tanc[2] > resolution[layer][block]) ? resolution[layer][block] : tanc[2];
                som[layer][block].Lattice_anchor_set(tanc, anchorTime);
                drawModel.Lattice_renew(layer, block);
            }
            int t_angle = texRotate[layer][block];
            int d_angle = tex.texMatrix2D.anglehw;
            int d_wrap = tex.texMatrix2D.wrapType;
            int t_wrap = texWrap[layer][block];
            glm::fvec2 t_trans = {texTranslate[layer][block][0], texTranslate[layer][block][1]};
            glm::fvec2 d_trans = {tex.texMatrix2D.translate.x, tex.texMatrix2D.translate.y};
            glm::fvec2 t_scale = {texScale[layer][block][0], texScale[layer][block][1]};
            glm::fvec2 d_scale = {tex.texMatrix2D.scale.x, tex.texMatrix2D.scale.y};
            glm::fvec2 d_resolution_w = tex.texMatrix2D.resolution_w;
            glm::fvec2 t_resolution_w = {texResolution_w[layer][block][0], texResolution_w[layer][block][1]};
            glm::fvec2 d_resolution_h = tex.texMatrix2D.resolution_h;
            glm::fvec2 t_resolution_h = {texResolution_h[layer][block][0], texResolution_h[layer][block][1]};
            // if (curve)
            // {
            if (d_angle != t_angle || d_trans != t_trans || d_scale != t_scale)
            {

                tex.texMatrix2D.anglehw = t_angle;
                tex.texMatrix2D.translate.x = t_trans.x;
                tex.texMatrix2D.translate.y = t_trans.y;
                tex.texMatrix2D.scale.x = t_scale.x;
                tex.texMatrix2D.scale.y = t_scale.y;

                float sx = (t_scale.x == 0) ? 0.0 : 1.0 / t_scale.x;
                float sy = (t_scale.y == 0) ? 0.0 : 1.0 / t_scale.y;

                tex.texMatrix2D.texture_m.Pop();
                tex.texMatrix2D.texture_m.Push();
                tex.texMatrix2D.texture_m.Save(glm::scale(tex.texMatrix2D.texture_m.Top(), glm::vec3(sx, sy, 1.0)));
                tex.texMatrix2D.texture_m.Save(glm::translate(tex.texMatrix2D.texture_m.Top(), glm::vec3(-t_trans.x, -t_trans.y, 0.0f)));
                tex.texMatrix2D.texture_m.Save(glm::rotate(tex.texMatrix2D.texture_m.Top(), glm::radians((float)t_angle), glm::vec3(0.0, 0.0, 1.0)));

                drawModel.Lattice_renew(layer, block);
            }
            if (curve)
                drawModel.Voxel_mapping(layer, block);
            if (d_resolution_w != t_resolution_w || d_resolution_h != t_resolution_h || d_wrap != t_wrap)
            {
                if (t_resolution_w.t < t_resolution_w.s)
                    t_resolution_w.t = t_resolution_w.s + 0.01;
                if (t_resolution_h.t < t_resolution_h.s)
                    t_resolution_h.t = t_resolution_h.s + 0.01;
                tex.texMatrix2D.resolution_w = t_resolution_w;
                tex.texMatrix2D.resolution_h = t_resolution_h;
                tex.texMatrix2D.wrapType = t_wrap;
                drawModel.Lattice_renew(layer, block);
            }
            if (rawmodel.voxelModel.somVoxel[layer][block]->textype != texType[layer][block])
            {
                rawmodel.voxelModel.somVoxel[layer][block]->textype = texType[layer][block];
                glm::ivec3 texWHD = {tex.imageTex[texType[layer][block]].width, tex.imageTex[texType[layer][block]].height, 1};
                som[layer][block].Lattice_tex_set(texWHD);
            }
            drawModel.showEachPart[layer][block] = selection[layer][block];
        }
    }
}
void imgui_end()
{

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
