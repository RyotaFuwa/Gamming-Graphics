#version 330 core

uniform mat4 viewMatrix = mat4(1.0f );
uniform mat4 projMatrix = mat4(1.0f );
uniform mat4 modelMatrix = mat4(1.0f );
uniform vec3 giggle;
uniform float decay;
uniform float half = 0.5;
uniform float halfValue = 150.0;

uniform mat4 expandMatrix[];

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
    float a = exp(-pow(start, 0.1));
    return value / (1 - a) * (exp(-pow(decay, 0.1)) - a);
}

void main() {
    for(int i = 0; i < gl_in.length(); i++) {
        vec4 newPos = gl_in[i].gl_Position;
        if(decay < half) {
            newPos += (vec4(IN[i].normal.xyz, 0.0f) + vec4(giggle, 0.0f)) * expansion(decay, half, halfValue) * 0.01 * pow(i, 3);
        }
        mat3 normalMatrix = transpose( inverse( mat3( modelMatrix )));
        vec3 normal = normalize(normalMatrix * normalize( -IN[i].normal ));
        OUT.normal = normal;
        OUT.worldPos  = (modelMatrix * vec4(newPos)).xyz;
        gl_Position = (projMatrix * viewMatrix) * vec4(OUT.worldPos, 1.0f);
        OUT.colour = IN[i].colour;
        OUT.texCoord = IN[i].texCoord;
        EmitVertex();
    }
        EndPrimitive();
}