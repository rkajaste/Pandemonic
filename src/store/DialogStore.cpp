#include "store/DialogStore.hpp"

Json::Value DialogStore::dialogs;
std::string DialogStore::dialogPosition = "bottom";
DialogData DialogStore::dialogData = { false, "", false, 0 };

void DialogStore::preload()
{
    const std::string dialogsPath = std::string(PROJECT_SOURCE_DIR) + "/data/dialogs.json";
    std::ifstream stream(dialogsPath, std::ifstream::binary);
    stream >> dialogs;
}

std::string DialogStore::getDialogIdentifier()
{
    return dialogData.identifier;
}

int DialogStore::getCurrentLine()
{
    return dialogData.currentLine;
}

bool DialogStore::isDialogFinished()
{
    return dialogData.isFinished;
}

bool DialogStore::isDialogOpen()
{
    return dialogData.isOpen;
}

void DialogStore::setDialogIdentifer(std::string identifier)
{
    dialogData.identifier = identifier;
}

void DialogStore::openDialog()
{
    dialogData.isOpen = true;
}

void DialogStore::advanceDialog()
{
    if (dialogs[dialogData.identifier].size() > dialogData.currentLine + 1) {
        dialogData.currentLine++;
    } else {
        dialogData.isFinished = true;
    }
}

void DialogStore::closeDialog()
{
    dialogData.identifier = "";
    dialogData.isOpen = false;
    dialogData.isFinished = false;
    dialogData.currentLine = 0;
}

std::vector<Dialog> DialogStore::getDialogByIdentifier(std::string identifier)
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

void DialogStore::setDialogPositionTop()
{
    dialogPosition = "top";
}

void DialogStore::setDialogPositionBottom()
{
    dialogPosition = "bottom";
}

bool DialogStore::isDialogPositionedTop()
{
    return dialogPosition == "top";
}