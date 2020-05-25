#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture.hpp"
#include "Shader.hpp"
#include "ResourceManager.hpp"

class SpriteRenderer
{
    public:
        SpriteRenderer(Shader shader);
        ~SpriteRenderer();
        void drawSprite(Texture2D tex, glm::vec2 pos, glm::vec2 size, GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));
        void debug(glm::vec2 position, glm::vec2 hitboxSize);

    private:
        Shader shader;
        Shader hitboxShader;
        GLuint quadVAO;
        void initRenderData();
};