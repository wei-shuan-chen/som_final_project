#ifndef DRAWMODEL_H
#define DRAWMODEL_H
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <thread>

#include "SOM.h"
#include "RAWmodel.h"
#include "matrixStack.h"
#include "shader.h"
#include "textureMap.h"
#include "Item.h"
#include "world.h"
#include "logger.h"
#include "camera.h"

void Shader_Create();
void Shader_Use();
void Model_del();
void Model_mapping();
void createThread();

extern Camera camera;
extern glm::vec3 lightPos;
extern const unsigned int SCR_WIDTH, SCR_HEIGHT;
extern float rate;
extern bool showVoxel;
extern bool showLatticePlane;
extern bool showLatticeLine;
extern bool startSOM;

#endif