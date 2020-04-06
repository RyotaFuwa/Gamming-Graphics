# version 400 core

uniform mat4 modelMatrix ;
uniform mat4 viewMatrix ;
uniform mat4 projMatrix ;

uniform float decay;
uniform float freq = 2.0f;

uniform sampler2D chessBoard;

layout (quads, cw) in ;

in Vertex { // Sent from the TCS
    vec2 texCoord ;
    vec3 normal;
} IN[]; // Equal to TCS layout size

out VertexOut { // Each TES works on a single vertex !
    vec2 texCoord;
    vec4 colour;
} OUT ;

float damping(float t, float amp, float freq, int phase=0) {
    float rad = freq * (t - phase / 360) * 2.0 * 3.1415926535;
	return amp * t * cos(rad);
}

vec3 QuadMixVec3( vec3 a , vec3 b , vec3 c , vec3 d ) {
vec3 p0 = mix(a ,c , gl_TessCoord.x );
vec3 p1 = mix(b ,d , gl_TessCoord.x );

return mix ( p0 , p1 , gl_TessCoord.y );
}

vec2 QuadMixVec2 ( vec2 a , vec2 b , vec2 c , vec2 d ) {
vec2 p0 = mix (a ,c , gl_TessCoord.x );
vec2 p1 = mix (b ,d , gl_TessCoord.x );

return mix ( p0 , p1 , gl_TessCoord.y );
}

void main () {
    vec3 combinedPos = QuadMixVec3( gl_in[0].gl_Position.xyz ,
        gl_in[1].gl_Position.xyz ,
        gl_in[2].gl_Position.xyz ,
        gl_in[3].gl_Position.xyz );

    OUT.texCoord = QuadMixVec2( IN[0].texCoord ,
        IN[1].texCoord ,
        IN[2].texCoord ,
        IN[3].texCoord );

    vec3 combinedNormal = QuadMixVec3( IN[0].normal ,
        IN[1].normal ,
        IN[2].normal ,
        IN[3].normal );

vec4 worldPos = modelMatrix * vec4(combinedPos , 1);
mat3 normalMatrix = transpose( inverse( mat3( modelMatrix )));
combinedNormal = normalize(normalMatrix * normalize(combinedNormal)) * damping(decay, 1.0, freq);

vec4 checkerCol = texture(chessBoard , OUT.texCoord);
float colAve = (checkerCol.x + checkerCol.y + checkerCol.z) / 3.0;
if(colAve >= 0.5){
    worldPos += vec4(combinedNormal, 0.0f) * -abs(damping(decay, 1.5, freq * 1.25));
    OUT.colour = vec4(damping(decay, 0.5, freq * 0.5) + 0.5, damping(decay, 0.3, freq) + 0.5, damping(decay, 0.25, freq * 2.0) + 0.75, 1.0);
}
if(colAve < 0.5){ 
    OUT.colour = vec4(0, 0, 0, 1.0);
}
gl_Position = projMatrix * viewMatrix * worldPos;
}