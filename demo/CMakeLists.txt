cmake_minimum_required(VERSION 3.27)
project(TwengineDemo)

# Output dir for the library
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# All engine source files
file(GLOB_RECURSE SRC src/*.cpp)

# Creates the library from the sources
add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR}/lib/include)
target_link_directories(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR}/lib)
target_link_libraries(${PROJECT_NAME} PRIVATE Twengine glfw)
