#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>

namespace Physics
{
    GLfloat calculateGravity(GLfloat gravityForce, GLfloat dt);
    GLboolean collides(glm::vec2 selfCoords, glm::vec2 selfSize, glm::vec2 otherCoords, glm::vec2 otherSize);
    GLboolean isGrounded(glm::vec2 self, glm::vec2 floor);
}
