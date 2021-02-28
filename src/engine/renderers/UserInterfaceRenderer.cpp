#include "UserInterfaceRenderer.hpp"

UserInterfaceRenderer::UserInterfaceRenderer(): Renderer {}{
    this->shader = ResourceManager::GetShader("ui");
    this->statusBarShader = ResourceManager::GetShader("statusBar");
}

void UserInterfaceRenderer::drawComponent(std::string textureName, glm::vec2 position, glm::vec2 size)
{
    this->initRenderData(this->defaultVertices, sizeof(this->defaultVertices));
    // Prepare transformations
    this->shader.Use();
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, Constants::LAYER_INDEXES[RenderingLayer::USER_INTERFACE]));
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

void UserInterfaceRenderer::drawBar(glm::vec2 position, glm::vec2 size, glm::vec4 color, GLint maxValue, GLint currentValue)
{
    GLfloat vertices[24] = {
        // Pos      // Tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        0.88f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };
    this->initRenderData(vertices, sizeof(vertices));
    this->statusBarShader.Use();

    if (maxValue > 0) {
        size.x = calculateBarWidth(size.x, maxValue, currentValue);
    }

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, Constants::LAYER_INDEXES[RenderingLayer::USER_INTERFACE]));
    model = glm::scale(model, glm::vec3(size, 1.0f));

    this->statusBarShader.SetMatrix4("model", model);
    this->statusBarShader.SetMatrix4("view", glm::mat4(1.0f));
    this->statusBarShader.SetVector2f("size", size);
    this->statusBarShader.SetVector4f("barColor", color);

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

GLfloat UserInterfaceRenderer::calculateBarWidth(GLfloat maxWidth, GLint maxValue, GLint currentValue)
{
    GLfloat width = maxWidth * ((GLfloat)currentValue / maxValue);

    return width;
}
