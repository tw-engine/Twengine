#ifndef TE_SHADER_HPP
#define TE_SHADER_HPP

#include "buffer.hpp"
#include "math_types.hpp"

#include <cstdint>

namespace te {
    class Shader {
    public:
        Shader();
        ~Shader();

        void UpdateState(UBO ubo);
    private:
        uint32_t _handle;

        UBO _global_uniform_object;
        UniformBuffer* _global_uniform_buffer;
    };
}

#endif
