#include "light.hpp"

/*
void afficherLight(LightProgram &light, char* couleur, glm::mat4 ViewMatrix){
    
    if(strcmp(couleur, "r") != 0){
        glUniform3f(light.uKd, 0.9, 0.1, 0.1);
        glUniform3f(light.uKs, 0.9, 0.1, 0.1);
        glUniform3f(light.uSchininess, 0.9, 0.9, 0.9);

        glm::vec4 Light(1., 1., 1., 0.);
        Light = Light*ViewMatrix;
        glUniform3f(light.uLightPos_vs, Light.x, Light.y, Light.z);
        glUniform3f(light.uLightIntensity, 0.9, 0.9, 0.9);
    }
    if(strcmp(couleur, "b") != 0){
        glUniform3f(light.uKd, 0.1, 0.1, 0.9);
        glUniform3f(light.uKs, 0.1, 0.1, 0.9);
        glUniform3f(light.uSchininess, 0.9, 0.9, 0.9);

        glm::vec4 Light(1., 1., 1., 0.);
        Light = Light*ViewMatrix;
        glUniform3f(light.uLightPos_vs, Light.x, Light.y, Light.z);
        glUniform3f(light.uLightIntensity, 0.9, 0.9, 0.9);
    }
}
*/
void afficherLight(ponctLightProgram &light, glm::vec3 Kd, glm::vec3 Ks, float shininess, float intensity, glm::mat4 ViewMatrix){
        glUniform3f(light.uKd, Kd.x, Kd.y, Kd.z);
        glUniform3f(light.uKs, Ks.x, Ks.y, Kd.z);
        glUniform3f(light.uSchininess, shininess, shininess, shininess);

        glm::vec4 Light(1., 1., 1., 0.);
        Light = Light*ViewMatrix;
        glUniform3f(light.uLightPos_vs, Light.x, Light.y, Light.z);
        glUniform3f(light.uLightIntensity, intensity, intensity, intensity);
}

void afficherDirLight(dirLightProgram &light, glm::vec3 Kd, glm::vec3 Ks, float shininess, float intensity, glm::mat4 ViewMatrix){
        glUniform3f(light.uKd, Kd.x, Kd.y, Kd.z);
        glUniform3f(light.uKs, Ks.x, Ks.y, Kd.z);
        glUniform3f(light.uSchininess, shininess, shininess, shininess);

        glm::vec4 Light(1., 1., .1, 0.);
        Light = Light*ViewMatrix;
        glUniform3f(light.uLightDir_vs, Light.x, Light.y, Light.z);
        glUniform3f(light.uLightIntensity, intensity, intensity, intensity);
}

void afficherTorcheLight(ponctLightProgram &light, glm::vec3 Kd, glm::vec3 Ks, float shininess, float intensity, glm::vec3 Position){
        glUniform3f(light.uKd, Kd.x, Kd.y, Kd.z);
        glUniform3f(light.uKs, Ks.x, Ks.y, Kd.z);
        glUniform3f(light.uSchininess, shininess, shininess, shininess);

        glUniform3f(light.uLightPos_vs, Position.x, Position.y, Position.z);
        glUniform3f(light.uLightIntensity, intensity, intensity, intensity);
}