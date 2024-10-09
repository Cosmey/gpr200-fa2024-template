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
using namespace Reece;

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;


glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);
bool firstMouse = true;
float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;
float yaw = -90.0f;
float pitch = 0.0f;
float fov = 60.0f;


void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

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
	Shader spriteShader("assets/Shaders/SpriteVS.vs", "assets/Shaders/SpiteFS.fs");







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

	glm::vec3 cameraTarget = glm::vec3(0.0f,0.0f,0.0f);
	glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
	glm::vec3 up = glm::vec3(0.0f,1.0f,0.0f);
	glm::vec3 cameraRight = glm::normalize(glm::cross(up,cameraDirection));

	glEnable(GL_DEPTH_TEST);

	//enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(0.0f), glm::vec3(1.0f,0.0f,0.0f));
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);



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
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
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
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, spriteTexture.GetTextureID());


		glfwSetCursorPosCallback(window,mouse_callback);



		float cameraSpeed = 5.0f; // adjust accordingly
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			cameraSpeed *= 2;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cameraPos += cameraSpeed * cameraFront * deltaTime;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cameraPos -= cameraSpeed * cameraFront * deltaTime;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed * deltaTime;
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			cameraPos += cameraSpeed * cameraUp * deltaTime;
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			cameraPos -= cameraSpeed * cameraUp * deltaTime;




		const float radius = 10.0f;
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;
		glm::mat4 view;
		view = glm::lookAt(cameraPos,cameraPos + cameraFront,cameraUp);

		spriteShader.setMat4("view", view);
		glm::mat4 projection = glm::perspective(glm::radians(fov), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
		spriteShader.setMat4("projection", projection);

		cout << deltaTime << endl;
		for(int i = 0;i < 20;i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model,cubePositions[i]);
			model = glm::rotate(model, glm::radians(180.0f), cubeRotations[i] += glm::vec3(deltaTime,deltaTime,0));
			model = glm::scale(model, cubeScales[i]);
			spriteShader.setMat4("model",model);
			glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0);
		}



		glfwSwapBuffers(window);

		previousTime = timeValue;
	}
	printf("Shutting down...");
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw   += xoffset;
	pitch += yoffset;

	if(pitch > 89.0f)
		pitch = 89.0f;
	if(pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	fov -= (float)yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 120.0f)
		fov = 120.0f;
}