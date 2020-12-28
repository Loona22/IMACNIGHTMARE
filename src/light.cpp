#include "light.hpp"

void afficherponctLight(ponctLightProgram &light, glm::vec3 Kd, glm::vec3 Ks, float shininess, float intensity, glm::mat4 ViewMatrix){
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