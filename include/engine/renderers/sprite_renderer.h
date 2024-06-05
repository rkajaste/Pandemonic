#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"
#include "engine/store/resource_store.h"
#include "animator.h"
#include "renderer.h"

class SpriteRenderer : public Renderer
{
public:
    SpriteRenderer();

    void drawSprite(Animator *animator, std::string textureName, glm::vec2 pos, glm::vec2 size, GLboolean flipX = false, GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
    void debug(glm::vec2 position, glm::vec2 hitboxSize);

private:
    Shader hitboxShader;
};
