#include "../include/sprite.hpp"

namespace te{
    Sprite::Sprite(VertexBuffer* vBuffer, IndexBuffer* iBuffer, const char* texture_path) : _texture(texture_path){
        vBuf = vBuffer;
        iBuf = iBuffer;
    }

    Sprite::~Sprite(){
        vBuf = nullptr;
        iBuf = nullptr;
    }

    void Sprite::Draw(){
        _texture.Bind();
        vBuf->Bind();
        iBuf->Draw();
    }
}
