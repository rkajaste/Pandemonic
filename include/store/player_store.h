#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "types.h"

struct PlayerStats
{
    int maxHP;
    int currentHP;
    int maxMP;
    int currentMP;
};

class PlayerStore
{
public:
    static glm::vec2 position;
    static EntityState state;
    static int maxHP;
    static int currentHP;
    static int maxMP;
    static int currentMP;
    static std::vector<EntityState> activeStates;
    static PlayerStats getPlayerStats();

private:
    PlayerStore(){};
};
