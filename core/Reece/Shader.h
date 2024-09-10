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
#include <C:\Users\reece.enthoven\gpr200-fa2024-template\core\ew\external/glad.h>
#include <C:\Users\reece.enthoven\gpr200-fa2024-template\core\ew\ewMath/ewMath.h>
using namespace std;


class Shader {
public:
    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath);

    void use();
    void setBool(const string &name, bool value) const;
    void setInt(const string &name, int value) const;
    void setFloat(const string &name, float value) const;
};



#endif //SHADER_H
