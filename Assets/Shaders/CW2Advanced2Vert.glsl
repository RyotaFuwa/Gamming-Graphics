# version 400 core

uniform float decay;
uniform vec3 center = vec3(0, 0, 0);
uniform float freq = 2.0f;

uniform mat4 modelMatrix ;
uniform mat4 viewMatrix ;
uniform mat4 projMatrix ;

layout(location = 0) in vec3 position;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 normal;

float damping(float t, float amp, float freq) {
    float rad = freq * t * 2.0 * 3.1415926535;
	return amp * t * cos(rad);
}

out Vertex {
    vec2 texCoord ;
    vec3 normal;
} OUT;

void main ( void ) {
    vec3 newPosition = position * damping(decay, 1.0, freq);
    //gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(newPosition, 1.0);
    gl_Position =  vec4(newPosition, 1.0);
    OUT.texCoord = texCoord;
    OUT.normal = normal;

    // mat3 normalMatrix = transpose( inverse( mat3( modelMatrix )));
    // OUT.normal = normalize(normalMatrix * normalize( normal ));
}

/*
out Vertex {
    vec4 colour;
    vec2 texCoord;
} OUT ;

void main ( void ) {
    vec3 newPosition = (position - center) * damping(decay, 1.75, freq) + center;
    gl_Position = projMatrix * viewMatrix * modelMatrix * vec4(newPosition, 1.0);
    OUT.colour = vec4(colour.xyz, 1.0f);
    OUT.texCoord = texCoord; 
}
*/