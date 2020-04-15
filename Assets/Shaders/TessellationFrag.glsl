# version 400 core
uniform sampler2D heightMap ;

in VertexOut {
    vec2 texCoord ;
} IN ;

out vec4 fragColor ;

void main( void ) {
    fragColor = texture( heightMap , IN.texCoord );
}
