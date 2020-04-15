#version 400 core

uniform mat4 modelMatrix 	= mat4(1.0f);
uniform mat4 viewMatrix 	= mat4(1.0f);
uniform mat4 projMatrix 	= mat4(1.0f);

uniform vec3 center = vec3(0.0f);
uniform float decay;

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 colour;	
layout(location = 2) in vec2 texCoord;

out Vertex
{
	vec4 colour;
	vec2 texCoord;
} OUT;

float log10(float x) {
	return log(x) / log(10);
}

void main(void)
{
	mat4 mvp 		= (projMatrix * viewMatrix * modelMatrix);
	float logdecay = log10(1 + 9.0 * decay);

    vec3 newPosition = (position - center) * logdecay + center;

	gl_Position		= mvp * vec4(newPosition, 1.0f);
	OUT.colour		= vec4(colour.xyz, logdecay);
	OUT.texCoord	= texCoord;
}