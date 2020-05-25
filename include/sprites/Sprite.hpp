#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ResourceManager.hpp"
#include "MapManager.hpp"
#include "SpriteRenderer.hpp"
#include "Physics.hpp"

class Sprite {
    public:
        Sprite(glm::vec2 coords, Texture2D texture, SpriteRenderer* renderer);
        ~Sprite(){};

        glm::vec2 coords;
        void update(GLfloat);
        void draw(GLboolean debug = false);
        void setRotation(GLfloat);
        void setColor(glm::vec3);
        void setSize(glm::vec2);
    protected:
        int direction = 1;
        Texture2D texture;
        glm::vec2 spriteCoords;
        glm::vec2 spriteSize;
        glm::vec2 hitboxSize;
        glm::vec3 color;
        GLfloat rotation;
    private:
        SpriteRenderer *renderer;

};
