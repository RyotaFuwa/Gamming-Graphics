# version 400 core

uniform vec3 center = vec3(0.0f);
uniform vec3 giggle = vec3(0.0f);

uniform float decay;

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 colour;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 normal;

float log10(float x) {
	return log(x) / log(10);
}

out Vertex {
    vec4 colour;
    vec2 texCoord ;
    vec3 normal ; // transformed worldspace normal !
} OUT ;

void main ( void ) {
    vec3 newPosition = (position - center) * decay + center + giggle;

    gl_Position = vec4(newPosition, 1.0);
    OUT.colour = colour;
    OUT.texCoord = texCoord;
    OUT.normal =  normal;
}