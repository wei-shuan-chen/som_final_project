#include "textureMap.h"

glm::ivec3** image;
unsigned int texture;
unsigned int depthCubemap;
unsigned int depthFBO;
int image_width, image_height;
const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

void createTexture(){
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int nrChannels;
    // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
    unsigned char *data = stbi_load("texture/color.png", &image_width, &image_height, &nrChannels, 0);

    if (data)
    {
        if(nrChannels == 3){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width, image_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }else if(nrChannels == 4){
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }else{
            cout << "ncrChannel error!" << endl;
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    // create image array
    image = (glm::ivec3**)calloc(image_height, sizeof(glm::ivec3*));
    for(int i = 0; i < image_height; i++){
        image[i] = (glm::ivec3*)calloc(image_width, sizeof(glm::ivec3));
        for(int j = 0; j < image_width; j++){
            for(int k = 0; k < 3; k++){
                if(nrChannels == 3) image[i][j][k] = data[i*image_width*3 + j*3 + k];
                if(nrChannels == 4) image[i][j][k] = data[i*image_width*4 + j*4 + k];
            }
        }
    }

    cout << "Image " << image_height << " x " << image_width <<endl;

    stbi_image_free(data);
}
void createdepthTexture(){
    glGenFramebuffers(1, &depthFBO);

    glGenTextures(1, &depthCubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
    for (unsigned int i = 0; i < 6; ++i)
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}
void bindTexture(int act, int bind){

    glActiveTexture(GL_TEXTURE0+act);

    if(bind == 0){
        glBindTexture(GL_TEXTURE_2D, texture);
    }else if(bind == 1){
        glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);
    }
}