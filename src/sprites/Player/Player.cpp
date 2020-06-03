#include "Player.hpp"

void Player::update(GLfloat dt) {
    this->enableGravity(dt);
    this->textureName = "player_idle";
    if (this->hasState(MOVING)) {
        this->move(dt);
        this->textureName = "player_run";
    }
    if (this->hasState(JUMPING)) {
        this->jump();
    }
    Sprite::update(dt);
}

void Player::handleInput(GLboolean keys[2048]) {
    
    if(keys[GLFW_KEY_RIGHT]) {
        this->direction = 1;
        this->removeState(IDLE);
        this->addState(MOVING);
    } else if (keys[GLFW_KEY_LEFT]) {
        this->direction = -1;
        this->removeState(IDLE);
        this->addState(MOVING);
    }

    if(!keys[GLFW_KEY_RIGHT] && !keys[GLFW_KEY_LEFT]) {
        this->removeState(MOVING);
        this->addState(IDLE);
    }

    if (keys[GLFW_KEY_UP] && this->hasState(GROUNDED)) {
        this->addState(JUMPING);
    }
}
