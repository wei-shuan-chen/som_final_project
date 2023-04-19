#ifndef GUI_H
#define GUI_H
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include<iostream>

#include "Drawmodel.h"
#include "SOM.h"

using namespace std;

void imgui_init(GLFWwindow *window);
void imgui_create();
void imgui_end();
int shape_init();

#endif