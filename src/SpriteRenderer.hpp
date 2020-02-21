#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <common/texture.hpp>
#include <common/shader.hpp>


class SpriteRenderer
{
    public:
        SpriteRenderer(Shader shader);
        ~SpriteRenderer();

        void DrawSprite(Texture2D texture, glm::vec2 position, 
            glm::vec2 size = glm::vec2(64, 64), GLfloat rotate = 0.0f, 
            glm::vec3 color = glm::vec3(1.0f));
    private:
        Shader shader; 
        GLuint quadVAO;

        void initRenderData();
};