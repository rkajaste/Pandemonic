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

void Sprite::checkCollision()
{
    for (const auto& terrainObj: MapManager::getTerrainObjects()) {
        glm::vec2 terrainSize(terrainObj->GetWidth(), terrainObj->GetHeight());
        glm::vec2 terrainCoords(terrainObj->GetX(), terrainObj->GetY());
        float terrainTop = terrainCoords.y - terrainSize.y * 2;
        float terrainBottom = terrainCoords.y - terrainSize.y;
        float terrainLeft = terrainCoords.x;
        float terrainRight = terrainCoords.x + terrainSize.x;
        if (terrainObj->GetProperties().GetStringProperty("blockers").find("t") != std::string::npos) {
            printf("%02f, %02f\n", this->last_coords.y + this->hitboxSize.y, terrainTop);
        }
        if (Physics::collides(this->coords, this->hitboxSize, terrainCoords, terrainSize)) {
            if (
                terrainObj->GetProperties().GetStringProperty("blockers").find("t") != std::string::npos &&
                this->last_coords.y <= terrainTop
            ) {
                this->coords.y = terrainTop;
                this->addState(GROUNDED);
                this->removeState(FALLING);
            } 
            if (
                terrainObj->GetProperties().GetStringProperty("blockers").find("b") != std::string::npos &&
                this->last_coords.y - this->hitboxSize.y >= terrainBottom
            ) {
                this->coords.y = terrainBottom + this->hitboxSize.y;
                this->gravityForce = 0.0f;
            } 
            if (terrainObj->GetProperties().GetStringProperty("blockers").find("l") != std::string::npos &&
               this->last_coords.x + this->hitboxSize.x <= terrainLeft) {
                this->coords.x = terrainCoords.x - this->hitboxSize.x;
            }
            if (terrainObj->GetProperties().GetStringProperty("blockers").find("r") != std::string::npos &&
                this->last_coords.x >= terrainRight) {
                this->coords.x = terrainCoords.x + terrainSize.x;
            }
        }
    }
}

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
