#ifndef TE_SPRITE_HPP
#define TE_SPRITE_HPP

#include "buffer.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../../extern/stb/stb_image.h"

namespace te{
    class Sprite{
    public:
        Sprite(VertexBuffer* vBufffer, IndexBuffer* iBuffer);
        virtual ~Sprite();

        void LoadTexture(const char* file, GLint loadFmt, GLint sourceFmt);

        void Draw();

    private:
        unsigned int _texture;

        VertexBuffer* vBuf;
        IndexBuffer* iBuf;
    };
}

#endif