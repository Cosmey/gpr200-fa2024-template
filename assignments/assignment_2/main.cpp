#include <stdio.h>
#include <math.h>
#include <iostream>

#include <ew/external/glad.h>
#include <ew/ewMath/ewMath.h>
#include <ew/external/stb_image.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Reece/Shader.h"
#include "Reece/TextureLoader.h"
using namespace Reece;

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

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
	Shader backgroundShader("assets/Shaders/BackgroundVS.vs", "assets/Shaders/backgroundFS.fs");

	float spriteVertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
    };

	float backgroundVertices[] = {
		// positions          // colors           // texture coords
		1.0f,   1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
	   -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
	   -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
   };
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3,  // second triangle
	};

	//enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);





	//background
	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(backgroundVertices), backgroundVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(spriteVertices), spriteVertices, GL_STATIC_DRAW);

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


	TextureLoader spriteTexture("assets/Textures/Potion.png",GL_TEXTURE_2D,GL_REPEAT,GL_NEAREST,true);
	TextureLoader faceTexture("assets/Textures/awesomeface.png",GL_TEXTURE_2D,GL_REPEAT,GL_LINEAR,true);
	TextureLoader backgroundTexture("assets/Textures/stoneWall.png",GL_TEXTURE_2D,GL_REPEAT,GL_LINEAR,true);

	backgroundShader.use();
	backgroundShader.setInt("texture1", 0);
	backgroundShader.setInt("texture2", 1);

	spriteShader.use();
	spriteShader.setInt("texture1", 2);

	//Render loop
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		//Clear framebuffer
		glClearColor(0.3f, 0.4f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		double timeValue = glfwGetTime();
		//Drawing happens here!
		backgroundShader.use();
		glBindVertexArray(VAO);
		backgroundShader.setFloat("uTime", timeValue);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, backgroundTexture.GetTextureID());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, faceTexture.GetTextureID());
		glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);

		spriteShader.use();
		spriteShader.setFloat("uTime", timeValue);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, spriteTexture.GetTextureID());
		glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);



		glfwSwapBuffers(window);
	}
	printf("Shutting down...");
}
