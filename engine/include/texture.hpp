#ifndef TW_TEXTURE_HPP
#define TW_TEXTURE_HPP

#include "../include/common.hpp"

namespace te{
    class Texture {
    public:
        Texture(const char* path);
        ~Texture();

        void Bind();
    private:
        void LoadImage(const char* path, uint8_t** out_data);

        uint32_t _handle;

        int _width;
        int _height;
    };
}

#endif
