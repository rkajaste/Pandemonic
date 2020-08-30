#pragma once
#include <vector>
#include <map>

#include "Sprite.hpp"
#include "Util.hpp"
#include "Physics.hpp"


class Player: public Sprite {
    public:
        Player(glm::vec2 coords, SpriteRenderer* renderer);

        void update(GLfloat);
        void handleInput(GLboolean keys[2048]);

    private:
        void handleIdling();
        void handleMoving(GLfloat dt);
        void handleJumping();
        void handleStanceSwitching();
        void handleAttacking();
};
