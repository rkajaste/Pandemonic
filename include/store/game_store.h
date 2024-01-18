#pragma once

#include <glad/glad.h>
#include <string>
#include <vector>
#include <map>
#include <json/json.h>
#include <fstream>
#include "engine/common/types.h"

class GameStore
{
public:
    static GameState getGameState();
    static void setGameState(GameState);

private:
    GameStore(){};

    static GameState gameState;
};
