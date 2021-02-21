#include "store/Store.hpp"

PlayerStatus Store::playerStatus;
Json::Value Store::dialogs;
GameState Store::gameState = GAME_START;
DialogData Store::dialogData = { false, "" };

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

std::string Store::getDialogIdentifier()
{
    return dialogData.identifier;
}

bool Store::isDialogOpen()
{
    return dialogData.isOpen;
}

void Store::openDialog(std::string identifier)
{
    dialogData.identifier = identifier;
    dialogData.isOpen = true;
}

std::vector<Dialog> Store::getDialogByIdentifier(std::string identifier)
{
    Json::Value dialogJson = dialogs[identifier];
    std::vector<Dialog> dialog;
    for(
        Json::Value::const_iterator itr = dialogJson.begin();
        itr != dialogJson.end();
        itr++
    ) {
        const Json::Value &dialogObject= *itr;
        Dialog dialogueLine = {
            dialogObject[std::string("avatar")].asString(),
            dialogObject[std::string("name")].asString(),
            dialogObject[std::string("text")].asString()
        };
        dialog.push_back(dialogueLine);
    }

    return dialog;
}

void Store::preloadDialogues()
{
    const std::string dialogsPath = std::string(PROJECT_SOURCE_DIR) + "/data/dialogs.json";
    std::ifstream stream(dialogsPath, std::ifstream::binary);
    stream >> dialogs;
}

void Store::preload()
{
    preloadDialogues();
}
