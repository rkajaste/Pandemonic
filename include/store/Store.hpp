#pragma once

#include <glad/glad.h>
#include <string>
#include <vector>
#include <map>
#include <json/json.h>
#include <fstream>
#include "engine/common/types.hpp"

struct PlayerStatus {
    GLint maxHP;
    GLint currentHP;
    GLint maxMP;
    GLint currentMP;
};

struct DialogData {
    bool isOpen;
    std::string identifier;
};

class Store {
    public:
        static PlayerStatus getPlayerStatus();
        static void setPlayerStatus(PlayerStatus);

        static GameState getGameState();
        static void setGameState(GameState);

        static std::vector<Dialog> getDialogByIdentifier(std::string identifier);
        static std::string getDialogIdentifier();
        static bool isDialogOpen();
        static void openDialog(std::string identifier);

        static void preload();
    private:
        Store(){};

        static PlayerStatus playerStatus;
        static GameState gameState;
        static DialogData dialogData;
        static Json::Value dialogs;
        static void preloadDialogues();
};
