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

// GLFW function declarations
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mode);

Game *game;

GLuint FBO;
GLuint RBO;
GLuint texture_id;

void create_framebuffer(GLuint width, GLuint height)
{
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);

    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n";

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void rescale_framebuffer(GLuint width, GLuint height)
{
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);

    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
}

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

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // IF using Docking Branch
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true); // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init("#version 330");

    glfwSetKeyCallback(window, key_callback);

    // OpenGL configuration
    glViewport(0, 0, bufferWidth, bufferHeight);
    create_framebuffer(bufferWidth, bufferHeight);

    game = new Game(Config::getScreenWidth(), Config::getScreenHeight());
    // Initialize game
    game->init();

    // DeltaTime variables
    GLfloat lastFrameTime = 0.0f;
    GLfloat accumulator = 0.0f;
    GLfloat dt = 0.01f;

    const double maxFPS = 60.0f;
    const double maxPeriod = 1.0 / maxFPS;

    bool enableImGui = true;
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

            if (enableImGui)
            {
                // Start the Dear ImGui frame
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();

                // Create a window called "My First Tool", with a menu bar.
                ImGui::Begin("My First Tool", NULL, ImGuiWindowFlags_MenuBar);
                if (ImGui::BeginMenuBar())
                {
                    if (ImGui::BeginMenu("File"))
                    {
                        if (ImGui::MenuItem("Open..", "Ctrl+O"))
                        { /* Do stuff */
                        }
                        if (ImGui::MenuItem("Save", "Ctrl+S"))
                        { /* Do stuff */
                        }
                        if (ImGui::MenuItem("Close", "Ctrl+W"))
                        {
                            enableImGui = false;
                        }
                        ImGui::EndMenu();
                    }
                    ImGui::EndMenuBar();
                }
                ImGui::End();

                ImGui::Begin("Scene");
                {
                    const float window_width = ImGui::GetContentRegionAvail().x;
                    const float window_height = ImGui::GetContentRegionAvail().y;

                    rescale_framebuffer(window_width, window_height);
                    glViewport(0, 0, window_width, window_height);

                    ImVec2 pos = ImGui::GetCursorScreenPos();

                    ImGui::GetWindowDrawList()->AddImage(
                        (ImTextureID)texture_id,
                        pos,
                        ImVec2(pos.x + window_width, pos.y + window_height),
                        ImVec2(0, 1),
                        ImVec2(1, 0));
                }
                ImGui::End();
                ImGui::Render();

                glBindFramebuffer(GL_FRAMEBUFFER, FBO);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glClearDepth(1.0f);
                game->render();
                glBindFramebuffer(GL_FRAMEBUFFER, 0);

                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

                if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
                {
                    GLFWwindow *backup_current_context = glfwGetCurrentContext();
                    ImGui::UpdatePlatformWindows();
                    ImGui::RenderPlatformWindowsDefault();
                    glfwMakeContextCurrent(backup_current_context);
                }
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

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glDeleteFramebuffers(1, &FBO);
    glDeleteTextures(1, &texture_id);
    glDeleteRenderbuffers(1, &RBO);

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
