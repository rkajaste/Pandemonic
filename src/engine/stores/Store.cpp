#include "Store.hpp"

PlayerStatus Store::playerStatus;
GameState Store::gameState = MAIN_MENU;

PlayerStatus Store::getPlayerStatus()
{
    return playerStatus;
}

void Store::setPlayerStatus(PlayerStatus status)
{
    playerStatus = status;
}

GameState Store::getGameState()
{
    return gameState;
}

void Store::setGameState(GameState state)
{
    gameState = state;
}