#pragma once
#include <glm/glm.hpp>
#include <SOIL.h>
#include <GL/glew.h>
#include <common/ResourceManager.hpp>
#include <src/SpriteRenderer.hpp>

class Sprite {
    public:
        glm::vec2 coords;
        Texture2D texture;
        Sprite(glm::vec2 coords, Texture2D texture, SpriteRenderer* renderer);
        void update(GLfloat);
        void draw();
        void setRotation(GLfloat);
        void setColor(glm::vec3);
        void setSize(glm::vec2);
    private: 
        SpriteRenderer *renderer;
        glm::vec2 size;
        glm::vec3 color;
        GLfloat rotation;
};
