#version 300 es

precision mediump float;

in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; // Coordonnées de texture du sommet

out vec3 fTex;

uniform sampler2D uEarthTexture;
uniform sampler2D uCloudTexture;

void main() {
    vec3 fTex1 = texture(uEarthTexture, vTexCoords).xyz;
    vec3 fTex2 = texture(uCloudTexture, vTexCoords).xyz;
    fTex = fTex1 + fTex2;
}
