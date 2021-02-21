#pragma once
#include <vector>
#include <map>

#include "Sprite.hpp"
#include "Util.hpp"
#include "Physics.hpp"
#include "store/Store.hpp"


class Player: public Sprite {
    public:
        Player(glm::vec2 coords, SpriteRenderer* renderer);
        glm::vec2 respawnCoords;
        void update(GLfloat);
        void handleInput(GLboolean keys[2048]);

    private:
        GLint mana;
        GLint maxMana;

        void handleIdling();
        void handleMoving(GLfloat dt);
        void handleJumping();
        void handleStanceSwitching();
        void handleAttacking();
        void checkMapObjectsCollisions();
        void die();
        void takeDamage(GLint damage);
        void updateStore();
};
