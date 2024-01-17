#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>
#include <cstdio>
#include <cstdlib>

#include "Config.hpp"
#include "Game.hpp"
#include "ResourceManager.hpp"
#include "engine/imgui/ImGuiHelper.hpp"
#include "engine/frame_buffer/FrameBuffer.hpp"

// GLFW function declarations
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

Game *game;
FrameBuffer *frameBuffer;
int main()
{
    Config::setRootDirectory();

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow *window = glfwCreateWindow(Config::getScreenWidth(), Config::getScreenHeight(), "Pandemonic", Config::isFullscreen() ? glfwGetPrimaryMonitor() : nullptr, nullptr);

    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    gladLoadGL();
    fprintf(stderr, "OpenGL Version %s\n", glGetString(GL_VERSION));
    
    if (Config::isImmediateMode) ImGuiHelper::init(window);

    glfwSetKeyCallback(window, key_callback);

    // OpenGL configuration
    glViewport(0, 0, bufferWidth, bufferHeight);
    frameBuffer = new FrameBuffer();
    frameBuffer->create(bufferWidth, bufferHeight);

    game = new Game(Config::getScreenWidth(), Config::getScreenHeight());
    // Initialize game
    game->init();

    // DeltaTime variables
    GLfloat lastFrameTime = 0.0f;
    GLfloat accumulator = 0.0f;
    GLfloat dt = 0.01f;

    const double maxFPS = 60.0f;
    const double maxPeriod = 1.0 / maxFPS;

    while (!glfwWindowShouldClose(window))
    {
        // Calculate delta time
        GLfloat newFrameTime = glfwGetTime();
        GLfloat frameTime = newFrameTime - lastFrameTime;
        if (frameTime >= maxPeriod)
        {
            glfwPollEvents();

            if (frameTime > 0.25f)
            {
                frameTime = 0.25f;
            }
            lastFrameTime = newFrameTime;
            accumulator += frameTime;

            while (accumulator >= dt)
            {
                // Manage user input
                game->processInput(dt);
                game->update(dt);
                accumulator -= dt;
            }

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearDepth(1.0f);
            glEnable(GL_CULL_FACE);
            glEnable(GL_BLEND);
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LEQUAL);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            if (Config::isImmediateMode)
            {

                ImGuiHelper::drawGUI(frameBuffer);

                frameBuffer->bind();
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glClearDepth(1.0f);
                game->render();
                frameBuffer->unbind();
                ImGuiHelper::render();
            }
            else
            {
                game->render();
            }
            glDisable(GL_BLEND);
            glfwSwapBuffers(window);
        }
    }
    // Delete all resources as loaded using the resource manager
    ResourceManager::Clear();
    
    if (Config::isImmediateMode) ImGuiHelper::destroy();

    delete frameBuffer;
    delete game;

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void key_callback(GLFWwindow *window, int key, int /*scancode*/, int action, int /*mode*/)
{
    // When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            game->keys[key] = GL_TRUE;
        else if (action == GLFW_RELEASE)
            game->keys[key] = GL_FALSE;
    }
}
