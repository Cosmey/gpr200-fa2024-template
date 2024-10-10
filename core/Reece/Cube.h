//
// Created by Reece on 10/9/2024.
//

#ifndef CUBE_H
#define CUBE_H
#include "ThreeDObject.h"


namespace Reece {
    class Cube : public ThreeDObject {
    public:
        Cube(Shader newShader, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
    	void SetTexture(string newTexture) override;
    	void Draw() override;
    private:
        float vertices[192] = {
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

	unsigned int indices[36] = {
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
    };
}




#endif //CUBE_H
