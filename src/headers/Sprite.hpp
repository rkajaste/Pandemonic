#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ResourceManager.hpp"
#include "MapManager.hpp"
#include "SpriteRenderer.hpp"

class Sprite {
    public:
        int direction = 1;
        glm::vec2 coords;
        Texture2D texture;
        Sprite(glm::vec2 coords, Texture2D texture, SpriteRenderer* renderer);
        ~Sprite(){};
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
