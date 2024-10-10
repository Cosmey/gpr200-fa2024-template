#include <stdio.h>
#include <math.h>
#include <iostream>
#include <list>

#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <ew/external/stb_image.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Reece/Shader.h"
#include "Reece/TextureLoader.h"
#include "Reece/Camera.h"
#include "Reece/Cube.h"
#include "Reece/ThreeDObject.h"
using namespace Reece;

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

void GetMousePos(GLFWwindow* window, double xpos, double ypos);
void GetScrollDelta(GLFWwindow* window, double xoffset, double yoffset);
void CheckInputs(GLFWwindow *window,Camera *myCamera,float deltaTime);
glm::vec2 mousePos;
glm::vec2 scrollDelta;

int main() {
	printf("Initializing...");
	if (!glfwInit()) {
		printf("GLFW failed to init!");
		return 1;
	}
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello Triangle", NULL, NULL);
	if (window == NULL) {
		printf("GLFW failed to create window");
		return 1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGL(glfwGetProcAddress)) {
		printf("GLAD Failed to load GL headers");
		return 1;
	}
	//Initialization goes here!
	Shader cubeShader("assets/Shaders/Cube.vs", "assets/Shaders/Cube.fs");

	//camera setup
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec2 aspectRatio = glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT);
	Camera myCamera(cameraPos,0.0f,0.0f,60.0f,aspectRatio);

	//Setup Cubes
	pmr::list<ThreeDObject*> objects;
	for(int i = 0;i < 20;i++)
	{
		glm::vec3 position = glm::vec3(ew::RandomRange(-10,10), ew::RandomRange(-10,10), ew::RandomRange(-10,10));
		glm::vec3 rotation = glm::vec3(ew::RandomRange(-1.0f,1.0f), ew::RandomRange(-1.0f,1.0f), ew::RandomRange(-1.0f,1.0f));
		glm::vec3 scale = glm::vec3(ew::RandomRange(0.2f,3.0f), ew::RandomRange(0.2f,3.0f), ew::RandomRange(0.2f,3.0f));
		objects.push_back(new Cube(cubeShader,position,rotation,scale));
		//objects.back.SetTexture("assets/Textures/stoneWall.png");
	}

	//enable depth
	glEnable(GL_DEPTH_TEST);

	//enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//make cursor not visible
	glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);

	//setting up time keeping
	float deltaTime = 0.0f;
	float previousTime = 0.0f;

	//set callbacks for camera movement
	glfwSetCursorPosCallback(window, GetMousePos);
	glfwSetScrollCallback(window, GetScrollDelta);

	//Render loop
	while (!glfwWindowShouldClose(window)) {
		//setting up for input
		glfwPollEvents();

		//Clear framebuffer
		glClearColor(0.3f, 0.4f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//set time
		float timeValue = glfwGetTime();
		deltaTime = timeValue - previousTime;
		cubeShader.setFloat("uTime", timeValue);

		//setup shader for drawing
		unsigned int VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		cubeShader.use();

		//update camera look and zoom
		myCamera.UpdateMousePosition(mousePos);
		myCamera.UpdateScroll(scrollDelta);

		//reset scroll delta
		scrollDelta = glm::vec2(0.0f);

		//check inputs
		CheckInputs(window,&myCamera,deltaTime);

		//setting view and projection
		glm::mat4 view = myCamera.View();
		glm::mat4 projection = myCamera.Projection();
		cubeShader.setMat4("view", view);
		cubeShader.setMat4("projection", projection);

		//draw all cubes
		for(auto currentObject : objects)
		{
			currentObject->Draw();
		}


		glfwSwapBuffers(window);

		previousTime = timeValue;
	}
	printf("Shutting down...");
}
void GetMousePos(GLFWwindow *window, double xpos, double ypos)
{
	mousePos = glm::vec2(xpos,ypos);
}
void GetScrollDelta(GLFWwindow* window, double xoffset, double yoffset)
{
	scrollDelta = glm::vec2(xoffset,yoffset);
}
void CheckInputs(GLFWwindow *window,Camera *myCamera,float deltaTime)
{
	float cameraSpeed = 5.0f; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		cameraSpeed *= 2;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		myCamera->position += cameraSpeed * myCamera->Front() * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		myCamera->position -= cameraSpeed * myCamera->Front() * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		myCamera->position -= glm::normalize(glm::cross(myCamera->Front(), myCamera->Up())) * cameraSpeed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		myCamera->position += glm::normalize(glm::cross(myCamera->Front(), myCamera->Up())) * cameraSpeed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		myCamera->position -= cameraSpeed * glm::normalize(glm::cross(myCamera->Front(), glm::normalize(glm::cross(myCamera->Front(), myCamera->Up())))) * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		myCamera->position += cameraSpeed * glm::normalize(glm::cross(myCamera->Front(), glm::normalize(glm::cross(myCamera->Front(), myCamera->Up())))) * deltaTime;
}

