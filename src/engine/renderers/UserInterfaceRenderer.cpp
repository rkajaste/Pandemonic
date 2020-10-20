#include "UserInterfaceRenderer.hpp"

UserInterfaceRenderer::UserInterfaceRenderer(): Renderer {}{
    this->shader = ResourceManager::GetShader("ui");
    this->statusBarShader = ResourceManager::GetShader("statusBar");
}

void UserInterfaceRenderer::drawComponent(std::string textureName, glm::vec2 position, glm::vec2 size)
{
    // Prepare transformations
    this->shader.Use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));

    Texture2D texture = ResourceManager::GetTexture("ui_" + textureName);

    this->shader.SetMatrix4("model", model);
    this->shader.SetMatrix4("view", glm::mat4(1.0f));

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();
    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void UserInterfaceRenderer::drawHealthBar(glm::vec2 position, glm::vec2 size)
{
    this->statusBarShader.Use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));

    this->statusBarShader.SetMatrix4("model", model);
    this->statusBarShader.SetMatrix4("view", glm::mat4(1.0f));
    this->statusBarShader.SetVector2f("size", size);

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
