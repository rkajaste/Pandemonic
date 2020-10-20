#include "Sprite.hpp"
#include <iostream>

Sprite::Sprite(glm::vec2 coords, SpriteRenderer* renderer)
{
    this->coords = coords;
    this->renderer = renderer;
    this->spriteCoords.x = this->coords.x - this->spriteSize.x / 2 + this->hitboxSize.x / 2;
    this->spriteCoords.y = this->coords.y + this->hitboxSize.y - this->spriteSize.y;
    this->last_coords.x = this->coords.x;
    this->last_coords.y = this->coords.y;
}

Sprite::~Sprite()
{
    delete this->cooldownManager;
    delete this->animator;
}

void Sprite::update(GLfloat /*dt*/)
{
    this->addState(FALLING);
    this->checkCollision();
    this->spriteCoords.x = this->coords.x - this->spriteSize.x / 2 + this->hitboxSize.x / 2;
    this->spriteCoords.y = this->coords.y + this->hitboxSize.y - this->spriteSize.y;
    this->last_coords = this->coords;
    if (this->cooldownManager != NULL) {
        this->cooldownManager->advanceCooldowns();
    }
}

void Sprite::handleCollision(const Tmx::Object* obj) {
    glm::vec2 objSize(obj->GetWidth(), obj->GetHeight());
    glm::vec2 objCoords(obj->GetX(), obj->GetY());
    float objTop = objCoords.y - objSize.y * 2;
    float objBottom = objCoords.y - objSize.y;
    float objLeft = objCoords.x;
    float objRight = objCoords.x + objSize.x;

    if (Physics::collides(this->coords, this->hitboxSize, objCoords, objSize)) {
        if (obj->GetName() == "blockers") {
            std::string blockersProp = obj->GetProperties().GetStringProperty("blockers");
            if (
                blockersProp.find("t") != std::string::npos &&
                this->last_coords.y <= objTop
            ) {
                this->coords.y = objTop;
                this->addState(GROUNDED);
                this->removeState(FALLING);
            } 
            if (
                blockersProp.find("b") != std::string::npos &&
                this->last_coords.y - this->hitboxSize.y >= objBottom
            ) {
                this->coords.y = objBottom + this->hitboxSize.y;
                this->gravityForce = 0.0f;
            } 
            if (blockersProp.find("l") != std::string::npos &&
                this->last_coords.x + this->hitboxSize.x <= objLeft) {
                this->coords.x = objCoords.x - this->hitboxSize.x;
            }
            if (blockersProp.find("r") != std::string::npos &&
                this->last_coords.x >= objRight) {
                this->coords.x = objCoords.x + objSize.x;
            }
        }

        if (obj->GetName() == "death") {
            if (
                obj->GetProperties().GetIntProperty("damage") == -1
            ) {
                if (obj->GetType() == "water" && this->last_coords.y - this->hitboxSize.y >= objTop) {
                    this->health = 0;
                }
            }
        }

    }
}

void Sprite::checkCollision()
{
    for (const auto& obj: MapManager::getTerrainObjects()) {
        this->handleCollision(obj);
    }
    for (const auto& obj: MapManager::getDeathObjects()) {
        this->handleCollision(obj);
    }
}

void Sprite::die(){}

void Sprite::draw(GLboolean debug)
{
    this->renderer->drawSprite(
        this->animator,
        this->textureName,
        this->spriteCoords,
        this->spriteSize,
        this->direction == -1 ? true : false,
        this->rotation,
        this->color
    );
    if (debug) {
        this->renderer->debug(this->coords, this->hitboxSize);
    }
}

void Sprite::setRotation(GLfloat degrees)
{
    this->rotation = degrees;
}

void Sprite::setSize(glm::vec2 size)
{
    this->spriteSize = size;
}

void Sprite::enableGravity(GLfloat dt)
{
    if (this->hasState(FALLING)) {
        this->gravityForce = Physics::calculateGravity(this->gravityForce, dt);
    }
    
    if (this->hasState(GROUNDED) && !this->hasState(JUMPING) && !this->hasState(FALLING)) {
        this->gravityForce = 0;
    }

    this->coords.y += this->gravityForce * dt; 
}

void Sprite::clearStates()
{
    this->states.clear();
}

void Sprite::addState(SpriteState state)
{
    this->states.push_back(state);
}

void Sprite::removeState(SpriteState state)
{
    if (this->hasState(state)) {
        this->states.erase(std::remove(this->states.begin(), this->states.end(), state), this->states.end());
    }
}

GLboolean Sprite::hasState(SpriteState state)
{
    return Util::existsInVector(state, this->states);
}

void Sprite::jump()
{
    this->gravityForce = -this->jumpForce;
    this->removeState(JUMPING);
    this->removeState(GROUNDED);
}

void Sprite::move(GLfloat dt) {
    this->coords.x += glm::round(this->speed * dt * this->direction);
}
