#pragma once

class Game {
    public:
        void start();
    private:
        GLFWwindow* window;
        void createWindow();
}