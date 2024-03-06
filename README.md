![Cpp Badge](https://img.shields.io/badge/C++17-blue?style=for-the-badge&logo=c%2B%2B)
![Cmake Badge](https://img.shields.io/badge/CMAKE-orange?style=for-the-badge&logo=cmake)
![OpenGL Badge](https://img.shields.io/badge/OPENGL-orange?style=for-the-badge&logo=opengl&logoColor=white)

# Under Construction :)

# Twengine
Twengine aka twin engine is a game engine/framework used to make 2D games in C++

- [Install](#install)
- [Building](#building)
- - [Manually building](#manual-building)
- - [Automatic building](#automatic-building)

## Install

Twengine requires a couple of packages to build and use.

| Dependencies |
| - |
| GLFW |
| OpenGL |

To install Twengine you can simply
```
$ git clone --recursive https://github.com/tw-engine/Twengine.git
```

## Building

Twengine primarily uses cmake to build the library and the demo, but also uses glslc to compile the shaders.

### Manual building

Manually compiling the shaders can be done with the following command
```
$ glslc shader.vert -o shader.vert.spv
```
The shaders have to be located like this
```
- executable
- shaders/
- - shader.vert.spv
- - shader.frag.spv
```

### Automatic building

The cmake script can take some arguments to effect the build process
```
// To simply build the library, demo, and shaders
$ cmake . && make

// To only build the library and shaders and exclude the demo
$ cmake . -DBUILD_DEMO=OFF && make

// To exclude shaders
$ cmake . -DBUILD_SHADERS=OFF && make

// To not run the demo after building
$ cmake . -DRUN_AFTER_BUILD=OFF && make

// To chain all commands
$ cmake . -DBUILD_DEMO=OFF -DBUILD_SHADERS=OFF -DRUN_AFTER_BUILD=OFF && make
```