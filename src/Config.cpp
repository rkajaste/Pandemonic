#include "Config.hpp"

std::array<std::pair<GLfloat, GLfloat>, 4> Config::screenResolutions = {
    std::pair<GLfloat, GLfloat>(2560.0f, 1440.0f),
    std::pair<GLfloat, GLfloat>(1920.0f, 1080.0f),
    std::pair<GLfloat, GLfloat>(1024.0f, 768.0f),
    std::pair<GLfloat, GLfloat>(800.0f, 600.0f)};

GLfloat Config::SCREEN_WIDTH = screenResolutions[1].first;
GLfloat Config::SCREEN_HEIGHT = screenResolutions[1].second;
GLboolean Config::FULLSCREEN = false;
std::string Config::ROOT_DIRECTORY = "";

std::pair<GLfloat, GLfloat>
Config::getScreenResolution()
{
    return std::pair<GLfloat, GLfloat>(SCREEN_WIDTH, SCREEN_HEIGHT);
}

std::array<std::pair<GLfloat, GLfloat>, 4> Config::getScreenResolutions()
{
    return screenResolutions;
}

std::string Config::getRootDirectory()
{
    return ROOT_DIRECTORY;
}

void Config::setRootDirectory()
{
    TCHAR path[MAX_PATH];
    GetModuleFileName(NULL, path, MAX_PATH);

    std::string pathStr(path);
    std::size_t position = pathStr.find_last_of("\\");
    std::string rootDirectory = pathStr.substr(0, position);
    std::replace(rootDirectory.begin(), rootDirectory.end(), '\\', '/');

    ROOT_DIRECTORY = rootDirectory;
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