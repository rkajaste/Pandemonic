#include "store/game_store.h"

GameState GameStore::gameState = GAME_START;

GameState GameStore::getGameState()
{
    return gameState;
}

void GameStore::setGameState(GameState state)
{
    gameState = state;
}
