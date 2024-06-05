#include "engine/imgui/imgui_helper.h"
#include "engine/store/map_store.h"
#include "imgui.h"
#include "store/player_store.h"
#include "types.h"
#include <iostream>
#include <vector>


#define X(state, name) name,
char const *entityStateNames[] =
{
  ENTITY_STATES
};
#undef X

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
    ImGuiHelper::drawMapWindow();

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
    ImGui::Begin("Player");
    {
      ImGui::BeginTable("player_table", 2);
          ImGui::TableNextRow();
              ImGui::TableNextColumn();
              ImGui::Text("X:");
              ImGui::TableNextColumn();
              ImGui::Text("%f", PlayerStore::position.x);
          ImGui::TableNextRow();
              ImGui::TableNextColumn();
              ImGui::Text("Y:");
              ImGui::TableNextColumn();
              ImGui::Text("%f", PlayerStore::position.y);
          ImGui::TableNextRow();
              ImGui::TableNextColumn();
              ImGui::Text("Current health:");
              ImGui::TableNextColumn();
              ImGui::Text("%d", PlayerStore::currentHP);
          ImGui::TableNextRow();
              ImGui::TableNextColumn();
              ImGui::Text("Current mana:");
              ImGui::TableNextColumn();
              ImGui::Text("%d", PlayerStore::currentMP);
          ImGui::TableNextRow();
              ImGui::TableNextColumn();
              ImGui::Text("Active states:");
              ImGui::TableNextColumn();
              for (auto & state : PlayerStore::activeStates) {
                  ImGui::Text(
                      "%s",
                      entityStateNames[state]
                  );
              }
      ImGui::EndTable();
    }
    ImGui::End();
}

void ImGuiHelper::drawMapWindow()
{
    ImGui::Begin("Map");
    {
        static const char* current_item = NULL;
        unsigned short current_item_index = 0;
        ImGuiStyle& style = ImGui::GetStyle();
        float w = ImGui::CalcItemWidth();
        float spacing = style.ItemInnerSpacing.x;
        float button_sz = ImGui::GetFrameHeight();
        ImGui::PushItemWidth(w - spacing * 2.0f - button_sz * 2.0f);
        if (ImGui::BeginCombo("##custom combo", current_item, ImGuiComboFlags_NoArrowButton))
        {
            unsigned short i = 0;
            for (const std::string &map : MapStore::getMaps())
            {
                bool is_selected = (current_item == map.c_str());
                if (ImGui::Selectable(map.c_str(), is_selected))
                {
                    current_item = map.c_str();
                    current_item_index = i;
                }
                if (is_selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
                i++;
            }
            ImGui::EndCombo();
        }
        ImGui::PopItemWidth();
        ImGui::SameLine(0, spacing);
        if (ImGui::ArrowButton("##r", ImGuiDir_Left))
        {
            current_item_index--;

            if (current_item_index < 0)
            {
                current_item_index = 0;
            }

            current_item = MapStore::getMaps().at(current_item_index).c_str();
        }
        ImGui::SameLine(0, spacing);
        if (ImGui::ArrowButton("##r", ImGuiDir_Right))
        {
            current_item_index++;
            
            if (current_item_index >= MapStore::getMaps().size()) {
                current_item_index = 0;
            }

            current_item = MapStore::getMaps().at(current_item_index).c_str();
        }
        ImGui::SameLine(0, style.ItemInnerSpacing.x);
        ImGui::Text("Custom Combo");
    }
    ImGui::End();
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
