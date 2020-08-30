#include "Config.hpp"


std::array<std::pair<GLfloat, GLfloat>, 4> Config::screenResolutions = { 
    std::pair<GLfloat, GLfloat>(2560.0f, 1080.0f),
    std::pair<GLfloat, GLfloat>(1920.0f, 1080.0f),
    std::pair<GLfloat, GLfloat>(1024.0f, 768.0f),
    std::pair<GLfloat, GLfloat>(800.0f, 600.0f)
};
GLfloat Config::SCREEN_WIDTH = screenResolutions[1].first;
GLfloat Config::SCREEN_HEIGHT = screenResolutions[1].second;
GLboolean Config::FULLSCREEN = false;

std::pair<GLfloat, GLfloat> Config::getScreenResolution()
{
    return std::pair<GLfloat, GLfloat>(SCREEN_WIDTH, SCREEN_HEIGHT);
}

std::array<std::pair<GLfloat, GLfloat>, 4> Config::getScreenResolutions()
{
    return screenResolutions;
}

GLfloat Config::getScreenWidth()
{
    return SCREEN_WIDTH;
}

GLfloat Config::getScreenHeight()
{
    return SCREEN_HEIGHT;
}

void Config::setScreenSize(int preset)
{
    SCREEN_WIDTH = screenResolutions[preset].first;
    SCREEN_HEIGHT = screenResolutions[preset].second;
}

GLboolean Config::isDebugMode()
{
    return DEBUG;
}

GLboolean Config::isFullscreen()
{
    return FULLSCREEN;
}

void Config::setFullscreen(GLboolean isFullscreen)
{
    FULLSCREEN = isFullscreen;
}