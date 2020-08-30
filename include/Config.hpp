#pragma once
#include <glad/glad.h>
#include <utility>
#include <vector>
#include <array>

/*******************************************************************
** Static configuration helper class for changing different
** parameters ie. screen size, fullscreen
******************************************************************/
class Config {
    public:
        static GLfloat SCREEN_WIDTH;
        static GLfloat SCREEN_HEIGHT;
        static GLboolean FULLSCREEN;
        static std::array<std::pair<GLfloat, GLfloat>, 4> screenResolutions;
        static const GLboolean DEBUG = true;

        static std::pair<GLfloat, GLfloat> getScreenResolution();
        static std::array<std::pair<GLfloat, GLfloat>, 4> getScreenResolutions();
        static GLfloat getScreenWidth();
        static GLfloat getScreenHeight();
        static void setScreenSize(int preset);
        static GLboolean isDebugMode();
        static GLboolean isFullscreen();
        static void setFullscreen(GLboolean isFullscreen);
    private:
        Config(){};
};
