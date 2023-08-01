#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>

#include "Gui.h"
#include "camera.h"
#include "Drawmodel.h"
#include "textureMap.h"

#include <stb_image.h>
#include <math.h>
#include <iostream>
#include <array>
#include <thread>
#include <fileSystem>

#define TSIZE 64

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);
void keyPressFun(GLFWwindow* window, int key, int scancode, int action, int mods);
// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;


int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	GLFWwindow *window = glfwCreateWindow(drawModel.SCR_WIDTH, drawModel.SCR_HEIGHT, "SOM_3D", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, keyPressFun);
	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// build and compile our shader program
	// ------------------------------------
	imgui_init(window);
	drawModel.Shader_Create();
    tex.create_texture();
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{

		// move(keyboard&mouth)
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		// input
		processInput(window);
		glClearColor(0.55f, 0.6f, 0.7f, 1.0f);
		// glClearColor(0.15f, 0.1f, 0.59f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		imgui_create();

		drawModel.Shader_Use(window);

		imgui_end();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	destroy_world();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	// camera
	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		drawModel.camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		drawModel.camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		drawModel.camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		drawModel.camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		drawModel.camera.ProcessKeyboard(UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		drawModel.camera.ProcessKeyboard(DOWN, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		drawModel.camera.ProcessKeyboard(PITCHUP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		drawModel.camera.ProcessKeyboard(PITCHDOWN, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		drawModel.camera.ProcessKeyboard(YAWUP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		drawModel.camera.ProcessKeyboard(YAWDOWN, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		drawModel.camera.ProcessMouseScroll(1);
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		drawModel.camera.ProcessMouseScroll(-1);

	// drawModel.lightPos = drawModel.camera.Position;
	// light
	float v = drawModel.rate*deltaTime;
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		drawModel.lightPos = drawModel.lightPos+glm::vec3(0.0,v,0.0);
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		drawModel.lightPos = drawModel.lightPos+glm::vec3(0.0,-1*v,0.0);
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		drawModel.lightPos = drawModel.lightPos+glm::vec3(-1*v,0.0,0.0);
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		drawModel.lightPos = drawModel.lightPos+glm::vec3(v,0.0,0.0);
	// if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
	// 	lightPos = lightPos+glm::vec3(0.0,0.0,v);
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
		drawModel.lightPos = drawModel.lightPos+glm::vec3(0.0,0.0,-1*v);


}
void keyPressFun(GLFWwindow* window, int key, int scancode, int action, int mods){

	// show
	if(key == GLFW_KEY_0 && action == GLFW_PRESS)
		drawModel.showOutSomIn[0] = !drawModel.showOutSomIn[0];
	if(key == GLFW_KEY_1 && action == GLFW_PRESS)
		drawModel.showOutSomIn[1] = !drawModel.showOutSomIn[1];
	if(key == GLFW_KEY_2 && action == GLFW_PRESS)
		drawModel.showOutSomIn[2] = !drawModel.showOutSomIn[2];
	if(key == GLFW_KEY_Z && action == GLFW_PRESS)
		drawModel.showVoxel = !drawModel.showVoxel;
	if(key == GLFW_KEY_X && action == GLFW_PRESS)
		drawModel.showLatticePlane = !drawModel.showLatticePlane;
	if(key == GLFW_KEY_C && action == GLFW_PRESS)
		drawModel.showLatticeLine = !drawModel.showLatticeLine;
	if(key == GLFW_KEY_G && action == GLFW_PRESS){
		startSOM = true;
		createThread();
	}

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}