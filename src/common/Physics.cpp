#include "Physics.hpp"

GLfloat Physics::calculateHeight(GLfloat height, GLfloat dt) {
    return height + 100.0f * dt;
}

GLboolean Physics::collides(glm::vec2 selfCoords, glm::vec2 selfSize, glm::vec2 otherCoords, glm::vec2 otherSize) {
    return (
        selfCoords.x + selfSize.x >= otherCoords.x &&
        selfCoords.x <= otherCoords.x + otherSize.x &&
        selfCoords.y - selfSize.y <= otherCoords.y && // self top higher than other bottom
        selfCoords.y >= otherCoords.y - otherSize.y // self bottom lower than other top
    );
}
