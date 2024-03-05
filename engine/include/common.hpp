#ifndef TE_COMMON_HPP
#define TE_COMMON_HPP

#include "../../extern/glad/include/glad/glad.h"
#include "../../extern/glfw/include/GLFW/glfw3.h"

#include <iostream>

class NoCopy{
public:
    NoCopy() = default;
    NoCopy(const NoCopy&) = delete;
    void operator=(const NoCopy&) = delete;
};

#endif
