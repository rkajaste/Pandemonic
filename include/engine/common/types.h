#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

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

enum EntityState
{
    IDLE,
    MOVING,
    JUMPING,
    FALLING,
    GROUNDED,
    SWITCHING_STANCE,
    SWITCHING_TO_ATTACK_STANCE,
    SWITCHING_TO_IDLE_STANCE,
    ATTACK_STANCE,
    ATTACKING,
    AERIAL_ATTACKING
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
