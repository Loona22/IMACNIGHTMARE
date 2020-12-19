#version 300 es

precision mediump float;

in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; // Coordonnées de texture du sommet

out vec3 fColor;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;

vec3 blinnPhong(){
    vec3 wi = normalize(uLightDir_vs);
    vec3 w0 = normalize(-vPosition_vs);
    vec3 halfvector = (w0 + wi)*0.5;
    return uLightIntensity*(uKd*dot(wi, vNormal_vs) + uKs*pow(dot(halfvector, vNormal_vs), uShininess));
    }

void main() {
    fColor = blinnPhong();
}
