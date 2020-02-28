#include "Sprite.hpp"

Sprite::Sprite(glm::vec2 coords, Texture2D texture, SpriteRenderer *renderer) {
    this->coords = coords;
    this->texture = texture;
    this->renderer = renderer;
    this->size = glm::vec2(255.0f, 170.0f);
    this->rotation = 0.0f;
    this->color = glm::vec3(1.0f);
}

void Sprite::update(GLfloat dt) {

}

void Sprite::draw() {
    this->renderer->DrawSprite(this->texture, this->coords, this->size, this->rotation, this->color);
}

void Sprite::setRotation(GLfloat degrees) {
    this->rotation = degrees;
}

void Sprite::setSize(glm::vec2 size) {
    this->size = size;
}