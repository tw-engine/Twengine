#ifndef TE_MATH_TYPES_HPP
#define TE_MATH_TYPES_HPP

constexpr float PI = 3.141592653589793f;

typedef struct vec2{
    struct {
        union {
            float x;
            float u;
        };
        union {
            float y;
            float v;
        };
    };
} vec2;

typedef struct vec3{
    struct {
        union {
            float x;
            float u;
            float r;
        };
        union {
            float y;
            float v;
            float g;
        };
        union {
            float z;
            float w;
            float b;
        };
    };
} vec3;

typedef struct vec4{
	struct{
        union{
            float x;
            float r;
        };
        union{
            float y;
            float g;
        };
        union{
            float z;
            float b;
        };
        union{
            float w;
            float a;
        };
	};
} vec4;

typedef struct Vertex {
    vec2 pos;
    vec3 col;
} Vertex;

typedef struct UBO{
	vec2 model;
	vec2 pixelSize;
	vec2 origin;
} UBO;

#endif
