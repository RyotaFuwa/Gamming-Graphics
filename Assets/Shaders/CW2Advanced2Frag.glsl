#version 400 core
uniform sampler2D chessBoard;

/*
in VertexOut {
    vec3 normal;
} IN;

out vec4 fragColor;

void main(void) {
    fragColor = texture(chessBoard, IN.texCoord);
}
*/

in VertexOut {
    vec2 texCoord;
    vec4 colour;
} IN;

out vec4 fragColor;

void main(void) {
    fragColor = IN.colour;
}