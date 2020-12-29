#include "interface.hpp"

GLuint Interface_Load(char* image_path){

    std::unique_ptr<glimac::Image> imgInterface = glimac::loadImage(image_path);
    if(imgInterface == NULL){
        std::cout << "img Interface nulle" << std::endl;
    }

    GLuint imgInterfaceId;
    glGenTextures(1, &imgInterfaceId);
    glBindTexture(GL_TEXTURE_2D, imgInterfaceId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgInterface->getWidth(), imgInterface->getHeight(), 0, GL_RGBA, GL_FLOAT, imgInterface->getPixels());
    glBindTexture(GL_TEXTURE_2D, 0);

    return imgInterfaceId;
}

void afficheInterface(GLuint imgInterfaceId, float x, float y, float z, float width, float height){
    if(imgInterfaceId){
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, imgInterfaceId);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glPushMatrix();
        glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex3f(x-width/2, y+height/2, z);
        glTexCoord2f(0,1);
        glVertex3f(x-width/2, y-height/2, z);
        glTexCoord2f(1,1);
        glVertex3f(x+width/2, y-height/2, z);
        glTexCoord2f(1,0);
        glVertex3f(x+width/2, y+height/2, z);

        glEnd();
        glPopMatrix();
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);
    }else {
        std::cout << "Problème de texture" << std::endl;
    }
}