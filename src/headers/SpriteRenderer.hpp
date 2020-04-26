#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.hpp"
#include "shader.hpp"

class SpriteRenderer
{
private:

    Shader shader;
    GLuint quadVAO;

public:
    SpriteRenderer(Shader shader);
    ~SpriteRenderer();
public:
    void DrawSprite(Texture2D &tex, glm::vec2 pos, glm::vec2 size = glm::vec2(10, 10), GLfloat rot = 0.0f, glm::vec3 color = glm::vec3(1.0f));

private:
    void initRenderData();
};