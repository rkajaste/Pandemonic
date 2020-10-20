#include "SpriteRenderer.hpp"

SpriteRenderer::SpriteRenderer() : Renderer {}
{
    this->shader = ResourceManager::GetShader("sprite");
    this->hitboxShader = ResourceManager::GetShader("hitbox");
}

void SpriteRenderer::drawSprite(Animator* animator, std::string textureName, glm::vec2 position, glm::vec2 size, GLboolean flipX, GLfloat rotate, glm::vec3 color)
{
    // Prepare transformations
    this->shader.Use();
    glm::mat4 model = glm::mat4(1.0f);
    // model = glm::translate(model, glm::vec3(position, 0.0f));  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)

    // model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // Move origin of rotation to center of quad
    // model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
    // model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back

    // model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));

    glm::vec2 textureCoords(animator->getTextureCoords(textureName));
    Texture2D texture = animator->getTexture();

    this->shader.SetMatrix4("model", model);
    this->shader.SetVector3f("spriteColor", color);
    this->shader.SetVector2f("spriteSize", glm::vec2(size));
    this->shader.SetVector2f("offset", textureCoords);
    this->shader.SetVector2f("spritesheetSize", glm::vec2(texture.Width, texture.Height));
    this->shader.SetBoolean("flipX", flipX);

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();
    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    animator->animate();
}

void SpriteRenderer::debug(glm::vec2 position, glm::vec2 hitboxSize)
{
    this->hitboxShader.Use();
    glBindVertexArray(this->quadVAO);

    glm::mat4 hitboxModel = glm::mat4(1.0f);
    hitboxModel = glm::translate(hitboxModel, glm::vec3(position, 0.0f));
    hitboxModel = glm::scale(hitboxModel, glm::vec3(hitboxSize, 1.0f));
    this->hitboxShader.SetMatrix4("model", hitboxModel);
    this->hitboxShader.SetVector2f("size", hitboxSize);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
}
