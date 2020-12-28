#version 300 es

precision mediump float;

// Attributs de sommet
layout(location = 0) in vec3 aVertexPosition; // Position du sommet

// Matrices de transformations reçues en uniform
uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

void main(){
    vec4 vertexPosition = vec4(aVertexPosition, 1);

    // Calcul de la position projetée
    gl_Position = uMVPMatrix * vertexPosition;
}