#pragma once

#include <string>
#include <vector>
#include <glm/glm.hpp>

struct TileLocationInfo {
    glm::vec2 coords;
    int gid;
};

struct TilesetAnimation {
    int frameCount;
    float animationSpeed;
    std::vector<int> tileIds;
};

struct TilesetInfo {
    std::string name;
    int firstGid;
    int columns;
    int tileCount;
    std::vector<TilesetAnimation> animations;
};

struct Dialog {
    std::string avatar;
    std::string name;
    std::string text;
};

enum GameState {GAME_START, MAIN_MENU};

enum SpriteState {
    IDLE, MOVING, JUMPING, FALLING, GROUNDED,
    SWITCHING_STANCE, ATTACK_STANCE,
    ATTACKING, AERIAL_ATTACKING
};