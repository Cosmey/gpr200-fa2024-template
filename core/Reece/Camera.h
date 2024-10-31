//
// Created by Reece on 10/9/2024.
//

#ifndef CAMERA_H
#define CAMERA_H
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


namespace Reece {
    class Camera {
    public:
        Camera(glm::vec3 position,float yaw,float pitch,float fov,glm::vec2 aspectRatio);
        void UpdateMousePosition(glm::vec2 mousePosition,bool move);
        void UpdateScroll(glm::vec2 offSet);
        glm::mat4 View();
        glm::mat4 Projection();
        glm::vec3 Front();
        glm::vec3 Up();
        glm::vec3 Right();
        glm::vec3 position;

    private:
        glm::vec3 front, up, right;
        glm::vec2 aspectRatio;
        float pitch, roll, yaw;
        float lastX,lastY;
        float fov;
        bool firstMouse;
        bool movingTransition;
    };

}



#endif //CAMERA_H
