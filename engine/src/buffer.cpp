#include "../include/buffer.hpp"
#include "../include/math_types.hpp"

namespace te{
    Buffer::Buffer(BufferType type) {
        _type = type;

        glGenBuffers(1, &_handle);
        glBindBuffer(type, _handle);
    }

    Buffer::~Buffer() {
        glDeleteBuffers(1, &_handle);
    }

    void Buffer::Upload(size_t size, void* data) {
        glBufferData(_type, size, data, GL_STATIC_DRAW);
    }

    uint32_t Buffer::Get() const {
        return _handle;
    }

    /*----------------------------------------------------------------------------------------------*/

    VertexBuffer::VertexBuffer(size_t size, Vertex* vertices) : Buffer::Buffer(BUFFER_TYPE_VERTEX) {
        glGenVertexArrays(1, &_attributes);
        glBindVertexArray(_attributes);

        glVertexAttribPointer(0, (sizeof((Vertex*)0)->pos) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
        glVertexAttribPointer(1, (sizeof((Vertex*)0)->col) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, col));
        glVertexAttribPointer(2, (sizeof((Vertex*)0)->tex) / sizeof(float), GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex));

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        Upload(size, vertices);
    }

    VertexBuffer::~VertexBuffer() {
        glDeleteVertexArrays(1, &_attributes);
    }

    void VertexBuffer::Upload(size_t size, Vertex* vertices) {
        Buffer::Upload(size, vertices);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void VertexBuffer::Bind() {
        glBindVertexArray(_attributes);
    }

    /*----------------------------------------------------------------------------------------------*/

    IndexBuffer::IndexBuffer(uint32_t count, uint32_t* indices) : Buffer::Buffer(BUFFER_TYPE_INDEX) {
        Upload(count, indices);
    }

    void IndexBuffer::Upload(uint32_t count, uint32_t* indices) {
        _count = count; 
        _indices = indices;
    }

    IndexBuffer::~IndexBuffer() {}

    void IndexBuffer::Draw() {
        glDrawElements(GL_TRIANGLES, _count, GL_UNSIGNED_INT, _indices);
    }

    /*----------------------------------------------------------------------------------------------*/

    UniformBuffer::UniformBuffer(uint32_t shader_program) : Buffer::Buffer(BUFFER_TYPE_UNIFORM) {
        glBindBufferBase(GL_UNIFORM_BUFFER, 0, Get());
        
        _block_index = glGetUniformBlockIndex(shader_program, "UniformBufferObject");
        glUniformBlockBinding(shader_program, _block_index, 0);

        Buffer::Upload(sizeof(UBO), NULL);
    }

    UniformBuffer::~UniformBuffer() {}

    void UniformBuffer::Update(UBO data) {
        glBindBuffer(GL_UNIFORM_BUFFER, Get());
        glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(UBO), &data);
    }
}
