#version 450

layout(location = 0) in vec3 in_color;
layout(location = 1) in vec2 in_texCoord;

//layout(binding = 1) uniform sampler2D uni_texture;

layout(location = 0) out vec4 out_color;

void main() {
    out_color = texture(in_texCoord, in_texCoord) * vec4(in_color, 1.0);
}
