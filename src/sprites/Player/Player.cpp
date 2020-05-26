#include "Player.hpp"


void Player::update(GLfloat dt) {
    this->enableGravity(dt);
    if (this->hasState(MOVING)) {
        this->move(dt);
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
