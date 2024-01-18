#include "config.h"

std::array<std::pair<GLfloat, GLfloat>, 4> Config::screenResolutions = {
    std::pair<GLfloat, GLfloat>(2560.0f, 1440.0f),
    std::pair<GLfloat, GLfloat>(1920.0f, 1080.0f),
    std::pair<GLfloat, GLfloat>(1024.0f, 768.0f),
    std::pair<GLfloat, GLfloat>(800.0f, 600.0f)};

std::string Config::ROOT_DIRECTORY = "";
GLfloat Config::SCREEN_WIDTH = screenResolutions[1].first;
GLfloat Config::SCREEN_HEIGHT = screenResolutions[1].second;
bool Config::isFullscreen = false;
bool Config::isImmediateMode = true;
bool Config::isDebugMode = true;

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

std::map<UserInput, GLboolean> Config::setupKeys(GLboolean keys[2048])
{
    GLFWgamepadstate state;

    if (glfwGetGamepadState(GLFW_JOYSTICK_1, &state))
    {
        return {
            {MOVE_LEFT, keys[GLFW_KEY_LEFT] || state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_LEFT]},
            {MOVE_RIGHT, keys[GLFW_KEY_RIGHT] || state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_RIGHT]},
            {JUMP, keys[GLFW_KEY_UP] || state.buttons[GLFW_GAMEPAD_BUTTON_DPAD_UP]},
            {ATTACK, keys[GLFW_KEY_SPACE] || state.buttons[GLFW_GAMEPAD_BUTTON_X] || state.buttons[GLFW_GAMEPAD_BUTTON_SQUARE]},
            {INTERACT, keys[GLFW_KEY_E] || state.buttons[GLFW_GAMEPAD_BUTTON_A] || state.buttons[GLFW_GAMEPAD_BUTTON_CROSS]},
            {SWITCH_STANCE, keys[GLFW_KEY_X] || state.buttons[GLFW_GAMEPAD_BUTTON_Y] || state.buttons[GLFW_GAMEPAD_BUTTON_TRIANGLE]}};
    }

    return {
        {MOVE_LEFT, keys[GLFW_KEY_LEFT]},
        {MOVE_RIGHT, keys[GLFW_KEY_RIGHT]},
        {JUMP, keys[GLFW_KEY_UP]},
        {ATTACK, keys[GLFW_KEY_SPACE]},
        {INTERACT, keys[GLFW_KEY_E]},
        {SWITCH_STANCE, keys[GLFW_KEY_X]}};
}

void Config::simpleiniHelper()
{
    // simple demonstration

    // CSimpleIniA ini;
    // ini.SetUnicode();

    // SI_Error rc = ini.LoadFile("example.ini");
    // if (rc < 0)
    // { /* handle error */
    // };

    // const char *pv;
    // pv = ini.GetValue("section", "key", "default");

    // ini.SetValue("section", "key", "newvalue");

    // pv = ini.GetValue("section", "key", "default");
}
