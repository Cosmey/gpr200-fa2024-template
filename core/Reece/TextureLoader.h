//
// Created by reece.enthoven on 9/25/2024.
//

#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H
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
#include "../ew/external/stb_image.h"
using namespace std;

namespace Reece
{
    class TextureLoader {
    public:
        TextureLoader(const string& texturePath,GLenum textureType,GLint wrapMode,GLint filterMode,bool flip);

    };
}




#endif //TEXTURELOADER_H
