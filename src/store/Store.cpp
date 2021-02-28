#include "store/Store.hpp"

GameState Store::gameState = GAME_START;


GameState Store::getGameState()
{
    return gameState;
}

void Store::setGameState(GameState state)
{
    gameState = state;
}
