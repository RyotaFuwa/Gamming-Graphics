#version 330 core

uniform mat4 viewMatrix = mat4(1.0f );
uniform mat4 projMatrix = mat4(1.0f );
uniform mat4 modelMatrix = mat4(1.0f );
uniform float decay;

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in Vertex {
    vec4 colour;
    vec2 texCoord; 
    vec3 normal; 
} IN[] ;

out VertexOut {
    vec3 worldPos;
    vec4 colour;
    vec2 texCoord;
    vec3 normal;
} OUT;

float expansion(float decay, float start, float value) {
    return value / (1 - exp(-start)) * (exp(-decay) - exp(-start));
}

void main() {
    for(int i = 0; i < gl_in.length(); i++) {
        float half  = 0.5;
        float halfValue = 50;
        vec4 newPos = gl_in[i].gl_Position;
        mat3 normalMatrix = transpose( inverse( mat3( modelMatrix )));
        vec3 normal = normalize(normalMatrix * normalize( - IN[i].normal ));
        if(decay < half) {
            newPos += (vec4(IN[i].normal.xyz, 0.0f) + vec4(giggle, 0.0f)) * expansion(decay, half, halfValue) * 0.05 * i;
        }
        OUT.normal = normal;
        vec3 wPos = (modelMatrix * vec4(newPos)).xyz;
        OUT.worldPos  = wPos;
        gl_Position = (projMatrix * viewMatrix) * vec4(wPos, 1.0f);
        OUT.colour = IN[i].colour;
        OUT.texCoord = IN[i].texCoord;
        EmitVertex();
    }
        EndPrimitive();
}