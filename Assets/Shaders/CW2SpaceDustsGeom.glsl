#version 330 core

uniform mat4 viewMatrix = mat4(1.0f);
uniform mat4 projMatrix = mat4(1.0f);
uniform mat4 modelMatrix = mat4(1.0f);
uniform vec3 loc;

layout(points) in;
layout(points, max_vertices = 8) out;

in Vertex {
    vec4 colour;
} IN[];

out Vertex {
    vec3 worldPos;
    vec4 colour;
} OUT;

uniform float particleSize = 0.10f;

void main() {
    for(int i = 0; i < gl_in.length(); i++) {
        gl_PointSize = 100.0f;
        gl_Position = vec4(0, 0, 0, 1.0f);
        vec3 pos = vec3(0, 0, 0);
        OUT.colour = IN[i].colour;
        for(int j = 0; j < 8; j++) {
            OUT.worldPos = (modelMatrix * vec4(pos, 1.0f)).xyz;
            gl_Position = (projMatrix * viewMatrix) * vec4(OUT.worldPos, 1.0f);
            pos += loc * 1.0f / 8.0f;
            EmitVertex();
            EndPrimitive();
        }
    }
}