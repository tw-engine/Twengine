#version 450

layout(location = 0) in vec2 in_position;
layout(location = 1) in vec3 in_color;
layout(location = 2) in vec2 in_texCoord;

layout(location = 0) out vec3 out_color;
layout(location = 1) out vec2 out_texCoord;

layout (std140, binding = 0) uniform UniformBufferObject 
{
    vec2 model;
    vec2 pixelSize;
    vec2 origin;
} ubo;

void main()  {
    gl_Position = vec4(ubo.pixelSize * (in_position + ubo.model - ubo.origin), 0.0f, 1.0f);

    out_color = in_color;
    out_texCoord = in_texCoord;
}
