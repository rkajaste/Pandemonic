#pragma once
#include <string>
#include <vector>
#include <glm/glm.hpp>

// X Macro for easier maintanability
// https://en.wikipedia.org/wiki/X_macro
#define ENTITY_STATES \
X(IDLE, "IDLE") \
X(MOVING, "MOVING") \
X(JUMPING, "JUMPING") \
X(FALLING, "FALLING") \
X(GROUNDED, "GROUNDED") \
X(SWITCHING_STANCE, "SWITCHING_STANCE") \
X(SWITCHING_TO_ATTACK_STANCE, "SWITCHING_TO_ATTACK_STANCE") \
X(SWITCHING_TO_IDLE_STANCE, "SWITCHING_TO_IDLE_STANCE") \
X(ATTACK_STANCE, "ATTACK_STANCE") \
X(ATTACKING, "ATTACKING") \
X(AERIAL_ATTACKING, "AERIAL_ATTACKING")


#define X(state, name) state,
enum EntityState : size_t
{
    ENTITY_STATES
};
#undef X



struct TileLocationInfo
{
    int gid;
    glm::vec2 coords;
    std::string layer;
};

struct TilesetAnimation
{
    int frameCount;
    float animationSpeed;
    std::vector<int> tileIds;
};

struct TilesetInfo
{
    std::string name;
    int firstGid;
    int columns;
    int tileCount;
    std::vector<TilesetAnimation> animations;
};

struct Dialog
{
    std::string avatar;
    std::string name;
    std::string text;
};

enum GameState
{
    GAME_START,
    MAIN_MENU
};

enum UserInput
{
    MOVE_LEFT,
    MOVE_RIGHT,
    JUMP,
    ATTACK,
    INTERACT,
    SWITCH_STANCE
};

