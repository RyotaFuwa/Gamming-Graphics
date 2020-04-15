# version 400 core

uniform vec4 col = vec4(-1, -1, -1, -1);

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 colour;
layout(location = 3) in vec3 normal;

out Vertex {
    vec4 colour;
} OUT ;

void main ( void ) {
    gl_Position = vec4(position, 1.0);
    if(col.x < 0)
        OUT.colour = colour;
    else
        OUT.colour = col;
}