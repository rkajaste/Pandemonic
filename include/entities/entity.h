#pragma once

#include <glm/glm.hpp>
#include <glad/glad.h>
#include "sprite_renderer.h"
#include "animator.h"
#include "cooldown_manager.h"
#include "types.h"
#include "Tmx.h"

class Entity
{
public:
    Entity(glm::vec2 coords, SpriteRenderer *renderer);
    virtual ~Entity();

    glm::vec2 coords;
    glm::vec2 last_coords;
    void update(GLfloat);
    void draw(GLboolean debug = false);
    void setRotation(GLfloat);
    void setColor(glm::vec3);
    void setSize(glm::vec2);

protected:
    SpriteRenderer *renderer;
    Animator *animator;
    CooldownManager *cooldownManager = NULL;
    int health;
    int maxHealth;
    int mana;
    int maxMana;

    int direction = 1;
    GLfloat speed = 1000.0f;
    GLfloat jumpForce = 1100.0f;
    GLfloat gravityForce = 0.0f;
    glm::vec3 color = glm::vec3(1.0f);
    GLfloat rotation = 0.0f;

    std::vector<EntityState> states;
    std::string textureName;
    glm::vec2 spriteCoords;
    glm::vec2 spriteSize;
    glm::vec2 hitboxSize;

    void enableGravity(GLfloat dt);
    void clearStates();
    void addState(EntityState);
    void removeState(EntityState);
    void jump();
    void move(GLfloat dt);
    virtual void die() = 0;
    virtual void takeDamage(GLint damage) = 0;

    GLboolean hasState(EntityState);

private:
    void checkCollision();
    void handleCollision(const Tmx::Object *obj);
};
