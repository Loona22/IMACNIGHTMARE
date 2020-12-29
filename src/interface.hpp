#include <GL/glew.h>
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <GL/gl.h>
#include <GL/glu.h>

GLuint Interface_Load(char* image_path);

void afficheInterface(GLuint Img_id, float x, float y, float z, float width, float height);