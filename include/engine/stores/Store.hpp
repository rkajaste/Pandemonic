#pragma once

#include <glad/glad.h>

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
    private:
        Store() { }
        static PlayerStatus playerStatus;
};
