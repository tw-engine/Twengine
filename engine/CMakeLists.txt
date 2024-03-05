cmake_minimum_required(VERSION 3.27)
project(Twengine)

# Output dir for the library
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# All engine source files
file(GLOB_RECURSE SRC src/*.cpp)
set(GLAD "../extern/glad/src/glad.c")
file(GLOB_RECURSE HEADER include/*.h include/*.hpp)

# Grouping files in IDEs that support it
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" PREFIX "src" FILES ${SRC})
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/include" PREFIX "include" FILES ${HEADER})

include_directories("../extern/glad/include")

# Creates the library from the sources
add_library(${PROJECT_NAME} ${SRC} ${GLAD})

# Setting the include dirs for the engine
target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Settings for C++ standard properties
set_target_properties(${PROJECT_NAME}
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

# Copies files to destinations
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/include DESTINATION ${CMAKE_BINARY_DIR}/lib)
