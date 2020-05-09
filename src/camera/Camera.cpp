#include "Camera.hpp"

Camera::Camera()
{
    this->view = glm::translate(this->view, glm::vec3(-glm::vec2(0.0f), -1.0f));

}

void Camera::setPosition(glm::vec2 coords)
{
    glm::vec2 position(-coords.x + SCREEN_WIDTH / 3, -coords.y + SCREEN_HEIGHT / 2);
    this->view = glm::mat4(1.0f);
    this->view = glm::translate(this->view, glm::vec3(position, -1.0f));
    printf("X: %02f, Y: %02f\n", position.x, position.y);
    ResourceManager::GetShader("sprite").SetMatrix4("view", this->view, GL_TRUE);
    ResourceManager::GetShader("tile").SetMatrix4("view", this->view, GL_TRUE);
}