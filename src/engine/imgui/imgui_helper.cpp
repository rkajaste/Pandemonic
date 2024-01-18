#include "engine/imgui/imgui_helper.h"
#include "imgui.h"

void ImGuiHelper::init(GLFWwindow *window)
{
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
}

void ImGuiHelper::drawGUI(Framebuffer *fb)
{
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGuiHelper::drawSceneWindow(fb);
    ImGuiHelper::drawGeneralSettingsWindow(fb);
    ImGuiHelper::drawPlayerWindow();
    ImGuiHelper::drawUserInputWindow();

    ImGui::Render();
}

void ImGuiHelper::render()
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ImGuiIO &io = ImGui::GetIO();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow *backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void ImGuiHelper::drawSceneWindow(Framebuffer *fb)
{
    ImGui::Begin("Scene");
    {
        const float windowWidth = ImGui::GetContentRegionAvail().x;
        const float windowHeight = ImGui::GetContentRegionAvail().y;

        fb->rescale(windowWidth, windowHeight);
        glViewport(0, 0, windowWidth, windowHeight);

        ImVec2 pos = ImGui::GetCursorScreenPos();

        ImGui::GetWindowDrawList()->AddImage(
            (ImTextureID)fb->getTextureID(),
            pos,
            ImVec2(pos.x + windowWidth, pos.y + windowHeight),
            ImVec2(0, 1),
            ImVec2(1, 0));
    }
    ImGui::End();
}

void ImGuiHelper::drawPlayerWindow()
{
}

void ImGuiHelper::drawUserInputWindow()
{
}

void ImGuiHelper::drawGeneralSettingsWindow(Framebuffer *fb)
{
    ImGui::Begin("General settings");
    {
        ImGui::Checkbox("Debug mode", &Config::isDebugMode);
    }
    ImGui::End();
}

void ImGuiHelper::destroy()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
