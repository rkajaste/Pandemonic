#include "Sprite.hpp"

Sprite::Sprite(
    glm::vec2 coords, 
    Texture2D image, 
    SpriteRenderer renderer, 
    glm::vec2 size
){
    this->coords = coords;
    this->image = image;
    this->renderer = renderer;
    this->size = size;
    this->rotate = 0.0f;
    this->color = glm::vec3(1.0f);
}
Sprite::update(GLfloat dt) {

}
Sprite::draw(GLfloat dt) {
    this->renderer.DrawSprite(this->image, this->coords, this->size, this->rotate, this->color);
}