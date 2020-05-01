#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.hpp"
#include "shader.hpp"

class SpriteRenderer
{
    public:
        SpriteRenderer(Shader shader);
        ~SpriteRenderer();
        void DrawSprite(Texture2D tex, glm::vec2 pos, glm::vec2 size, GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

    private:
        Shader shader;
        GLuint quadVAO;
        void initRenderData();
};