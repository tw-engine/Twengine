#include "../include/texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../../extern/stb/stb_image.h"

namespace te{
    Texture::Texture(const char* path) {
        if(path == NULL)
            return;

        glGenTextures(1, &_handle);
        glBindTexture(GL_TEXTURE_2D, _handle);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        uint8_t* data = NULL;
        LoadImage(path, &data);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(data);
    }

    Texture::~Texture() {
        glDeleteTextures(1, &_handle);
    }

    void Texture::Bind() {
        glBindTexture(GL_TEXTURE_2D, _handle);
    }
        
    void Texture::LoadImage(const char* path, uint8_t** out_data) {
        int channels = 0; /* Must be passed to stbi_load */

        stbi_set_flip_vertically_on_load(true);

        (*out_data) = stbi_load(path, &_width, &_height, &channels, 0);

        if((*out_data)== NULL) {
            std::cerr << "Failed to load texture at: \"" << path << "\"\n";
            stbi_image_free((*out_data));
            exit(EXIT_FAILURE);
        }
    }
}
