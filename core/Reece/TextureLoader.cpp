//
// Created by reece.enthoven on 9/25/2024.
//

#include "TextureLoader.h"

namespace Reece
{
    TextureLoader::TextureLoader(const string& texturePath, GLenum textureType, GLint wrapMode, GLint filterMode,bool flip)
    {
        //flips sprite if needed
        stbi_set_flip_vertically_on_load(flip);

        //setting up texture space
        unsigned int texture;
        glGenTextures(1, &texture);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(textureType, texture);

        //set wrap and filtering modes
        glTexParameteri(textureType, GL_TEXTURE_WRAP_S, wrapMode);
        glTexParameteri(textureType, GL_TEXTURE_MIN_FILTER, filterMode);

        //create texture attibute varibles
        int width, height, nrChannels;

        //loads in the texture
        unsigned char *data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            //makes sure nrChannels lines up with color channels
            GLint format;
            if(nrChannels == 1)
            {
                format = GL_RED;
            }
            else if(nrChannels == 2)
            {
                format = GL_RG;
            }
            else if(nrChannels == 3)
            {
                format = GL_RGB;
            }
            else
            {
                format = GL_RGBA;
            }
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        }
        else
        {
            std::cout << "Failed to load texture " << texturePath << std::endl;
        }
        stbi_image_free(data);
    }

}