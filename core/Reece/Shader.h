//
// Created by reece.enthoven on 9/9/2024.
//

#ifndef SHADER_H
#define SHADER_H

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
using namespace std;

namespace Reece
{
    class Shader {
    public:
        unsigned int ID;

        Shader(const char* vertexPath, const char* fragmentPath);

        void use();
        void setBool(const string &name, bool value) const;
        void setInt(const string &name, int value) const;
        void setFloat(const string &name, float value) const;
        void setMat4(const string &name, const glm::mat4 &m);
        void setVec3(const string &name,const glm::vec3 &v);
        void checkCompileErrors(unsigned int shader, string type);

    };
}




#endif //SHADER_H
