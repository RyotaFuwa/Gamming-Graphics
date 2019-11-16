#version 400 core

uniform mat4 modelMatrix 	= mat4(1.0f);
uniform mat4 viewMatrix 	= mat4(1.0f);
uniform mat4 projMatrix 	= mat4(1.0f);

uniform vec3 center = vec3(0.0f);

uniform float time = 0.0f;
uniform float timeLimit = 10.0f;

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 colour;	
layout(location = 2) in vec2 texCoord;

out Vertex
{
	vec4 colour;
	vec2 texCoord;
} OUT;

void main(void)
{
	mat4 mvp 		= (projMatrix * viewMatrix * modelMatrix);

    if(time >= timeLimit)
        gl_Position = vec4(center, 1.0f);
    else {
    float rate = 1.0f - (time / timeLimit);
    vec3 newPosition = (position - center) * rate;
	gl_Position		= mvp * vec4(newPosition, 1.0f);
    }

	OUT.texCoord	= texCoord;
	OUT.colour		= colour;
}