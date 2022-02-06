#pragma once

#include <glad/glad.h>
#include <string>
#include <vector>
#include <map>
#include <json/json.h>
#include <fstream>
#include "engine/common/types.hpp"

class Store
{
public:
    static GameState getGameState();
    static void setGameState(GameState);

private:
    Store(){};

    static GameState gameState;
};
