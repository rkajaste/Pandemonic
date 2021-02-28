#include "store/PlayerStore.hpp"

PlayerStats PlayerStore::playerStats;

PlayerStats PlayerStore::getPlayerStats()
{
    return playerStats;
}

void PlayerStore::setPlayerStats(PlayerStats status)
{
    playerStats = status;
}