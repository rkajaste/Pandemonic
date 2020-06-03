#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ResourceManager.hpp"
#include "MapManager.hpp"
#include "SpriteRenderer.hpp"
#include "Physics.hpp"
#include "Animator.hpp"

enum SpriteState {
    IDLE, MOVING, JUMPING, FALLING, GROUNDED,
    SWITCHING_STANCE, ATTACK_STANCE, ATTACKING
};

class Sprite {
    public:
        Sprite(glm::vec2 coords, SpriteRenderer* renderer);
        ~Sprite();

        glm::vec2 coords;
        glm::vec2 last_coords;
        void update(GLfloat);
        void draw(GLboolean debug = false);
        void setRotation(GLfloat);
        void setColor(glm::vec3);
        void setSize(glm::vec2);
    protected:
        int direction = 1;
        GLfloat speed = 1000.0f;
        GLfloat jumpForce = 1100.0f;
        GLfloat gravityForce = 0.0f;

        std::vector<SpriteState> states;
        std::string textureName;
        glm::vec2 spriteCoords;
        glm::vec2 spriteSize;
        glm::vec2 hitboxSize;
        glm::vec3 color;
        GLfloat rotation;
        SpriteRenderer *renderer;
        Animator *animator;

        void enableGravity(GLfloat dt);
        void clearStates();
        void addState(SpriteState);
        void removeState(SpriteState);
        GLboolean hasState(SpriteState);

        void jump();
        void move(GLfloat dt);
    private:
        void checkCollision();
};
