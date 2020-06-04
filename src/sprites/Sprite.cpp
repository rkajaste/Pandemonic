#include "Sprite.hpp"
#include <iostream>

Sprite::Sprite(glm::vec2 coords, SpriteRenderer *renderer)
{
    this->coords = coords;
    this->renderer = renderer;
    this->rotation = 0.0f;
    this->color = glm::vec3(1.0f);
    this->spriteCoords.x = this->coords.x - this->spriteSize.x / 2 + this->hitboxSize.x / 2;
    this->spriteCoords.y = this->coords.y + this->hitboxSize.y - this->spriteSize.y;
    this->last_coords.x = this->coords.x;
    this->last_coords.y = this->coords.y;
}

Sprite::~Sprite()
{
    delete this->animator;
}

void Sprite::update(GLfloat /*dt*/)
{
    this->addState(FALLING);
    this->checkCollision();
    this->spriteCoords.x = this->coords.x - this->spriteSize.x / 2 + this->hitboxSize.x / 2;
    this->spriteCoords.y = this->coords.y + this->hitboxSize.y - this->spriteSize.y;
    this->last_coords = this->coords;
    this->advanceCooldowns();
}

void Sprite::checkCollision()
{
    for (const auto& terrainObj: MapManager::getTerrainObjects()) {
        glm::vec2 terrainSize(terrainObj->GetWidth(), terrainObj->GetHeight());
        glm::vec2 terrainCoords(terrainObj->GetX(), terrainObj->GetY() - terrainSize.y);
        float terrainTop = terrainCoords.y - terrainSize.y;
        float terrainBottom = terrainCoords.y;
        float terrainLeft = terrainCoords.x;
        float terrainRight = terrainCoords.x + terrainSize.x;
        if (Physics::collides(this->coords, this->hitboxSize, terrainCoords, terrainSize)) {
            if (
                terrainObj->GetProperties().GetStringProperty("blockers") == "t" &&
                this->last_coords.y >= terrainTop
            ) {
                this->coords.y = terrainTop;
                this->addState(GROUNDED);
                this->removeState(FALLING);
            } else if (terrainObj->GetProperties().GetStringProperty("blockers") == "l") {
                this->coords.x = terrainCoords.x;
            } else if (terrainObj->GetProperties().GetStringProperty("blockers") == "r") {
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

void Sprite::addState(Sprite::State state)
{
    this->states.push_back(state);
}

void Sprite::removeState(Sprite::State state)
{
    this->states.erase(std::remove(this->states.begin(), this->states.end(), state), this->states.end());
}

GLboolean Sprite::hasState(Sprite::State state)
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

void Sprite::advanceCooldowns()
{
    for (auto const& timer : this->timers)
    {
        this->timers[timer.first] += 1.0f;
        if (timer.second >= this->cooldowns[timer.first]) {
            this->timers[timer.first] = this->cooldowns[timer.first];
        }
    }
}

void Sprite::setCooldown(std::string action)
{
    this->timers[action] = 0.0f;
}

void Sprite::clearCooldown(std::string action)
{
    this->timers[action] = this->cooldowns[action];
}

GLboolean Sprite::hasCooldown(std::string action)
{
    printf("%s %f %f \n", action.c_str(), this->timers[action], this->cooldowns[action]);
    return this->timers[action] < this->cooldowns[action];
}