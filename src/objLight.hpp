#ifndef OBJLIGHT_HPP
#define OBJLIGHT_HPP

#include <GL/glew.h>
#include <iostream> 
#include <string>
#include <vector>

#include <glimac/glm.hpp>
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>

struct ObjLightProgram {
    glimac::Program objLight_Program;

    //float vertices[] ;

    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uTexture;

    GLint uMaterialAmbient;
    GLint uMaterialDiffuse;
    GLint uMaterialSpecular;
    GLint uMaterialShininess;

    GLint uLightAmbient;
    GLint uLightDiffuse;
    GLint uLightSpecular;
    GLint uLightPosition;

    GLint uViewPos;

    ObjLightProgram(const glimac::FilePath& applicationPath):
        objLight_Program(loadProgram(applicationPath.dirPath() + "shaders/lightShader.vs.glsl",
                              applicationPath.dirPath() + "shaders/lightShader.fs.glsl")) {
        uViewPos = glGetUniformLocation(objLight_Program.getGLId(), "viewPos");

        uMaterialAmbient = glGetUniformLocation(objLight_Program.getGLId(), "material.ambient"); 
        uMaterialDiffuse = glGetUniformLocation(objLight_Program.getGLId(), "material.diffuse"); 
        uMaterialSpecular = glGetUniformLocation(objLight_Program.getGLId(), "material.specular"); 
        uMaterialShininess = glGetUniformLocation(objLight_Program.getGLId(), "material.shininess"); 

        uLightAmbient = glGetUniformLocation(objLight_Program.getGLId(), "light.ambient"); 
        uLightDiffuse = glGetUniformLocation(objLight_Program.getGLId(), "light.diffuse"); 
        uLightSpecular = glGetUniformLocation(objLight_Program.getGLId(), "light.specular"); 
        uLightPosition = glGetUniformLocation(objLight_Program.getGLId(), "light.position"); 
    }
};

void loadObjLight();

#endif