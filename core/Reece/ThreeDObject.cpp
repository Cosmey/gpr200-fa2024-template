//
// Created by Reece on 10/9/2024.
//
#include "ThreeDObject.h"

namespace Reece {
    ThreeDObject::ThreeDObject(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) {
        this->position = position;
        this->rotation = rotation;
        this->scale = scale;
    }

}