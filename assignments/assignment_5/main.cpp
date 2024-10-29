#include <stdio.h>
#include <math.h>
#include <iostream>

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
	Shader spriteShader("assets/Shaders/Cube.vs", "assets/Shaders/Cube.fs");

	//camera setup
	glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec2 aspectRatio = glm::vec2(SCREEN_WIDTH, SCREEN_HEIGHT);
	Camera myCamera(cameraPos,0.0f,0.0f,60.0f,aspectRatio);






	float vertices[] = {
		// positions          // colors           // texture coords
		1.0f,  1.0f,-1.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		1.0f, -1.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
	   -1.0f, -1.0f,-1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
	   -1.0f,  1.0f,-1.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // top left

		1.0f,  1.0f, 1.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		1.0f, -1.0f, 1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
	    1.0f, -1.0f,-1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
	    1.0f,  1.0f,-1.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // top left

		1.0f,  1.0f, 1.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		1.0f, -1.0f, 1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
	   -1.0f, -1.0f, 1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
	   -1.0f,  1.0f, 1.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // top left

		-1.0f,  1.0f, 1.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		-1.0f, -1.0f, 1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-1.0f, -1.0f,-1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-1.0f,  1.0f,-1.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // top left

		 1.0f,  1.0f, 1.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 1.0f,  1.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-1.0f,  1.0f,-1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-1.0f,  1.0f, 1.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // top left

		1.0f,  -1.0f, 1.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 1.0f,  -1.0f,-1.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-1.0f,  -1.0f,-1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-1.0f,  -1.0f, 1.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // top left
   };

	unsigned int indices[] = {
		//quad 1
		0, 1, 3,
		1, 2, 3,
		//quad 2
		4, 5, 7,
		5, 6, 7,
		//quad 3
		8, 9, 11,
		9, 10, 11,
		//quad 4
		12, 13, 15,
		13, 14, 15,
		//quad 5
		16, 17, 19,
		17, 18, 19,
		//quad 6
		20, 21, 23,
		21, 22, 23,
	};


	glm::vec3 lightPosition = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 lightRotation = glm::vec3(.01f, 0.0f, 0.0f);
	glm::vec3 lightScale = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::vec3 cubePositions[20];
	for(int i =0;i < 20;i++) {
		cubePositions[i] = glm::vec3(ew::RandomRange(-10,10), ew::RandomRange(-10,10), ew::RandomRange(-10,10));
	}
	glm::vec3 cubeRotations[20];
	for(int i =0;i < 20;i++) {
		cubeRotations[i] = glm::vec3(ew::RandomRange(-1.0f,1.0f), ew::RandomRange(-1.0f,1.0f), ew::RandomRange(-1.0f,1.0f));
	}
	glm::vec3 cubeScales[20];
	for(int i =0;i < 20;i++) {
		cubeScales[i] = glm::vec3(ew::RandomRange(0.2f,3.0f), ew::RandomRange(0.2f,3.0f), ew::RandomRange(0.2f,3.0f));
	}



	glEnable(GL_DEPTH_TEST);

	//enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);




	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

//sprite


	TextureLoader spriteTexture("assets/Textures/stoneWall.png",GL_TEXTURE_2D,GL_REPEAT,GL_NEAREST,true);



	spriteShader.use();
	spriteShader.setInt("texture1", 2);

	glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);

	float deltaTime = 0.0f;
	float previousTime = 0.0f;

	GLdouble mouseX,mouseY;
	glfwSetCursorPosCallback(window, GetMousePos);
	glfwSetScrollCallback(window, GetScrollDelta);
	//Render loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		//Clear framebuffer
		glClearColor(0.3f, 0.4f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		float timeValue = glfwGetTime();
		deltaTime = timeValue - previousTime;
		//Drawing happens here!
		glBindVertexArray(VAO);

		spriteShader.use();
		spriteShader.setFloat("uTime", timeValue);
		spriteShader.setVec3("lightPos",lightPosition + glm::vec3(1,1,1));

		myCamera.UpdateMousePosition(mousePos);
		myCamera.UpdateScroll(scrollDelta);
		scrollDelta = glm::vec2(0.0f);
		CheckInputs(window,&myCamera,deltaTime);
		glm::mat4 view;
		view = myCamera.View();

		spriteShader.setMat4("view", view);
		glm::mat4 projection = myCamera.Projection();
		spriteShader.setMat4("projection", projection);

		//light
		spriteShader.setVec3("objectColor",glm::vec3(1.0f,1.0f,1.0f));
		spriteShader.setVec3("lightColor",glm::vec3(1.0f,1.0f,1.0f));
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model,lightPosition);
		//model = glm::rotate(model, glm::radians(0.0f), lightRotation);
		model = glm::scale(model, lightScale);
		spriteShader.setMat4("model",model);
		glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0);

		for(int i = 0;i < 20;i++)
		{
			spriteShader.setVec3("objectColor",glm::vec3(2.0f,0.5f,0.31f));
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model,cubePositions[i]);
			model = glm::rotate(model, glm::radians(timeValue * 100.0f), cubeRotations[i] += glm::vec3(deltaTime,deltaTime,0));
			model = glm::scale(model, cubeScales[i]);
			spriteShader.setMat4("model",model);
			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, spriteTexture.GetTextureID());
			glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0);
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

