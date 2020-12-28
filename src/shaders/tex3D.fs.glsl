#version 300 es

precision mediump float;

in vec2 vTexCoords; // Coordonnées de texture du sommet

out vec3 fTex;

uniform sampler2D uTexture;

void main() {
    fTex = texture(uTexture, vTexCoords).xyz;
}
