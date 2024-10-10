//
// Created by Reece on 10/9/2024.
//

#include "Cube.h"

namespace Reece {
    Cube::Cube(Shader newShader,glm::vec3 position, glm::vec3 rotation, glm::vec3 scale) : ThreeDObject(position, rotation, scale)
    {
        *myShader = newShader;
        unsigned int VBO, EBO;
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

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
    }
    void Cube::SetTexture(string newTexture) {
        *myTexture = TextureLoader(newTexture,GL_TEXTURE_2D,GL_REPEAT,GL_NEAREST,true);
        myShader->use();
        myShader->setInt("texture1", 0);
    }
    void Cube::Draw()
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model,position);
        model = glm::rotate(model, glm::radians(180.0f), rotation);
        model = glm::scale(model, scale);
        myShader->setMat4("model",model);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, myTexture->GetTextureID());
        glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0);
    }

}