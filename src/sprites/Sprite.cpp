#include "Sprite.hpp"
#include <iostream>

Sprite::Sprite(glm::vec2 coords, Texture2D texture, SpriteRenderer *renderer) {
    this->coords = coords;
    this->texture = texture;
    this->renderer = renderer;
    this->spriteSize = glm::vec2(texture.Width, texture.Height);
    this->hitboxSize = glm::vec2(64.0f, 128.0f);
    this->rotation = 0.0f;
    this->color = glm::vec3(1.0f);
    this->spriteCoords.x = this->coords.x - this->spriteSize.x / 2 + this->hitboxSize.x / 2;
    this->spriteCoords.y = this->coords.y + this->hitboxSize.y - this->spriteSize.y;
}

void Sprite::update(GLfloat /*dt*/) {
    this->spriteCoords.x = this->coords.x - this->spriteSize.x / 2 + this->hitboxSize.x / 2;
    this->spriteCoords.y = this->coords.y + this->hitboxSize.y - this->spriteSize.y;
    for (const auto& terrainObj :MapManager::getTerrainObjects()) {
        glm::vec2 terrainSize(terrainObj->GetWidth(), terrainObj->GetHeight());
        glm::vec2 terrainCoords(terrainObj->GetX(), terrainObj->GetY() - terrainSize.y);
        if (Physics::collides(this->coords, this->hitboxSize, terrainCoords, terrainSize)) {
            if (terrainObj->GetProperties().GetStringProperty("blockers") == "t") {
                this->coords.y = terrainCoords.y - terrainSize.y;
            } else if (terrainObj->GetProperties().GetStringProperty("blockers") == "l") {
                this->coords.x = terrainCoords.x;
            } else if (terrainObj->GetProperties().GetStringProperty("blockers") == "r") {
                this->coords.x = terrainCoords.x + terrainSize.x;
            }
        }
    }
}

void Sprite::draw(GLboolean debug) {
    this->renderer->drawSprite(
        this->texture,
        this->spriteCoords,
        this->spriteSize,
        this->rotation,
        this->color
    );
    if (debug) {
        this->renderer->debug(this->coords, this->hitboxSize);
    }
}

void Sprite::setRotation(GLfloat degrees) {
    this->rotation = degrees;
}

void Sprite::setSize(glm::vec2 size) {
    this->spriteSize = size;
}
