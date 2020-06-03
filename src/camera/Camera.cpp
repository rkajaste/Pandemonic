#include "Camera.hpp"

GLfloat responsiveOffsetY = SCREEN_HEIGHT - 768.0f;

Camera::Camera()
{
    this->view = glm::translate(this->view, glm::vec3(glm::vec2(0.0f), -1.0f));
    this->offset.x = SCREEN_WIDTH / 2;
    this->offset.y = SCREEN_HEIGHT / 2;
    // 192.0f = player hitbox size Y + one tile size Y
    this->minCameraY = responsiveOffsetY - 192.0f;
}

void Camera::setPosition(glm::vec2 playerCoords)
{
    this->position.x = -playerCoords.x + this->offset.x;
    this->position.y = -playerCoords.y + this->offset.y;
    //this->contain(playerCoords);
    this->view = glm::mat4(1.0f);
    this->view = glm::translate(this->view, glm::vec3(this->position, -1.0f));
    ResourceManager::GetShader("sprite").SetMatrix4("view", this->view, GL_TRUE);
    ResourceManager::GetShader("tile").SetMatrix4("view", this->view, GL_TRUE);
    ResourceManager::GetShader("hitbox").SetMatrix4("view", this->view, GL_TRUE);
}

void Camera::contain(glm::vec2 playerCoords)
{
    if(playerCoords.x < SCREEN_WIDTH / 2) {
        this->position.x = 0.0f;
    }
    if(playerCoords.x > MapManager::getWorldWidth() - SCREEN_WIDTH / 2) {
        this->position.x = -MapManager::getWorldWidth() + SCREEN_WIDTH;
    }
    if(playerCoords.y + this->offset.y >= responsiveOffsetY - MapManager::getWorldHeight()){
        this->position.y = this->minCameraY;
    }
}
