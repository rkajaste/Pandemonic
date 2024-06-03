#include "store/player_store.h"
#include <vector>

std::vector<EntityState> PlayerStore::activeStates;
glm::vec2 PlayerStore::position = glm::vec2(0, 0);
int PlayerStore::maxHP = 0;
int PlayerStore::currentHP = 0;
int PlayerStore::maxMP = 0;
int PlayerStore::currentMP = 0;

PlayerStats PlayerStore::getPlayerStats()
{
    return {
        PlayerStore::maxHP,
        PlayerStore::currentHP,
        PlayerStore::maxMP,
        PlayerStore::currentMP
    };
}
