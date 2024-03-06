#version 450

layout(location = 0) in vec3 in_color;
layout(location = 1) in vec2 in_texCoord;

layout(binding = 0) uniform sampler2D uni_texture;

layout(location = 0) out vec4 out_color;

void main() {
    out_color = texture(uni_texture, in_texCoord);
}
