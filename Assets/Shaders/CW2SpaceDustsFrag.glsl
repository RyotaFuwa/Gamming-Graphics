#version 400 core

uniform vec3 cameraPos;
uniform vec3 lightColour;
uniform vec3 lightPos;
uniform float lightRadius;

in Vertex {
    vec3 worldPos;
    vec4 colour;
} IN;

out vec4 fragColor;

void main(void) {
    vec3 incident = normalize(lightPos - IN.worldPos);
    vec3 viewDir  = normalize(cameraPos - IN.worldPos);
    vec3 halfDir  = normalize(incident + viewDir);
    float dist    = length(lightPos - IN.worldPos);
    float atten   = 1.0 - clamp(dist / lightRadius, 0.0, 1.0);
    
    vec3 ambient   = IN.colour.rgb * lightColour * 0.25;
    vec3 diffuse   = IN.colour.rgb * lightColour * atten;
    vec3 specular  = lightColour * atten;
    fragColor      = vec4(ambient + diffuse, IN.colour.a);
}