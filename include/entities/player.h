#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <map>
#include "entity.h"

class Player : public Entity
{
public:
    Player(glm::vec2 coords, SpriteRenderer *renderer);
    glm::vec2 respawnCoords;
    void update(GLfloat);
    void handleInput(std::map<UserInput, GLboolean> keys);

private:
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
