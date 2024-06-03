#include "physics.h"

GLfloat Physics::calculateGravity(GLfloat gravityForce, GLfloat dt)
{
    gravityForce += 3000.0f * dt;
    return gravityForce;
}

GLboolean Physics::collides(glm::vec2 selfCoords, glm::vec2 selfSize, glm::vec2 otherCoords, glm::vec2 otherSize)
{
    float selfCoordsY = MapManager::getWorldHeight() - selfCoords.y;
    float otherCoordsY = MapManager::getWorldHeight() - otherCoords.y;
    float selfTop = selfCoordsY;
    float selfBottom = selfCoordsY - selfSize.y;
    float selfLeft = selfCoords.x;
    float selfRight = selfCoords.x + selfSize.x;
    float otherTop = otherCoordsY;
    float otherBottom = otherCoordsY - otherSize.y;
    float otherLeft = otherCoords.x;
    float otherRight = otherCoords.x + otherSize.x;

    return (
        selfRight >= otherLeft &&
        selfLeft <= otherRight &&
        selfTop >= otherBottom &&
        selfBottom <= otherTop
    );
}
