#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <src/GameState.hpp>

class Game
{
    public:
        GameState  state;
        GLboolean  keys[1024];
        GLuint	   width, height;
        // Constructor/Destructor
        Game(GLuint width, GLuint height);
        ~Game();
        // Initialize game state (load all shaders/textures/levels)
        void init();
        // GameLoop
        void processInput(GLfloat dt);
        void update(GLfloat dt);
        void render();
};