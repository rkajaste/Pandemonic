#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ResourceManager.hpp"
#include "MapManager.hpp"
#include "SpriteRenderer.hpp"
#include "Physics.hpp"

enum SpriteState { IDLE, MOVING, JUMPING, FALLING, ATTACKING, GROUNDED };

class Sprite {
    public:
        Sprite(glm::vec2 coords, Texture2D texture, SpriteRenderer* renderer);
        ~Sprite(){};

        glm::vec2 coords;
        glm::vec2 last_coords;
        void update(GLfloat);
        void draw(GLboolean debug = false);
        void setRotation(GLfloat);
        void setColor(glm::vec3);
        void setSize(glm::vec2);
    protected:
        std::vector<SpriteState> states;
        int direction = 1;
        Texture2D texture;
        glm::vec2 spriteCoords;
        glm::vec2 spriteSize;
        glm::vec2 hitboxSize;
        glm::vec3 color;
        GLfloat rotation;
        GLfloat speed = 1100.0f;
        GLfloat jumpForce = 40.0f;
        GLfloat gravityForce = 0.0f;

        void enableGravity(GLfloat dt);
        void clearStates();
        void addState(SpriteState);
        void removeState(SpriteState);
        GLboolean hasState(SpriteState);

        void jump();
        void move(GLfloat dt);
    private:
        SpriteRenderer *renderer;
        void checkCollision();
};
