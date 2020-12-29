#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include "glimac/Image.hpp"

using namespace glimac;

struct ObjetProgram {
    Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;

    GLint uLightDir;
    GLint uLightAmbient;
    GLint uLightDiffuse;
    GLint uLightSpecular;

    GLint uMatSpecular;
    GLint uMatShininess;
    GLint uMatDiffuse;

    GLint uViewPos;

    ObjetProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/lightShader.vs.glsl",
                              applicationPath.dirPath() + "shaders/lightShaderDir.fs.glsl")){
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");

        uLightDir = glGetUniformLocation(m_Program.getGLId(), "light.direction");
        uLightAmbient = glGetUniformLocation(m_Program.getGLId(), "light.ambient");
        uLightDiffuse = glGetUniformLocation(m_Program.getGLId(), "light.diffuse");
        uLightSpecular = glGetUniformLocation(m_Program.getGLId(), "light.specular");

        uMatSpecular = glGetUniformLocation(m_Program.getGLId(), "material.specular");
        uMatShininess = glGetUniformLocation(m_Program.getGLId(), "material.shininess");
        uMatDiffuse = glGetUniformLocation(m_Program.getGLId(), "material.diffuse");

        uViewPos = glGetUniformLocation(m_Program.getGLId(), "viewPos");
        }
};

struct LightProgram {
    Program m_Program;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;

    LightProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/lightObjShader.vs.glsl",
                              applicationPath.dirPath() + "shaders/lightObjShader.fs.glsl")){
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        }
};