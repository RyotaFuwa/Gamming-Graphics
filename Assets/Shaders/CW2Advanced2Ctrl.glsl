#version 400 core

layout(vertices = 4) out;

in Vertex {
    vec2 texCoord;
    vec3 normal;
} IN[] ;

out Vertex {
    vec2 texCoord;
    vec3 normal;
} OUT[];

void main() {
    gl_TessLevelInner[0] = 4000;
    gl_TessLevelInner[1] = 4000;
    gl_TessLevelOuter[0] = 4000;
    gl_TessLevelOuter[1] = 4000;
    gl_TessLevelOuter[2] = 4000;
    gl_TessLevelOuter[3] = 4000;

    OUT[gl_InvocationID].texCoord = IN[gl_InvocationID].texCoord;
    OUT[gl_InvocationID].normal = IN[gl_InvocationID].normal;
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}