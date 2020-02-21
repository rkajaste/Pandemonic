#pragma once
#include <glm/glm.hpp>
#include <SOIL.h>
#include <GL/glew.h>
#include <common/ResourceManager.hpp>
#include <src/SpriteRenderer.hpp>

class Sprite {
    public:
        glm::vec2 coords;
        Texture2D image;
        Sprite(glm::vec2, Texture2D, SpriteRenderer, size = {{255.0f}, {170.0f}});
        void update(GLfloat);
        void draw(GLfloat);
        void setRotation(GLfloat);
        void setColor(glm::vec3);
    private: 
        SpriteRenderer renderer;
        glm::vec3 color;
        GLfloat rotation;
}