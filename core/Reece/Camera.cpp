//
// Created by Reece on 10/9/2024.
//

#include "Camera.h"

namespace Reece {
    Camera::Camera(glm::vec3 position,float yaw,float pitch,float fov,glm::vec2 newAspectRatio)
    {
        aspectRatio = newAspectRatio;
        front = glm::vec3(0.0f, 0.0f, -1.0f);
        up    = glm::vec3(0.0f, 1.0f, 0.0f);
        right = glm::vec3(1.0f, 0.0f, 0.0f);
        this->position = position;
        this->front = front;
        this->up = up;
        this->yaw = yaw;
        this->pitch = pitch;
        this->fov = fov;
        lastX = aspectRatio.x / 2.0f;
        lastY = aspectRatio.y / 2.0f;
        firstMouse = true;
    }
    void Camera::UpdateMousePosition(glm::vec2 mousePosition)
    {
        if (firstMouse)
        {
            lastX = mousePosition.x;
            lastY = mousePosition.y;
            firstMouse = false;
        }

        float xoffset = mousePosition.x - lastX;
        float yoffset = lastY - mousePosition.y;
        lastX = mousePosition.x;
        lastY = mousePosition.y;

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
        front = glm::normalize(direction);
    }
    void Camera::UpdateScroll(glm::vec2 offSet)
    {
        fov -= (float)offSet.y;
        if (fov < 1.0f)
            fov = 1.0f;
        if (fov > 120.0f)
            fov = 120.0f;
    }
    glm::mat4 Camera::View()
    {
        return glm::lookAt(position,position + front,up);
    }
    glm::mat4 Camera::Projection()
    {
        return glm::perspective(glm::radians(fov), (float)aspectRatio.x / (float)aspectRatio.y, 0.1f, 100.0f);
    }

    glm::vec3 Camera::Front()
    {
        return front;
    }
    glm::vec3 Camera::Up()
    {
        return up;
    }
    glm::vec3 Camera::Right()
    {
        return right;
    }

}