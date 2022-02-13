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
#include "Config.hpp"
#include "engine/common/types.hpp"

/*******************************************************************
** Static configuration helper class for changing different
** parameters ie. screen size, fullscreen
******************************************************************/
class Config
{
public:
    static std::string ROOT_DIRECTORY;
    static GLfloat SCREEN_WIDTH;
    static GLfloat SCREEN_HEIGHT;
    static GLboolean FULLSCREEN;
    static std::array<std::pair<GLfloat, GLfloat>, 4> screenResolutions;
    static const GLboolean DEBUG = true;

    static std::string getRootDirectory();
    static std::pair<GLfloat, GLfloat> getScreenResolution();
    static std::array<std::pair<GLfloat, GLfloat>, 4> getScreenResolutions();
    static GLfloat getScreenWidth();
    static GLfloat getScreenHeight();
    static void setScreenSize(int preset);
    static GLboolean isDebugMode();
    static GLboolean isFullscreen();
    static void setRootDirectory();
    static void setFullscreen(GLboolean isFullscreen);
    static std::map<UserInput, GLboolean> setupKeys(GLboolean keys[2048]);
    static void simpleiniHelper();

private:
    Config(){};
};
