#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "engine/frame_buffer/FrameBuffer.hpp"
#include "Config.hpp"

class ImGuiHelper
{
public:
    static void drawGUI(FrameBuffer *);
    static void init(GLFWwindow *);
    static void render();    
    static void destroy();
private:
    ImGuiHelper(){};
    static void drawSceneWindow(FrameBuffer *);
    static void drawPlayerWindow();
    static void drawUserInputWindow();
    static void drawGeneralSettingsWindow();
};

