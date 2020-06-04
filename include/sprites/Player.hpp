#pragma once
#include "Sprite.hpp"
#include "Util.hpp"
#include "Physics.hpp"
#include <vector>
#include <map>

class Player: public Sprite {
    public:
        Player(glm::vec2 coords, SpriteRenderer* renderer)
            : Sprite{coords, renderer}
        {
            this->hitboxSize = glm::vec2(32.0f, 128.0f);
            this->spriteSize = glm::vec2(255.0f, 170.0f);
            this->animator = new Animator(this->spriteSize);

            this->speed = 1000.0f;
            this->jumpForce = 1100.0f;

            this->cooldowns = {
                {"attack", 30.0f},
                {"aerial_slash", 200.0f}
            };
            this->timers = {
                {"attack", 0.0f},
                {"aerial_slash", 0.0f}
            };
        } 

        void update(GLfloat);
        void handleInput(GLboolean keys[2048]);

    private:
        void handleIdling();
        void handleMoving(GLfloat dt);
        void handleJumping();
        void handleStanceSwitching();
        void handleAttacking();
};
