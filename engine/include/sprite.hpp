#ifndef TE_SPRITE_HPP
#define TE_SPRITE_HPP

#include "buffer.hpp"
#include "texture.hpp"

namespace te{
    class Sprite{
    public:
        Sprite(VertexBuffer* vBuffer, IndexBuffer* iBuffer, const char* texture_path);
        virtual ~Sprite();

        void Draw();

    private:
        Texture _texture;

        VertexBuffer* vBuf;
        IndexBuffer* iBuf;
    };
}

#endif
