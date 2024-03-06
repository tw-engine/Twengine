#include "../include/sprite.hpp"

namespace te{
    Sprite::Sprite(VertexBuffer* vBuffer, IndexBuffer* iBuffer){
        vBuf = vBuffer;
        iBuf = iBuffer;
    }

    Sprite::~Sprite(){
        vBuf = nullptr;
        iBuf = nullptr;
    }

    void Sprite::LoadTexture(const char* file, GLint loadFmt, GLint sourceFmt){
        glGenTextures(1, &_texture);
        glBindTexture(GL_TEXTURE_2D, _texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width, height, channels;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* data = stbi_load(file, &width, &height, &channels, 0);
        
        if(!data){
            std::cerr << "Failed to load texture at: " << file << '\n';
            stbi_image_free(data);
        }
        
        glTexImage2D(GL_TEXTURE_2D, 0, loadFmt, width, height, 0, sourceFmt, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Sprite::Draw(){
        glBindTexture(GL_TEXTURE_2D, _texture);

        vBuf->Bind();
        iBuf->Draw();
    }
}