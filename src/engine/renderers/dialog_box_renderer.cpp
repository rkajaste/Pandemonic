#include "engine/renderers/dialog_box_renderer.h"

DialogBoxRenderer::DialogBoxRenderer() : Renderer{}
{
    this->shader = ResourceManager::GetShader("ui");
}

void DialogBoxRenderer::drawDialogBox(glm::vec2 position, glm::vec2 size)
{
    this->initRenderData(this->defaultVertices, sizeof(this->defaultVertices));
    this->shader.Use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, Constants::LAYER_INDEXES[RenderingLayer::POPUP]));
    model = glm::scale(model, glm::vec3(size, 1.0f));

    this->shader.SetMatrix4("model", model);
    this->shader.SetMatrix4("view", glm::mat4(1.0f));

    Texture2D texture = ResourceManager::GetTexture("ui_dialog_box");
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void DialogBoxRenderer::drawDialogBoxAvatar(
    glm::vec2 position,
    glm::vec2 size,
    std::string textureName)
{
    this->initRenderData(this->defaultVertices, sizeof(this->defaultVertices));
    this->shader.Use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, Constants::LAYER_INDEXES[RenderingLayer::POPUP]));
    model = glm::scale(model, glm::vec3(size, 1.0f));

    this->shader.SetMatrix4("model", model);
    this->shader.SetMatrix4("view", glm::mat4(1.0f));

    Texture2D texture = ResourceManager::GetTexture(textureName);
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}