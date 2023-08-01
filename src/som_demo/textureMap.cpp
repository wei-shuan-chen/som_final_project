#include "textureMap.h"

texture_cls tex;

texture_cls::texture_cls(){}
texture_cls::~texture_cls(){
    free(intensityTex.data);
    free(colormapTex.data);
    // for(int i = 0; i < 3; i++){
    //     free(imageTex[i].data);
    // }
}
glm::fvec2 texture_cls::compute_voxel_texture(MatrixStack tex, glm::fvec4 texCoord){
    tex.Save(glm::translate(tex.Top(), glm::vec3(-0.5f, -0.5f, 0.0f)));
    glm::fvec2 newTexCoord = {0.0, 0.0};
    float down = 0.0;
    for(int t = 0; t < 4; t++){
        down += tex.Top()[t][3]*texCoord[t];
    }
    for(int texNum = 0; texNum < 2; texNum++){
        float tmp = 0.0;
        for(int t = 0; t < 4; t++){
            tmp += tex.Top()[t][texNum]*texCoord[t];
        }
        newTexCoord[texNum] = tmp/down;
    }

    return newTexCoord;
}
void texture_cls::create_texture(){
    create_img_tex();
    create_depth_tex();
    create_ray_tex();
}
void texture_cls::bindTexture(int bind){

    glActiveTexture(GL_TEXTURE0+bind);

    if(bind == 0){
        glBindTexture(GL_TEXTURE_2D, imageTex[0].texture);
    }else if(bind == 1){
        glBindTexture(GL_TEXTURE_2D, imageTex[1].texture);
    }else if(bind == 2){
        glBindTexture(GL_TEXTURE_2D, imageTex[2].texture);
    }else if(bind == 3){
        glBindTexture(GL_TEXTURE_CUBE_MAP, shadowTex.depthCubemap);
    }else if(bind == 4){
        glBindTexture(GL_TEXTURE_3D, intensityTex.texture3D);
    }else if(bind == 5){
        glBindTexture(GL_TEXTURE_1D, colormapTex.texture1D);
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
void texture_cls::create_ray_tex(){
    // init
    intensityTex.x = rawmodel.infdata.resolution[1];
    intensityTex.y = rawmodel.infdata.resolution[2];
    intensityTex.z = rawmodel.infdata.resolution[0];
    intensityTex.data = (float*)calloc(intensityTex.x*intensityTex.y*intensityTex.z, sizeof(float));
    for(int z = 0; z < intensityTex.z; z++){
        for(int y = 0; y < intensityTex.y; y++){
            for(int x = 0; x < intensityTex.x; x++){
                int num = x + y*intensityTex.x + z*intensityTex.x*intensityTex.y;
                intensityTex.data[num] = rawmodel.rawData[y][x][z].layer/255.0;
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
    glTexImage3D(GL_TEXTURE_3D, 0, GL_RED, intensityTex.x, intensityTex.y, intensityTex.z, 0, GL_RED, GL_FLOAT, intensityTex.data);

    glGenTextures(1, &colormapTex.texture1D);
    glBindTexture(GL_TEXTURE_1D, colormapTex.texture1D);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, colormapTex.color+1, 0, GL_RGBA, GL_FLOAT, colormapTex.data);
}
void texture_cls::create_img_tex(){
    for(int t = 0; t< 3; t++){
        glGenTextures(1, &imageTex[t].texture);
        glBindTexture(GL_TEXTURE_2D, imageTex[t].texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        int nrChannels;
        // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
        imageTex[t].data = stbi_load(texName[t], &imageTex[t].width, &imageTex[t].height, &nrChannels, 0);

        if (imageTex[t].data)
        {
            if(nrChannels == 3){
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageTex[t].width, imageTex[t].height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageTex[t].data);
            }else if(nrChannels == 4){
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageTex[t].width, imageTex[t].height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageTex[t].data);
            }else{
                cout << "ncrChannel error!" << endl;
            }
            glGenerateMipmap(GL_TEXTURE_2D);
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