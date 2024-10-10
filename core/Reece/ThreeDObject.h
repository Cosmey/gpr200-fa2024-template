//
// Created by Reece on 10/9/2024.
//

#ifndef THREEDOBJECT_H
#define THREEDOBJECT_H
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include "../ew/external/glad.h"
#include "../ew/ewMath/ewMath.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "TextureLoader.h"
#include "Shader.h"
using namespace std;

namespace Reece {
    class ThreeDObject {
    public:
        ThreeDObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);
        virtual void SetTexture(string newTexture) = 0;
        virtual void Draw() = 0;
        TextureLoader *myTexture;
        Shader *myShader;

        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
    };
}




#endif //THREEDOBJECT_H
