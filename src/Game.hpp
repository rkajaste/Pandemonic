#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Game {
    public:
        Game(int width, int height, const char* title);
        void start();
    private:
        GLFWwindow* window;
        int windowWidth;
        int windowHeight;
        const char* windowTitle;
        void createWindow();
};