#ifndef TE_BUFFER_HPP
#define TE_BUFFER_HPP

#include "common.hpp"
#include "math_types.hpp"

#include <cstddef>
#include <cstdint>

namespace te{
    typedef enum BufferType {
        BUFFER_TYPE_VERTEX = GL_ARRAY_BUFFER,
        BUFFER_TYPE_INDEX = GL_ELEMENT_ARRAY_BUFFER,
        BUFFER_TYPE_UNIFORM = GL_UNIFORM_BUFFER
    } BufferType;

    class Buffer {
    public:
        Buffer(BufferType type);
        ~Buffer();

        void Upload(size_t size, void* data);

        uint32_t Get() const;
    private:
        uint32_t _handle;

        BufferType _type;
    };

    class VertexBuffer : Buffer {
    public:
        VertexBuffer(size_t size, Vertex* vertices);
        ~VertexBuffer();

        void Upload(size_t size, Vertex* vertices);

        void Bind();
        
    private:
        uint32_t _attributes;
    };

    class IndexBuffer : Buffer {
    public:
        IndexBuffer(uint32_t count, uint32_t* indices);
        ~IndexBuffer();

        void Upload(uint32_t count, uint32_t* indices);

        void Draw();
    private:
        uint32_t* _indices;
        uint32_t _count;
    };

    /*----------------------------------------------------------------------------------------------*/

    class UniformBuffer : Buffer {
    public:
        UniformBuffer(uint32_t shader_program);
        ~UniformBuffer();

        void Update(UBO data);

    private:
        uint32_t _block_index;
    };
}

#endif
