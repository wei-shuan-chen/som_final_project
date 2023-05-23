#include "textureMap.h"

texture_cls tex;

texture_cls::texture_cls(){}
texture_cls::~texture_cls(){}

void texture_cls::createTexture(){
    glGenTextures(1, &imageTex.texture);
    glBindTexture(GL_TEXTURE_2D, imageTex.texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    imageTex.data = stbi_load("texture/b.png", &imageTex.width, &imageTex.height, &nrChannels, 0);

    if (imageTex.data)
    {
        if(nrChannels == 3){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageTex.width, imageTex.height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageTex.data);
        }else if(nrChannels == 4){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageTex.width, imageTex.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageTex.data);
        }else{
            cout << "ncrChannel error!" << endl;
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    texture1Dto2D(nrChannels);

    stbi_image_free(imageTex.data);
}
void texture_cls::createdepthTexture(){
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
void texture_cls::bindTexture(int act, int bind){

    glActiveTexture(GL_TEXTURE0+act);

    if(bind == 0){
        glBindTexture(GL_TEXTURE_2D, imageTex.texture);
    }else if(bind == 1){
        glBindTexture(GL_TEXTURE_CUBE_MAP, shadowTex.depthCubemap);
    }
}

void texture_cls::texture1Dto2D(int nrChannels){
       // create image array
    imageTex.image = (glm::ivec3**)calloc(imageTex.height, sizeof(glm::ivec3*));
    for(int i = 0; i < imageTex.height; i++){
        imageTex.image[i] = (glm::ivec3*)calloc(imageTex.width, sizeof(glm::ivec3));
        for(int j = 0; j < imageTex.width; j++){
            for(int k = 0; k < 3; k++){
                if(nrChannels == 3) imageTex.image[i][j][k] = imageTex.data[i*imageTex.width*3 + j*3 + k];
                if(nrChannels == 4) imageTex.image[i][j][k] = imageTex.data[i*imageTex.width*4 + j*4 + k];
            }
        }
    }

    cout << "Image(w x h) " << imageTex.width << " x " << imageTex.height <<endl;

}