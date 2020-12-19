#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/glm.hpp>
#include "glimac/Image.hpp"
#include "glimac/FreeflyCamera.hpp"

#include "model.hpp"

using namespace glimac;

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(800, 600, "GLImac");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    FilePath applicationPath(argv[0]);
    Program ObjProgram = (loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/normal.fs.glsl"));
    ObjProgram.use();

    GLint uMVPMatrix = glGetUniformLocation(ObjProgram.getGLId(), "uMVPMatrix");
    GLint uMVMatrix = glGetUniformLocation(ObjProgram.getGLId(), "uMVMatrix");
    GLint uNormalMatrix = glGetUniformLocation(ObjProgram.getGLId(), "uNormalMatrix");
    //GLint uObjTexture = glGetUniformLocation(ObjProgram.getGLId(), "uTexture");

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    glEnable(GL_DEPTH_TEST);

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    // Initialisation objet
    std::string fileCube = "/home/loona/Bureau/Projet/GLImac-Template/assets/models/cube.obj";
    Model cube(fileCube);

    // Déclaration de matrices
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), 800.0f/600.0f, 0.1f, 100.f);
    glm::mat4 MVMatrix = glm::translate(glm::mat4(1.f) , glm::vec3(0., 0. , -5.));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
    glm::mat4 MVPMatrix = ProjMatrix*MVMatrix;

    //récupération des positions de la souris
    glm::ivec2 mousePos = windowManager.getMousePosition();

    //création de la trackballCamera
    FreeflyCamera camera;
    glm::mat4 ViewMatrix;

    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
            if(windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT)==true){
                camera.rotateLeft((windowManager.getMousePosition().y - mousePos.y)/100);
                camera.rotateUp((windowManager.getMousePosition().x - mousePos.x)/100);
            }
        }

        mousePos = windowManager.getMousePosition();

        if(windowManager.isKeyPressed(SDLK_d)==true){
            camera.moveLeft(-0.5);
        }
        if(windowManager.isKeyPressed(SDLK_q)==true){
            camera.moveLeft(0.5);
        }
        if(windowManager.isKeyPressed(SDLK_z)==true){
            camera.moveFront(0.5);
        }
        if(windowManager.isKeyPressed(SDLK_s)==true){
            camera.moveFront(-0.5);
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        // couleur de    fond
        glClearColor(0.2, 0.3, 0.3 ,1);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ViewMatrix = camera.getViewMatrix() ;

        MVMatrix = glm::mat4(1.f) * ViewMatrix;

        // Rotation de la Terre
        NormalMatrix = glm::transpose(glm::inverse(MVMatrix)); 
        MVPMatrix = ProjMatrix*MVMatrix;

        glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(MVPMatrix));

        cube.Draw(ObjProgram);

        // Update the display
        windowManager.swapBuffers();

        //SDL_Delay(60);
    }

    return EXIT_SUCCESS;
}
