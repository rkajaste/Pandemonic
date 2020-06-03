#include "Player.hpp"

void Player::update(GLfloat dt) {
    this->enableGravity(dt);
    this->handleIdling();
    this->handleMoving(dt);
    this->handleJumping();
    this->handleStanceSwitching();
    this->handleAttacking();

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
    
    if (keys[GLFW_KEY_X] && !this->hasState(SWITCHING_STANCE) && !this->hasState(ATTACKING)) {
        if (this->hasState(ATTACK_STANCE)) {
            this->removeState(IDLE);
            this->addState(SWITCHING_STANCE);
            this->removeState(ATTACK_STANCE);
        } else {
            this->removeState(IDLE);
            this->addState(SWITCHING_STANCE);
            this->addState(ATTACK_STANCE);
        }
    }

    if (keys[GLFW_KEY_SPACE] && this->hasState(ATTACK_STANCE)) {
        this->removeState(IDLE);
        this->addState(ATTACKING);
    }
}

void Player::handleIdling()
{
    if (this->hasState(IDLE)) {
        this->textureName = "player_idle";

        if(this->hasState(ATTACK_STANCE)) {
            this->textureName = "player_idle_attack_stance";
        }
    }
}

void Player::handleMoving(GLfloat dt)
{
    if (this->hasState(MOVING)) {
        this->move(dt);
        this->textureName = "player_run";
        if(this->hasState(ATTACK_STANCE)) {
            this->textureName = "player_run_attack_stance";
        }
    }
}

void Player::handleJumping()
{
    if (this->hasState(JUMPING)) {
        this->jump();
    }
}


void Player::handleStanceSwitching()
{
    if (this->hasState(SWITCHING_STANCE)) {
        if (this->hasState(ATTACK_STANCE)) {
            this->textureName = "player_unsheathe";

            if (
                this->animator->hasAnimationFinished(this->textureName)
            ) {
                this->removeState(SWITCHING_STANCE);
                this->addState(ATTACK_STANCE);
                this->addState(IDLE);
            }
        } else {
            this->textureName = "player_sheathe";

            if (
                this->animator->hasAnimationFinished(this->textureName)
            ) {
                this->removeState(SWITCHING_STANCE);
                this->removeState(ATTACK_STANCE);
                this->addState(IDLE);
            }
        }
    }
}

void Player::handleAttacking()
{
    if (this->hasState(ATTACK_STANCE) && this->hasState(ATTACKING)) {
        this->textureName = "player_attack";
        if (this->animator->hasAnimationFinished(this->textureName)) {
            this->removeState(ATTACKING);
            this->addState(IDLE);
        }
    }
}
