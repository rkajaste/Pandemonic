#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <vector>
#include <map>
#include "entity.h"
#include "util.h"
#include "physics.h"
#include "store/player_store.h"
#include "store/dialog_store.h"
#include "store/map_store.h"

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
