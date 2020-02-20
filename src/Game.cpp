#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <src/Renderer.hpp>

class Game {
    public:
        Game(){}
        Game(int width = 1024, int height = 768, const char* title = "Game") {
            windowWidth = width;
            windowHeight = height;
            windowTitle = title;
            createWindow()
        };

        void start() {
            if(window == NULL){
                fprintf(stderr, "Failed to open GLFW window");
                glfwTerminate();
                exit(EXIT_FAILURE);
            }
            glfwMakeContextCurrent(window);
            glewExperimental=true;
            if(glewInit() != GLEW_OK){
                fprintf(stderr, "Failed to initialize GLEW\n");
                exit(EXIT_FAILURE);
            }
            // Ensure we can capture ESC key
            glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
            Renderer renderer();
            do {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                
                renderer.draw();

                glfwSwapBuffers(window);
                glfwPollEvents();
            } while (
                glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
                glfwWindowShouldClose(window) == 0
            );
        }
    private:
        GLFWwindow* window;
        int windowWidth;
        int windowHeight;
        const char* windowTitle;
        void createWindow() {
            glfwWindowHint(GLFW_SAMPLES, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL);
        }
};