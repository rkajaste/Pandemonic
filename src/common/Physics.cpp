#include "Physics.hpp"

GLfloat Physics::calculateGravity(GLfloat gravityForce, GLfloat dt) {
    gravityForce += 200.0f * dt;
    return gravityForce;
}

GLboolean Physics::collides(glm::vec2 selfCoords, glm::vec2 selfSize, glm::vec2 otherCoords, glm::vec2 otherSize) {
    return (
        selfCoords.x + selfSize.x >= otherCoords.x &&
        selfCoords.x <= otherCoords.x + otherSize.x &&
        selfCoords.y - selfSize.y <= otherCoords.y && // self top higher than other bottom
        selfCoords.y >= otherCoords.y - otherSize.y // self bottom lower than other top
    );
}
