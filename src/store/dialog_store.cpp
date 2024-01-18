#include "store/dialog_store.h"

Json::Value DialogStore::dialogs;
std::string DialogStore::dialogPosition = "bottom";
DialogData DialogStore::dialogData = {
    false, // isOpen
    "",    // identifier
    false, // isFinished
    0      // currentLine
};
int DialogStore::debounceIndex = 0;

void DialogStore::preload()
{
    const std::string dialogsPath = Config::getRootDirectory() + "/data/dialogs.json";
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

int DialogStore::getDebounceIndex()
{

    return debounceIndex;
}

bool DialogStore::hasDebounceFinished()
{
    std::vector<Dialog> dialog = getDialogByIdentifier(dialogData.identifier);

    if (static_cast<int>(dialog.size()) > 0)
    {
        int dialogueLineLength = dialog[getCurrentLine()].text.length();
        return debounceIndex >= dialogueLineLength;
    }

    return true;
}

void DialogStore::skipDebounce()
{
    std::vector<Dialog> dialog = getDialogByIdentifier(dialogData.identifier);

    if (static_cast<int>(dialog.size()) > 0)
    {
        int dialogueLineLength = dialog[getCurrentLine()].text.length();
        debounceIndex = dialogueLineLength;
    }
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

void DialogStore::incrementDebounceIndex()
{
    if (!hasDebounceFinished())
    {
        debounceIndex++;
    }
}

void DialogStore::advanceDialog()
{
    if (dialogData.currentLine < static_cast<int>(dialogs[dialogData.identifier].size()) - 1)
    {
        debounceIndex = 0;
        dialogData.currentLine++;
    }
    else
    {
        dialogData.isFinished = true;
    }
}

void DialogStore::closeDialog()
{
    dialogData.identifier = "";
    dialogData.isOpen = false;
    dialogData.isFinished = false;
    dialogData.currentLine = 0;
    debounceIndex = 0;
}

std::vector<Dialog> DialogStore::getDialogByIdentifier(std::string identifier)
{
    Json::Value dialogJson = dialogs[identifier];
    std::vector<Dialog> dialog;
    for (
        Json::Value::const_iterator itr = dialogJson.begin();
        itr != dialogJson.end();
        itr++)
    {
        const Json::Value &dialogObject = *itr;
        Dialog dialogueLine = {
            dialogObject[std::string("avatar")].asString(),
            dialogObject[std::string("name")].asString(),
            dialogObject[std::string("text")].asString()};
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