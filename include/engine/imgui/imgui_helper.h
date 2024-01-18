#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "engine/framebuffer/framebuffer.h"
#include "config.h"

class ImGuiHelper
{
public:
    static void drawGUI(Framebuffer *);
    static void init(GLFWwindow *);
    static void render();
    static void destroy();

private:
    ImGuiHelper(){};
    static void drawSceneWindow(Framebuffer *);
    static void drawPlayerWindow();
    static void drawUserInputWindow();
    static void drawGeneralSettingsWindow(Framebuffer *);
};
