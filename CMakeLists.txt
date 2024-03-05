cmake_minimum_required(VERSION 3.27)
project(Twengine LANGUAGES CXX VERSION 0.1.0)

option(BUILD_DEMO "Build the demo project" ON)
option(BUILD_SHADERS "Build shaders" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(BUILD_DEMO)
	message("Building Demo")
	add_subdirectory(demo)
endif()

add_subdirectory(engine)

add_subdirectory(extern/glfw)