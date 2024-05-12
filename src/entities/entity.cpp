#include "entity.h"
#include "Tmx.h"
#include "store/map_store.h"
#include "map_manager.h"
#include "physics.h"

Entity::Entity(glm::vec2 coords, SpriteRenderer *renderer)
{
    this->coords = coords;
    this->renderer = renderer;
    this->spriteCoords.x = this->coords.x - this->spriteSize.x / 2 + this->hitboxSize.x / 2;
    this->spriteCoords.y = this->coords.y + this->hitboxSize.y - this->spriteSize.y;
    this->last_coords.x = this->coords.x;
    this->last_coords.y = this->coords.y;
}

Entity::~Entity()
{
    delete this->cooldownManager;
    delete this->animator;
}

void Entity::update(GLfloat dt)
{
    this->addState(FALLING);
    this->checkCollision();
    this->spriteCoords.x = this->coords.x - this->spriteSize.x / 2 + this->hitboxSize.x / 2;
    this->spriteCoords.y = this->coords.y + this->hitboxSize.y - this->spriteSize.y;
    this->last_coords = this->coords;
    if (this->cooldownManager != NULL)
    {
        this->cooldownManager->advanceCooldowns(dt);
    }
}

void Entity::handleCollision(const Tmx::Object *obj)
{
    glm::vec2 objSize(obj->GetWidth(), obj->GetHeight());
    glm::vec2 objCoords(obj->GetX(), obj->GetY());
    float objTop = objCoords.y - objSize.y * 2;
    float objBottom = objCoords.y - objSize.y;
    float objLeft = objCoords.x;
    float objRight = objCoords.x + objSize.x;

    if (Physics::collides(this->coords, this->hitboxSize, objCoords, objSize))
    {
        if (obj->GetName() == "blocker")
        {
            std::string blockerType = obj->GetType();
            std::string context = obj->GetProperties().GetStringProperty("collision_context");

            if (context == MapStore::getCollisionContext() || context == "")
            {
                if (
                    blockerType.find("t") != std::string::npos &&
                    this->last_coords.y <= objTop)
                {
                    this->coords.y = objTop;
                    this->addState(GROUNDED);
                    this->removeState(FALLING);
                }
                if (
                    blockerType.find("b") != std::string::npos &&
                    this->last_coords.y >= objBottom)
                {
                    this->coords.y = objBottom + objSize.y * 2;
                    this->gravityForce = 0.0f;
                }
                if (blockerType.find("l") != std::string::npos &&
                    this->last_coords.x + this->hitboxSize.x <= objLeft)
                {
                    this->coords.x = objCoords.x - this->hitboxSize.x;
                }
                if (blockerType.find("r") != std::string::npos &&
                    this->last_coords.x >= objRight)
                {
                    this->coords.x = objCoords.x + objSize.x;
                }
            }
        }

        if (obj->GetName() == "death")
        {
            if (
                obj->GetProperties().GetIntProperty("damage") == -1)
            {
                if (obj->GetType() == "water" && this->last_coords.y - this->hitboxSize.y >= objTop)
                {
                    this->takeDamage(this->maxHealth);
                }
            }
        }
    }
}

void Entity::checkCollision()
{
    for (const auto &obj : MapManager::getTerrainObjects())
    {
        this->handleCollision(obj);
    }
    for (const auto &obj : MapManager::getDeathObjects())
    {
        this->handleCollision(obj);
    }
}

void Entity::draw(GLboolean debug)
{
    this->renderer->drawSprite(
        this->animator,
        this->textureName,
        this->spriteCoords,
        this->spriteSize,
        this->direction == -1 ? true : false,
        this->rotation,
        this->color);
    if (debug)
    {
        this->renderer->debug(this->coords, this->hitboxSize);
    }
}

void Entity::setRotation(GLfloat degrees)
{
    this->rotation = degrees;
}

void Entity::setSize(glm::vec2 size)
{
    this->spriteSize = size;
}

void Entity::enableGravity(GLfloat dt)
{
    if (this->hasState(FALLING))
    {
        this->gravityForce = Physics::calculateGravity(this->gravityForce, dt);
    }

    if (this->hasState(GROUNDED) && !this->hasState(JUMPING) && !this->hasState(FALLING))
    {
        this->gravityForce = 0;
    }

    this->coords.y += this->gravityForce * dt;
}

void Entity::clearStates()
{
    this->states.clear();
}

void Entity::addState(EntityState state)
{
    this->states.push_back(state);
}

void Entity::removeState(EntityState state)
{
    if (this->hasState(state))
    {
        this->states.erase(std::remove(this->states.begin(), this->states.end(), state), this->states.end());
    }
}

GLboolean Entity::hasState(EntityState state)
{
    return Util::existsInVector(state, this->states);
}

void Entity::jump()
{
    this->gravityForce = -this->jumpForce;
    this->removeState(JUMPING);
    this->removeState(GROUNDED);
}

void Entity::move(GLfloat dt)
{
    this->coords.x += glm::round(this->speed * dt * this->direction);
}
