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
	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "SOM_3D", NULL, NULL);
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
	Shader_Create();
    tex.createTexture();
	tex.createdepthTexture();
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{

		// move(keyboard&mouth)
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		// input
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		imgui_create();
		Shader_Use();

		imgui_end();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	Model_del();
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
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(UP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(DOWN, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		camera.ProcessKeyboard(PITCHUP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
		camera.ProcessKeyboard(PITCHDOWN, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
		camera.ProcessKeyboard(YAWUP, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
		camera.ProcessKeyboard(YAWDOWN, deltaTime);

	// light
	float v = rate*deltaTime;
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
		lightPos = lightPos+glm::vec3(0.0,v,0.0);
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
		lightPos = lightPos+glm::vec3(0.0,-1*v,0.0);
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
		lightPos = lightPos+glm::vec3(-1*v,0.0,0.0);
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
		lightPos = lightPos+glm::vec3(v,0.0,0.0);
	// if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
	// 	lightPos = lightPos+glm::vec3(0.0,0.0,v);
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
		lightPos = lightPos+glm::vec3(0.0,0.0,-1*v);


}
void keyPressFun(GLFWwindow* window, int key, int scancode, int action, int mods){

	// show
	if(key == GLFW_KEY_Z && action == GLFW_PRESS)
		showVoxel = !showVoxel;
	if(key == GLFW_KEY_X && action == GLFW_PRESS)
		showLatticePlane = !showLatticePlane;
	if(key == GLFW_KEY_C && action == GLFW_PRESS)
		showLatticeLine = !showLatticeLine;
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