#ifndef LIGHT_HPP
#define LIGHT_HPP

#include <GL/glew.h>
#include <iostream> 
#include <string>
#include <vector>

#include <glimac/glm.hpp>
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>


struct ponctLightProgram {
    glimac::Program ponct_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture;

    GLint uKd;
    GLint uKs;
    GLint uSchininess;
    GLint uLightPos_vs;
    GLint uLightIntensity;

    ponctLightProgram(const glimac::FilePath& applicationPath):
        ponct_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/ponctuelleLight.fs.glsl")) {
        uMVPMatrix = glGetUniformLocation(ponct_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(ponct_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(ponct_Program.getGLId(), "uNormalMatrix");
        uTexture = glGetUniformLocation(ponct_Program.getGLId(), "uTexture");

        uKd = glGetUniformLocation(ponct_Program.getGLId(), "uKd");
        uKs = glGetUniformLocation(ponct_Program.getGLId(), "uKs");
        uSchininess = glGetUniformLocation(ponct_Program.getGLId(), "uSchininess");
        uLightPos_vs = glGetUniformLocation(ponct_Program.getGLId(), "uLightPos_vs");
        uLightIntensity = glGetUniformLocation(ponct_Program.getGLId(), "uLightIntensity");
    }

};

struct dirLightProgram {
    glimac::Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture;

    GLint uKd;
    GLint uKs;
    GLint uSchininess;
    GLint uLightDir_vs;
    GLint uLightIntensity;

    dirLightProgram(const glimac::FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/directionalLight.fs.glsl")) {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");

        uKd = glGetUniformLocation(m_Program.getGLId(), "uKd");
        uKs = glGetUniformLocation(m_Program.getGLId(), "uKs");
        uSchininess = glGetUniformLocation(m_Program.getGLId(), "uSchininess");
        uLightDir_vs = glGetUniformLocation(m_Program.getGLId(), "uLightDir_vs");
        uLightIntensity = glGetUniformLocation(m_Program.getGLId(), "uLightIntensity");
    }
};

//void afficherLight(LightProgram &light, char* couleur, glm::mat4 ViewMatrix);

void afficherLight(ponctLightProgram &light, glm::vec3 Kd, glm::vec3 Ks, float shininess, float intensity, glm::mat4 ViewMatrix);

void afficherDirLight(dirLightProgram &light, glm::vec3 Kd, glm::vec3 Ks, float shininess, float intensity, glm::mat4 ViewMatrix);

void afficherTorcheLight(ponctLightProgram &light, glm::vec3 Kd, glm::vec3 Ks, float shininess, float intensity, glm::vec3 Position);

#endif