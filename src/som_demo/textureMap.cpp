#include "textureMap.h"

texture_cls tex;

texture_cls::texture_cls(){
    texMap.texture_m.Save(glm::translate(texMap.texture_m.Top(), glm::vec3(0.5f, 0.5f, 0.0f)));
    texMap.texture_m.Push();
}
texture_cls::~texture_cls(){
    free(intensityTex.data);
    free(colormapTex.data);
    free(threeDTex.data);
    // for(int i = 0; i < 3; i++){
    //     free(imageTex[i].data);
    // }
}
glm::fvec3 texture_cls::compute_voxel_texture(glm::fvec4 texCoord){
    texMap.texture_m.Push();
    texMap.texture_m.Save(glm::translate(texMap.texture_m.Top(), glm::vec3(-0.5f, -0.5f, 0.0f)));

    // compute new texture coord
    glm::fvec3 newTexCoord = {0.0, 0.0, 0.0};
    float down = 0.0;
    for(int t = 0; t < 4; t++){
        down += texMap.texture_m.Top()[t][3]*texCoord[t];
    }
    for(int texNum = 0; texNum < 3; texNum++){
        float tmp = 0.0;
        for(int t = 0; t < 4; t++){
            tmp += texMap.texture_m.Top()[t][texNum]*texCoord[t];
        }
        newTexCoord[texNum] = tmp/down;
    }
    texMap.texture_m.Pop();


    float wb, we, hb, he, gap_w, gap_h;
    wb = texMap.resolution_w.x;
    we = texMap.resolution_w.y;
    hb = texMap.resolution_h.x;
    he = texMap.resolution_h.y;
    gap_w = we - wb;
    gap_h = he- hb;
    if((newTexCoord.s <= we && newTexCoord.s >= wb) && (newTexCoord.t <= he && newTexCoord.t >= hb)){
        if(newTexCoord.s == we) newTexCoord.s -= 0.0001;
        if(newTexCoord.t == he) newTexCoord.t -= 0.0001;
        return newTexCoord;
    }
    // resolution && repeat
    if(texMap.wrapType == REPEAT){
        float tmpCoord;
        if(newTexCoord.s > we){
            tmpCoord = newTexCoord.s - wb;
            while(tmpCoord > we){
                tmpCoord -= gap_w;
            }
            newTexCoord.s = tmpCoord;
        }
        if(newTexCoord.s < wb){
            tmpCoord = newTexCoord.s;
            while(tmpCoord < wb){
                tmpCoord += gap_w;
            }
            newTexCoord.s = tmpCoord;
        }
        if(newTexCoord.t > he){
            tmpCoord = newTexCoord.t - hb;
            while(tmpCoord > he){
                tmpCoord -= gap_h;
            }
            newTexCoord.t = tmpCoord;
        }
        if(newTexCoord.t < hb){
            tmpCoord = newTexCoord.t;
            while(tmpCoord < hb){
                tmpCoord += gap_h;
            }
            newTexCoord.t = tmpCoord;
        }

    }
    // resolution && border
    if(texMap.wrapType == BORDER){
        if(newTexCoord.s > we)
            newTexCoord.s = 1.1;
        if(newTexCoord.s < wb)
            newTexCoord.s = -0.1;
        if(newTexCoord.t > he)
            newTexCoord.t = 1.1;
        if(newTexCoord.t < hb)
            newTexCoord.t = -0.1;
    }

    // cout <<"\n\n\n";
    return newTexCoord;
}
void texture_cls::create_texture(){
    create_img_tex();
    create_depth_tex();
    create_ray_tex();
    create_3D_tex();
}
void texture_cls::bindTexture(int bind){

    glActiveTexture(GL_TEXTURE0+bind);

    if(bind == 0){
        glBindTexture(GL_TEXTURE_3D, imageTex[0].texture);
    }else if(bind == 1){
        glBindTexture(GL_TEXTURE_3D, imageTex[1].texture);
    }else if(bind == 2){
        glBindTexture(GL_TEXTURE_3D, imageTex[2].texture);
    }else if(bind == 3){
        glBindTexture(GL_TEXTURE_CUBE_MAP, shadowTex.depthCubemap);
    }else if(bind == 4){
        glBindTexture(GL_TEXTURE_3D, intensityTex.texture3D);
    }else if(bind == 5){
        glBindTexture(GL_TEXTURE_1D, colormapTex.texture1D);
    }else if(bind == 6){
        glBindTexture(GL_TEXTURE_3D, threeDTex.texture);
    }
}
void texture_cls::updataColorMap(vector<float> newdata){
    for(int c = 0; c < colormapTex.color+1; c++){
        for(int j = 0; j < 4; j++){
            colormapTex.data[c*4+j] = newdata[c*4+j];
        }
    }
    glBindTexture(GL_TEXTURE_1D, colormapTex.texture1D);
    glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, colormapTex.color+1, 0, GL_RGBA, GL_FLOAT, colormapTex.data);
}
void texture_cls::updateIntensityMap(){
    for(int z = 0; z < intensityTex.z; z++){
        for(int y = 0; y < intensityTex.y; y++){
            for(int x = 0; x < intensityTex.x; x++){
                int num = x*4 + y*intensityTex.x*4 + z*intensityTex.x*intensityTex.y*4;
                intensityTex.data[num+3] = rawmodel.rawData[y][x][z].layer/255.0;
            }
        }
    }
    glBindTexture(GL_TEXTURE_3D, intensityTex.texture3D);
    glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, intensityTex.x, intensityTex.y, intensityTex.z, 0, GL_RGBA, GL_FLOAT, intensityTex.data);
}
void texture_cls::create_ray_tex(){
    // init
    intensityTex.x = rawmodel.infdata.resolution[1];
    intensityTex.y = rawmodel.infdata.resolution[2];
    intensityTex.z = rawmodel.infdata.resolution[0];
    intensityTex.data = (float*)calloc(intensityTex.x*intensityTex.y*intensityTex.z*4, sizeof(float));
    for(int z = 0; z < intensityTex.z; z++){
        for(int y = 0; y < intensityTex.y; y++){
            for(int x = 0; x < intensityTex.x; x++){
                int num = x*4 + y*intensityTex.x*4 + z*intensityTex.x*intensityTex.y*4;
                float gx,gy,gz;
                if(x == 0)
                    gx = rawmodel.rawData[y][x+1][z].layer-rawmodel.rawData[y][x][z].layer;
                else if(x == intensityTex.x-1) gx = rawmodel.rawData[y][x][z].layer - rawmodel.rawData[y][x-1][z].layer;
                else {
                    gx = (rawmodel.rawData[y][x+1][z].layer-rawmodel.rawData[y][x-1][z].layer)/2.0;
                    if(rawmodel.rawData[y][x+1][z].layer == 0 || rawmodel.rawData[y][x-1][z].layer == 0) gx *=-1;
                }
                if(y == 0) gy = rawmodel.rawData[y+1][x][z].layer - rawmodel.rawData[y][x][z].layer;
                else if(y == intensityTex.y-1) gy = rawmodel.rawData[y][x][z].layer - rawmodel.rawData[y-1][x][z].layer;
                else {
                    gy = (rawmodel.rawData[y+1][x][z].layer - rawmodel.rawData[y-1][x][z].layer)/2.0;
                    if(rawmodel.rawData[y+1][x][z].layer == 0 || rawmodel.rawData[y-1][x][z].layer == 0) gy*=-1;
                }

                if(z == 0) gz = rawmodel.rawData[y][x][z+1].layer - rawmodel.rawData[y][x][z].layer;
                else if(z == intensityTex.z-1) gz = rawmodel.rawData[y][x][z].layer - rawmodel.rawData[y][x][z-1].layer;
                else {
                    gz = (rawmodel.rawData[y][x][z+1].layer - rawmodel.rawData[y][x][z-1].layer)/2.0;
                    if(rawmodel.rawData[y][x][z+1].layer == 0 || rawmodel.rawData[y][x][z-1].layer == 0) gz *=-1;
                }

                float dist = sqrt(gx*gx+gy*gy+gz*gz);
                intensityTex.data[num+0] = gx/dist;
                intensityTex.data[num+1] = gy/dist;
                intensityTex.data[num+2] = gz/dist;
                intensityTex.data[num+3] = rawmodel.rawData[y][x][z].layer/255.0;
            }
        }
    }
    colormapTex.data = (float*)calloc((colormapTex.color+1)*4, sizeof(float));
    colormapTex.data[0] = -1;

    // set
    glGenTextures(1, &intensityTex.texture3D);
    glBindTexture(GL_TEXTURE_3D, intensityTex.texture3D);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
    glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, intensityTex.x, intensityTex.y, intensityTex.z, 0, GL_RGBA, GL_FLOAT, intensityTex.data);

    glGenTextures(1, &colormapTex.texture1D);
    glBindTexture(GL_TEXTURE_1D, colormapTex.texture1D);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, colormapTex.color+1, 0, GL_RGBA, GL_FLOAT, colormapTex.data);
}
void texture_cls::create_3D_tex(){

    threeDTex.data = (float*)calloc(3*threeDTex.width*threeDTex.height*threeDTex.depth, sizeof(float));
    for(int z = 0; z < threeDTex.depth; z++){
        for(int y = 0; y < threeDTex.height; y++){
            for(int x = 0; x < threeDTex.width; x++){
                int num = x*3 + y*threeDTex.width*3 + z*threeDTex.width*threeDTex.height*3;
                if(y < 3 ||y > 6||x < 3 || x > 6){
                    threeDTex.data[num] = 1.0;
                    threeDTex.data[num+1] = 0.0;
                    threeDTex.data[num+2] = 0.0;
                }else{
                    threeDTex.data[num] = 1.0;
                    threeDTex.data[num+1] = 0.0;
                    threeDTex.data[num+2] = 1.0;
                }
            }
        }
    }

    glGenTextures(1, &threeDTex.texture);
    glBindTexture(GL_TEXTURE_3D, threeDTex.texture);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
    glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB, threeDTex.width, threeDTex.height, threeDTex.depth, 0, GL_RGB, GL_FLOAT, threeDTex.data);
}
void texture_cls::create_img_tex(){
    for(int t = 0; t< 3; t++){
        glGenTextures(1, &imageTex[t].texture);
        glBindTexture(GL_TEXTURE_3D, imageTex[t].texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        int nrChannels;
        // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
        imageTex[t].data = stbi_load(texName[t], &imageTex[t].width, &imageTex[t].height, &nrChannels, 0);

        if (imageTex[t].data)
        {
            if(nrChannels == 3){
                glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB, imageTex[t].width, imageTex[t].height, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, imageTex[t].data);
            }else if(nrChannels == 4){
                glTexImage3D(GL_TEXTURE_3D, 0, GL_RGBA, imageTex[t].width, imageTex[t].height, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageTex[t].data);
            }else{
                cout << "ncrChannel error!" << endl;
            }
            // glGenerateMipmap(GL_TEXTURE_3D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }

        texture1Dto2D(nrChannels, t);

        stbi_image_free(imageTex[t].data);
    }
}
void texture_cls::create_depth_tex(){
    glGenFramebuffers(1, &shadowTex.depthFBO);

    glGenTextures(1, &shadowTex.depthCubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, shadowTex.depthCubemap);
    for (unsigned int i = 0; i < 6; ++i)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, shadowTex.width, shadowTex.height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindFramebuffer(GL_FRAMEBUFFER, shadowTex.depthFBO);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowTex.depthCubemap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}


void texture_cls::texture1Dto2D(int nrChannels, int t){
    // create image array
    imageTex[t].image = (glm::ivec3**)calloc(imageTex[t].height, sizeof(glm::ivec3*));
    for(int i = 0; i < imageTex[t].height; i++){
        imageTex[t].image[i] = (glm::ivec3*)calloc(imageTex[t].width, sizeof(glm::ivec3));
        for(int j = 0; j < imageTex[t].width; j++){
            for(int k = 0; k < 3; k++){
                if(nrChannels == 3) imageTex[t].image[i][j][k] = imageTex[t].data[i*imageTex[t].width*3 + j*3 + k];
                if(nrChannels == 4) imageTex[t].image[i][j][k] = imageTex[t].data[i*imageTex[t].width*4 + j*4 + k];
            }
        }
    }

    cout << "Image(w x h) "<<t << " : " << imageTex[t].width << " x " << imageTex[t].height <<endl;
}