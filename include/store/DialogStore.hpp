#pragma once

#include <glad/glad.h>
#include <string>
#include <vector>
#include <map>
#include <json/json.h>
#include <fstream>
#include "engine/common/types.hpp"

struct DialogData {
    bool isOpen;
    std::string identifier;
    bool isFinished;
    int currentLine;
};

class DialogStore {
    public:
        static std::vector<Dialog> getDialogByIdentifier(std::string identifier);
        static std::string getDialogIdentifier();
        static int getCurrentLine();
        static int getDebounceIndex();
        static bool hasDebounceFinished();
        static void skipDebounce();
        static void setDialogIdentifer(std::string identifier);
        static bool isDialogOpen();
        static bool isDialogFinished();
        static void openDialog();
        static void closeDialog();
        static void advanceDialog();
        static void setDialogPositionTop();
        static void setDialogPositionBottom();
        static bool isDialogPositionedTop();
        static void incrementDebounceIndex();

        static void preload();
    private:
        DialogStore(){};

        static std::string dialogPosition;
        static DialogData dialogData;
        static Json::Value dialogs;
        static int debounceIndex;
        static void preloadDialogues();
};
