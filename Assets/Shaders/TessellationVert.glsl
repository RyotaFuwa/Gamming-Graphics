# version 400 core

layout ( location = 0) in vec3 position ;
layout ( location = 2) in vec2 texCoord ;
layout ( location = 3) in vec3 normal;

out Vertex {
    vec2 texCoord ;
    vec3 normal;
} OUT ;

void main( void ) {
    gl_Position = vec4( position , 1.0);
    OUT.texCoord = texCoord;
    OUT.normal = normal;
}
