#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "engine/framebuffer/framebuffer.h"

class Framebuffer
{
public:
  Framebuffer(){};
  ~Framebuffer();
  GLuint getTextureID() { return textureID; };
  void create(GLuint, GLuint);
  void rescale(GLuint, GLuint);
  void bind();
  void unbind();

private:
  GLuint FBO;
  GLuint RBO;
  GLuint textureID;
};
