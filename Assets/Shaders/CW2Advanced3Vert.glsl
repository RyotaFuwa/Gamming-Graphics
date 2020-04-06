# version 400 core

uniform mat4 viewMatrix = mat4(1.0f );
uniform mat4 projMatrix = mat4(1.0f );
uniform mat4 modelMatrix = mat4(1.0f );

uniform float decay;

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 colour;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec3 normal;

float expdecay(float t) {
	return (exp(t) - 1) / (exp(1) - 1) ;
}

out Vertex {
    vec3 worldPos;
    vec4 colour;
    vec2 texCoord;
    vec3 normal;
} OUT ;

void main ( void ) {
    OUT.worldPos = (modelMatrix * vec4(position, 1.0f)).xyz * expdecay(decay); 
    gl_Position = projMatrix * viewMatrix * vec4(OUT.worldPos, 1.0f);

    mat3 normalMatrix = transpose( inverse( mat3( modelMatrix )));
    vec3 normal = normalize(normalMatrix * normalize( normal ));
    OUT.normal =  normal;

    OUT.colour = colour;
    OUT.texCoord = texCoord;
}