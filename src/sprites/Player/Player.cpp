#include "Player.hpp"


void Player::update(GLfloat dt) {
    this->coords.y = Physics::calculateHeight(this->coords.y, dt);
    if (Util::existsInVector(MOVING, this->states)) {
        this->move(dt);
    }
    if (Util::existsInVector(JUMPING, this->states)) {
        this->jump(dt);
    }
    Sprite::update(dt);
}

void Player::move(GLfloat dt) {
    this->coords.x += this->speed * dt * this->direction;
}

void Player::jump(GLfloat dt) {
    this->coords.y -= this->jumpForce * dt; // * this->noClipDirection;
}

void Player::handleInput(GLboolean keys[2048]) {
    this->states.clear();
    this->states.push_back(IDLE);

    if(keys[GLFW_KEY_RIGHT]) {
        this->direction = 1;
        this->states.push_back(MOVING);
    } else if (keys[GLFW_KEY_LEFT]) {
        this->direction = -1;
        this->states.push_back(MOVING);
    }

    if (keys[GLFW_KEY_UP]) {
        this->noClipDirection = 1;
        this->states.push_back(JUMPING);
    }

    // if (keys[GLFW_KEY_DOWN]) {
    //     this->noClipDirection = -1;
    //     this->states.push_back(JUMPING);
    // }
}
