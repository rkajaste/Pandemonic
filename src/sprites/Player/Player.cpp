#include "Player.hpp"

Player::Player(glm::vec2 coords, SpriteRenderer* renderer) : Sprite{coords, renderer} {
    this->hitboxSize = glm::vec2(32.0f, 128.0f);
    this->spriteSize = glm::vec2(255.0f, 170.0f);
    this->animator = new Animator(this->spriteSize);
    this->respawnCoords = coords;
    this->health = 100;
    this->maxHealth = 100;
    this->mana = 30;
    this->maxMana = 30;
    this->speed = 600.0f;
    this->jumpForce = 1100.0f;

    Cooldowns cooldowns = {
        {
            "attack", 
            {
                { "timer", 0.0f },
                { "cooldown", 30.0f}
            }
        },
        {
            "aerial_slash",
            {
                { "timer", 0.0f },
                { "cooldown", 200.0f }
            }
        }
    };
    this->cooldownManager = new CooldownManager(cooldowns);
}

void Player::update(GLfloat dt) {
    this->enableGravity(dt);
    this->handleIdling();
    if (this->hasState(GROUNDED)) {
        this->cooldownManager->clearCooldown("aerial_slash");
    } else {
        if (this->hasState(FALLING)){
            if (this->gravityForce > 0) {
                this->textureName = "player_fall";
                if (this->hasState(ATTACK_STANCE)) {
                    this->textureName = "player_unsheathed_fall";
                }
            } else {
                this->textureName = "player_jump";
                if (this->hasState(ATTACK_STANCE)) {
                    this->textureName = "player_unsheathed_jump";
                }
            }
        }
    }
    if(!this->hasState(AERIAL_ATTACKING)) {
        this->handleMoving(dt);
    }
    this->handleJumping();
    this->handleStanceSwitching();
    this->handleAttacking();
    this->checkMapObjectsCollisions();

    Sprite::update(dt);
    if (this->health <= 0) {
        this->die();
    }
}

void Player::checkMapObjectsCollisions() {
    for (const auto& interactionObj: MapManager::getInteractionObjects()) {
        glm::vec2 objSize(interactionObj->GetWidth(), interactionObj->GetHeight());
        glm::vec2 objCoords(interactionObj->GetX(), interactionObj->GetY());

        if (Physics::collides(this->coords, this->hitboxSize, objCoords, objSize)) {
            // do something
        }
    }
    for (const auto& levelTransitionObject: MapManager::getLevelTransitionObjects()) {
        glm::vec2 objSize(levelTransitionObject->GetWidth(), levelTransitionObject->GetHeight());
        glm::vec2 objCoords(levelTransitionObject->GetX(), levelTransitionObject->GetY());

        if (Physics::collides(this->coords, this->hitboxSize, objCoords, objSize)) {
            const std::string levelTransition = levelTransitionObject->GetProperties().GetStringProperty("level_transition");
            const std::string playerSpawn = levelTransitionObject->GetProperties().GetStringProperty("player_spawn");
            MapManager::loadMap(levelTransition);
            this->coords = MapManager::getPlayerSpawnPoint(playerSpawn);
            this->respawnCoords = this->coords;
        }
    }
}

void Player::handleInput(GLboolean keys[2048]) {

    if(keys[GLFW_KEY_RIGHT] && !this->hasState(AERIAL_ATTACKING)) {
        this->direction = 1;
        this->removeState(IDLE);
        this->addState(MOVING);
    } else if (keys[GLFW_KEY_LEFT] && !this->hasState(AERIAL_ATTACKING)) {
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
        if (!this->hasState(JUMPING) && !this->hasState(FALLING)) {
            if (!this->cooldownManager->hasCooldown("attack")) {
                this->removeState(IDLE);
                this->addState(ATTACKING);
            }
        } else {
            if (!this->cooldownManager->hasCooldown("aerial_slash")) {
                this->removeState(IDLE);
                this->addState(AERIAL_ATTACKING);
            }
        }
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
        if(this->hasState(GROUNDED)) {
            this->textureName = "player_run";
            if(this->hasState(ATTACK_STANCE)) {
                this->textureName = "player_run_attack_stance";
            }
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
    if (this->hasState(ATTACK_STANCE)) {
        if (this->hasState(ATTACKING)) {
            this->textureName = "player_attack";
            if (this->animator->hasAnimationFinished(this->textureName) || !this->hasState(GROUNDED)) {
                this->removeState(ATTACKING);
                this->addState(IDLE);
                this->cooldownManager->setCooldown("attack");
            }
        } else if (this->hasState(AERIAL_ATTACKING)) {
            this->textureName = "player_aerial_slash";
            this->gravityForce = -60;
            if (this->animator->hasAnimationFinished(this->textureName)) {
                this->removeState(AERIAL_ATTACKING);
                this->addState(IDLE);
                this->cooldownManager->setCooldown("aerial_slash");
            }
        }
    }
}

void Player::die()
{
    this->coords = this->respawnCoords;
    this->health = this->maxHealth;
}