#pragma once

#include <glm/glm.hpp>
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
    static PlayerStats getPlayerStats();

private:
    PlayerStore(){};
};
