#version 400 core

layout(vertices = 4) out;

in Vertex {
    vec4 colour;
    vec2 texCoord;
    vec3 normal; 
} IN[] ;

out Vertex {
    vec4 colour;
    vec2 texCoord;
    vec3 normal;
} OUT[];


void main() {
    gl_TessLevelInner[0] = 200;
    gl_TessLevelInner[1] = 200;
    gl_TessLevelOuter[0] = 200;
    gl_TessLevelOuter[1] = 200;
    gl_TessLevelOuter[2] = 200;
    gl_TessLevelOuter[3] = 200;

    OUT[gl_InvocationID].colour = IN[gl_InvocationID].colour;
    OUT[gl_InvocationID].texCoord = IN[gl_InvocationID].texCoord;
    OUT[gl_InvocationID].normal = IN[gl_InvocationID].normal;
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}