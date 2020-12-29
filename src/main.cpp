#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/glm.hpp>
#include "glimac/Image.hpp"
#include "glimac/FreeflyCamera.hpp"

#include "structures.hpp"
#include "model.hpp"
#include "interface.hpp"

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

    LightProgram LightProgram(applicationPath);

    ObjetProgram ObjProgram(applicationPath);

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    glEnable(GL_DEPTH_TEST);

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    // Initilisation de l'interface

    GLuint interface_titre = Interface_Load("/home/loona/Bureau/Projet/GLImac-Template/assets/interface/barre_titre.png");
    std::cout << "interface_titre " << interface_titre << std::endl;

    // Initialisation objet
    std::string fileCube = "/home/loona/Bureau/Projet/GLImac-Template/assets/models/cubeSponge/cubeSponge.obj";
    Model cube(fileCube);

    std::string fileLightCube = "/home/loona/Bureau/Projet/GLImac-Template/assets/models/cube.obj";
    Model lightCube(fileLightCube);

    // Déclaration de matrices
    glm::mat4 globalMVMatrix;
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), 800.0f/800.0f, 0.1f, 100.f);
    glm::mat4 MVMatrix = glm::translate(glm::mat4(1.f) , glm::vec3(0., 0. , -5.));
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
    glm::mat4 MVPMatrix = ProjMatrix*MVMatrix;

    glm::mat4 lightMVMatrix = glm::translate(glm::mat4(1.f) , glm::vec3(0., 0. , -5.));
    glm::mat4 lightNormalMatrix = glm::transpose(glm::inverse(lightMVMatrix));
    glm::mat4 lightMVPMatrix = ProjMatrix*lightMVMatrix;

    //récupération des positions de la souris
    glm::ivec2 mousePos = windowManager.getMousePosition();

    //création de la trackballCamera
    FreeflyCamera camera;
    glm::mat4 ViewMatrix;

    /***********
    Initilisation musique
    **********/
    /*
    Mix_Music *musique;
    musique = Mix_LoadMUS("../GLImac-Template/assets/musique/son.mp3");
    if(musique == NULL){
        std::cout << "Probleme deee chargement musique" << std::endl;
        return false;
    }
    Mix_PlayMusic(musique, -1);
    */

    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
        }

        mousePos = windowManager.getMousePosition();

        if(windowManager.isKeyPressed(SDLK_d)==true){
            camera.moveLeft(-0.05);
        }
        if(windowManager.isKeyPressed(SDLK_q)==true){
            camera.moveLeft(0.05);
        }
        if(windowManager.isKeyPressed(SDLK_z)==true){
            camera.moveFront(0.05);
        }
        if(windowManager.isKeyPressed(SDLK_s)==true){
            camera.moveFront(-0.05);
        }

        if(windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT)==true){
            camera.rotateLeft((windowManager.getMousePosition().y - mousePos.y)/100);
            camera.rotateUp((windowManager.getMousePosition().x - mousePos.x)/100);
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/

        // couleur de fond
        glClearColor(0.5, 0.5, 0.5, 0.);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ViewMatrix = camera.getViewMatrix() ;
        globalMVMatrix = glm::mat4(1.f) * ViewMatrix;

        MVMatrix = glm::mat4(1.f) * ViewMatrix;
        NormalMatrix = glm::transpose(glm::inverse(MVMatrix)); 
        MVPMatrix = ProjMatrix*MVMatrix;

        ObjProgram.m_Program.use();

        // lumières
        glm::vec4 lightDir(1., 1., 1., 0.);
        lightDir = lightDir * ViewMatrix;
        glUniform3f(ObjProgram.uLightDir, lightDir.x, lightDir.y, lightDir.z);
        glUniform3f(ObjProgram.uViewPos, camera.getPosCamera().x, camera.getPosCamera().y, camera.getPosCamera().z);

        glUniform3f(ObjProgram.uLightAmbient, 0.2, 0.2, 0.2);
        glUniform3f(ObjProgram.uLightDiffuse, 0.5, 0.5, 0.5);
        glUniform3f(ObjProgram.uLightSpecular, 1., 1., 1.);

        glUniform3f(ObjProgram.uMatSpecular, 0.5, 0.5, 0.5);
        glUniform1f(ObjProgram.uMatShininess, 32.);

        glUniformMatrix4fv(ObjProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(ObjProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
        glUniformMatrix4fv(ObjProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(MVPMatrix));

        cube.Draw(ObjProgram.m_Program);
/*
        LightProgram.m_Program.use();
        lightMVMatrix = glm::translate(globalMVMatrix, glm::vec3(lightPos.x, lightPos.y, lightPos.z));
        //lightMVMatrix = glm::rotate(lightMVMatrix, glm::radians(windowManager.getTime()*100), glm::vec3(0., 2., 0.)); // Translation * Rotation
        lightNormalMatrix = glm::transpose(glm::inverse(lightMVMatrix)); 
        lightMVPMatrix = ProjMatrix*lightMVMatrix;

        glUniformMatrix4fv(LightProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(lightMVMatrix));
        glUniformMatrix4fv(LightProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(lightNormalMatrix));
        glUniformMatrix4fv(LightProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(lightMVPMatrix));

       lightCube.Draw(LightProgram.m_Program);
*/
        // Update the display
        windowManager.swapBuffers();

        //SDL_Delay(60);
    }

    //Mix_FreeMusic(musique);
    //Mix_CloseAudio();

    return EXIT_SUCCESS;
}
