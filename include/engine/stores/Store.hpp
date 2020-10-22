#pragma once

#include <glad/glad.h>

#include "types.hpp"

struct PlayerStatus {
    GLint maxHP;
    GLint currentHP;
    GLint maxMP;
    GLint currentMP;
};

class Store {
    public:
        static PlayerStatus getPlayerStatus();
        static void setPlayerStatus(PlayerStatus);
        
        static GameState getGameState();
        static void setGameState(GameState);
    private:
        Store() { }
        static PlayerStatus playerStatus;
        static GameState gameState;
};
