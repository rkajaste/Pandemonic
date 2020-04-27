#include "Player.hpp"
#include "Physics.hpp"
#include <algorithm>

void Player::update(GLfloat dt) {
    this->coords.y = Physics::calculateHeight(this->coords.y, dt);
    if (this->hasState(MOVING)) {
        this->move(dt);
    } else if (this->hasState(JUMPING)) {
        this->jump(dt);
    }
}

void Player::move(GLfloat dt) {
    this->coords.x += this->speed * dt * this->direction;
}

void Player::jump(GLfloat dt) {
    this->coords.y -= this->jumpForce * dt;
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
        this->states.push_back(JUMPING);
    }
}

GLboolean Player::hasState(PlayerState state) {
    return std::find(this->states.begin(), this->states.end(), state) != this->states.end();
}