# version 400 core

layout (quads, cw) in ;

uniform sampler2D heightMap ;

uniform mat4 modelMatrix ;
uniform mat4 viewMatrix ;
uniform mat4 projMatrix ;

in Vertex {
    vec4 colour;
    vec2 texCoord ;
    vec3 normal ; 
} IN[] ;

out VertexOut {
    vec3 worldPos;
    vec4 colour;
    vec2 texCoord ;
    vec3 normal ; 
}  OUT;


vec3 QuadMixVec3( vec3 a , vec3 b , vec3 c , vec3 d ) {
vec3 p0 = mix(a ,c , gl_TessCoord.x );
vec3 p1 = mix(b ,d , gl_TessCoord.x );

return mix ( p0 , p1 , gl_TessCoord.y );
}

vec2 QuadMixVec2( vec2 a , vec2 b , vec2 c , vec2 d ) {
vec2 p0 = mix(a ,c , gl_TessCoord.x );
vec2 p1 = mix(b ,d , gl_TessCoord.x );

return mix ( p0 , p1 , gl_TessCoord.y );
}

void main () {
    OUT.texCoord = QuadMixVec2(IN[0].texCoord ,
        IN[1].texCoord,
        IN[2].texCoord,
        IN[3].texCoord);

    vec3 combinedPos = QuadMixVec3(gl_in[0].gl_Position.xyz,
        gl_in[1].gl_Position.xyz,
        gl_in[2].gl_Position.xyz,
        gl_in[3].gl_Position.xyz);
    vec4 worldPos = modelMatrix * vec4(combinedPos , 1.0f);
    float height = texture(heightMap , OUT.texCoord).x;
    worldPos.y += height * 50;
    OUT.worldPos = worldPos.xyz;
    gl_Position = projMatrix * viewMatrix * worldPos;

    vec3 normal = QuadMixVec3(IN[0].normal,
        IN[1].normal,
        IN[2].normal,
        IN[3].normal);

}
