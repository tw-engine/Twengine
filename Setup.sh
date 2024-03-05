#!/bin/bash

shaders=engine/shaders

buildAndRun="yes"

glslc $shaders/shader.vert -o vert.spv
glslc $shaders/shader.frag -o frag.spv

cmake .
make

for arg in "$@"; do
    if [[ $arg == "nr" || $arg == "norun" ]]; then
        buildAndRun="no"
    fi
done

if [[ "$buildAndRun" == "yes" ]]; then
    ./bin/TwengineDemo
fi
