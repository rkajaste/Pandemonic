#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <src/Game.hpp>

int main() {
    glewExperimental = true;
    if(!glfwInit()){
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }
    Game game(1024, 768, "Test");
    game.start()
};
