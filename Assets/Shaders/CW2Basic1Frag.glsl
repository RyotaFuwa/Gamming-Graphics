#version 400 core

uniform sampler2D cleanBubble;
uniform sampler2D dirtyBubble;
uniform float decay;

in Vertex {
    vec4 colour;
    vec2 texCoord;
} IN;

out vec4 fragColor;

void main(void) {
    fragColor = mix( texture(dirtyBubble, IN.texCoord),
        texture(cleanBubble, IN.texCoord), pow(decay, 2)) * IN.colour;
}