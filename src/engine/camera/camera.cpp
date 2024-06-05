#include "camera.h"

Camera::Camera()
{
    this->view = glm::translate(this->view, glm::vec3(glm::vec2(0.0f), -1.0f));
    this->offset.x = Config::getScreenWidth() / 2;
    this->offset.y = Config::getScreenHeight() / 2;
}

void Camera::setPosition(glm::vec2 playerCoords)
{
    this->position.x = -playerCoords.x + this->offset.x;
    this->position.y = -playerCoords.y + this->offset.y;
    this->contain(playerCoords);
    this->view = glm::mat4(1.0f);
    this->view = glm::translate(this->view, glm::vec3(this->position, -1.0f));
    ResourceStore::GetShader("sprite").SetMatrix4("view", this->view, GL_TRUE);
    ResourceStore::GetShader("tile").SetMatrix4("view", this->view, GL_TRUE);
    ResourceStore::GetShader("hitbox").SetMatrix4("view", this->view, GL_TRUE);
}

void Camera::contain(glm::vec2 playerCoords)
{
    const GLfloat playerAndTileHeight = 128.0f + 64.0f;
    DialogStore::setDialogPositionBottom();
    if (playerCoords.x < Config::getScreenWidth() / 2)
    {
        this->position.x = 0.0f;
    }
    if (playerCoords.x > MapStore::getWorldWidth() - Config::getScreenWidth() / 2)
    {
        this->position.x = -MapStore::getWorldWidth() + Config::getScreenWidth();
    }
    if (playerCoords.y + this->offset.y >= MapStore::getWorldHeight() - playerAndTileHeight)
    {
        this->position.y = -MapStore::getWorldHeight() + Config::getScreenHeight();
        DialogStore::setDialogPositionTop();
    }
}
