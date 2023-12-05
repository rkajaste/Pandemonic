#define STB_IMAGE_IMPLEMENTATION

#include <glad/glad.h>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>
#include <cstdio>
#include <cstdlib>

#include "Config.hpp"
#include "Game.hpp"
#include "ResourceManager.hpp"

// GLFW function declerations
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

Game *game;

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

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    gladLoadGL();
    fprintf(stderr, "OpenGL Version %s\n", glGetString(GL_VERSION));
    
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();


    glfwSetKeyCallback(window, key_callback);

    // OpenGL configuration
    glViewport(0, 0, Config::getScreenWidth(), Config::getScreenHeight());
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
            
            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
            ImGui::ShowDemoWindow(); // Show demo window! :)
            
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearDepth(1.0f);
            glEnable(GL_CULL_FACE);
            glEnable(GL_BLEND);
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LEQUAL);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            game->render();
            
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            
            glDisable(GL_BLEND);
            glfwSwapBuffers(window);
            
        }
    }

    // Delete all resources as loaded using the resource manager
    ResourceManager::Clear();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    
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

    // window resize inital logic
    if (game->keys[GLFW_KEY_1])
    {
        Config::setScreenSize(0);
        glfwSetWindowSize(window, Config::getScreenWidth(), Config::getScreenHeight());
    }
    if (game->keys[GLFW_KEY_2])
    {
        Config::setScreenSize(1);
        glfwSetWindowSize(window, Config::getScreenWidth(), Config::getScreenHeight());
    }
    if (game->keys[GLFW_KEY_3])
    {
        Config::setScreenSize(2);
        glfwSetWindowSize(window, Config::getScreenWidth(), Config::getScreenHeight());
    }
    if (game->keys[GLFW_KEY_4])
    {
        Config::setScreenSize(3);
        glfwSetWindowSize(window, Config::getScreenWidth(), Config::getScreenHeight());
    }
    if (game->keys[GLFW_KEY_F])
    {
        Config::setFullscreen(true);
        glfwSetWindowMonitor(window, glfwGetPrimaryMonitor(), 0, 0, Config::getScreenWidth(), Config::getScreenHeight(), 60);
    }
    if (game->keys[GLFW_KEY_W])
    {
        Config::setFullscreen(false);
        glfwSetWindowMonitor(window, nullptr, 0, 0, Config::getScreenWidth(), Config::getScreenHeight(), 60);
    }
}
