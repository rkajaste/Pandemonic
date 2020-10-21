#include "Store.hpp"

PlayerStatus Store::playerStatus;

PlayerStatus Store::getPlayerStatus()
{
    return playerStatus;
}

void Store::setPlayerStatus(PlayerStatus status)
{
    playerStatus = status;
}