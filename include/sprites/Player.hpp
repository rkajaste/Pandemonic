#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <vector>
#include <map>
#include "Sprite.hpp"
#include "Util.hpp"
#include "Physics.hpp"
#include "store/PlayerStore.hpp"
#include "store/DialogStore.hpp"
#include "store/MapStore.hpp"

class Player : public Sprite
{
public:
    Player(glm::vec2 coords, SpriteRenderer *renderer);
    glm::vec2 respawnCoords;
    void update(GLfloat);
    void handleInput(std::map<UserInput, GLboolean> keys);

private:
    GLint mana;
    GLint maxMana;
    std::string collidedEntrance;

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
