#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <windows.h>
#include <pathcch.h>
#include <algorithm>
#include <utility>
#include <vector>
#include <array>
#include <string>
#include <map>
#include <SimpleIni.h>
#include "engine/common/types.h"

/*******************************************************************
** Static configuration helper class for changing different
** parameters ie. screen size, fullscreen
******************************************************************/
class Config
{
public:
    static bool isImmediateMode;
    static bool isDebugMode;
    static bool isFullscreen;
    static std::string getRootDirectory();
    static std::string getMapsDirectory();
    static std::string getAssetsDirectory();
    static std::pair<GLfloat, GLfloat> getScreenResolution();
    static std::array<std::pair<GLfloat, GLfloat>, 4> getScreenResolutions();
    static GLfloat getScreenWidth();
    static GLfloat getScreenHeight();
    static void setScreenSize(int preset);
    static void setRootDirectory();
    static std::map<UserInput, GLboolean> setupKeys(GLboolean keys[2048]);
    static void simpleiniHelper();

private:
    Config(){};
    static std::string ROOT_DIRECTORY;
    static std::string MAPS_DIRECTORY;
    static std::string ASSETS_DIRECTORY;
    static GLfloat SCREEN_WIDTH;
    static GLfloat SCREEN_HEIGHT;
    static std::array<std::pair<GLfloat, GLfloat>, 4> screenResolutions;
};
