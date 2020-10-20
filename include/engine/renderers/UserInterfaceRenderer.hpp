#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Texture.hpp"
#include "Shader.hpp"
#include "ResourceManager.hpp"
#include "Animator.hpp"
#include "Renderer.hpp"

class UserInterfaceRenderer: public Renderer
{
    public:
        UserInterfaceRenderer();

        void drawComponent(std::string textureName, glm::vec2 position, glm::vec2 size);
        void drawHealthBar(glm::vec2 position, glm::vec2 size);
    
    private:
        Shader statusBarShader;
};
