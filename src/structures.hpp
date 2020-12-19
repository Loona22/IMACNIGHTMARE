#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/glm.hpp>
#include "glimac/Image.hpp"

using namespace glimac;

struct ObjetProgram {
    Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uObjTexture;

    ObjetProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/tex3D.fs.glsl")){
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uObjTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
        }
};

/*
struct LightProgram {
    Program m_Program;

    GLint uKd;
    GLint uKs;
    GLint uSchininess;
    GLint uLightDir_vs;
    //GLint uLightPos_vs;
    GLint uLightIntensity;

    LightProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/directionalLight.fs.glsl")){
        uKd = glGetUniformLocation(m_Program.getGLId(), "uKd");
        uKs = glGetUniformLocation(m_Program.getGLId(), "uKs");
        uSchininess = glGetUniformLocation(m_Program.getGLId(), "uSchininess");
        uLightDir_vs = glGetUniformLocation(m_Program.getGLId(), "uLightDir_vs");
        //uLightPos_vs = glGetUniformLocation(m_Program.getGLId(), "uLightPos_vs");
        uLightIntensity = glGetUniformLocation(m_Program.getGLId(), "uLightIntensity");
    }
};*/
