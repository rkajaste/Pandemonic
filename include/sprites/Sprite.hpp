#pragma once
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "ResourceManager.hpp"
#include "MapManager.hpp"
#include "SpriteRenderer.hpp"
#include "Physics.hpp"
#include "Animator.hpp"

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
        enum State {
            IDLE, MOVING, JUMPING, FALLING, GROUNDED,
            SWITCHING_STANCE, ATTACK_STANCE,
            ATTACKING, AERIAL_ATTACKING
        };

        SpriteRenderer *renderer;
        Animator *animator;

        int direction = 1;
        GLfloat speed = 1000.0f;
        GLfloat jumpForce = 1100.0f;
        GLfloat gravityForce = 0.0f;

        std::vector<Sprite::State> states;
        std::string textureName;
        glm::vec2 spriteCoords;
        glm::vec2 spriteSize;
        glm::vec2 hitboxSize;
        glm::vec3 color;
        GLfloat rotation;

        std::map<std::string, GLfloat> cooldowns;
        std::map<std::string, GLfloat> timers;

        void enableGravity(GLfloat dt);
        void clearStates();
        void addState(Sprite::State);
        void removeState(Sprite::State);
        void jump();
        void move(GLfloat dt);

        void advanceCooldowns();
        void setCooldown(std::string action);
        void clearCooldown(std::string action);
        GLboolean hasCooldown(std::string action);

        GLboolean hasState(Sprite::State);
    private:
        void checkCollision();
};
