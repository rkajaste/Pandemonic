#include "store/player_store.h"

int PlayerStore::maxHP = 0;
int PlayerStore::currentHP = 0;
int PlayerStore::maxMP = 0;
int PlayerStore::currentMP = 0;

PlayerStats PlayerStore::getPlayerStats()
{
    PlayerStats stats = {
        PlayerStore::maxHP,
        PlayerStore::currentHP,
        PlayerStore::maxMP,
        PlayerStore::currentMP};

    return stats;
}