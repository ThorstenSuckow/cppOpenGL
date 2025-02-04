module;

#include <imgui.h>
#include <map>
#include <string>
#include <iostream>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <glad/glad.h>
#include "imgui_internal.h"

export module ImGuiUtil;

using namespace std;

void polygonModeOptions(map<string, unsigned int>& settings) {


    unsigned int polygonMode = settings["GL_POLYGON_MODE"];
    unsigned short lft = (settings["GL_POLYGON_MODE"] >> 16);
    unsigned short rgt = settings["GL_POLYGON_MODE"];

    ImGui::Text("GL_POLYGON_MODE");


    const char* items[] = { "GL_FRONT", "GL_BACK", "GL_FRONT_AND_BACK", "GL_FILL", "GL_LINE", "GL_POINT"};
    static int selectedItem_lft = lft == GL_FRONT ? 0 : (lft == GL_BACK ? 1 : 2);
    if (ImGui::BeginCombo("##select_GL_POLYGON_MODE_lft", items[selectedItem_lft])) {
        for (int i = 0; i < 3; ++i) {
            bool isSelected = (selectedItem_lft == i);
            if (ImGui::Selectable(items[i], isSelected)) {
                selectedItem_lft = i;
            }
            if (isSelected) {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }
    settings["GL_POLYGON_MODE"] = (selectedItem_lft == 0 ? GL_FRONT : (selectedItem_lft == 1 ? GL_BACK : GL_FRONT_AND_BACK)) << 16;

    static int selectedItem_rgt = rgt == GL_FILL ? 3 : (rgt == GL_LINE ? 4 : GL_POINT);
    if (ImGui::BeginCombo("##select_GL_POLYGON_MODE_rgt", items[selectedItem_rgt])) {
        for (int i = 3; i < 6; ++i) {
            bool isSelected = (selectedItem_rgt == i);
            if (ImGui::Selectable(items[i], isSelected)) {
                selectedItem_rgt = i;
            }
            if (isSelected) {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }
    settings["GL_POLYGON_MODE"] = (settings["GL_POLYGON_MODE"] & 0xFFFF0000)
        | (selectedItem_rgt == 3 ? GL_FILL : (selectedItem_rgt == 4 ? GL_LINE : GL_POINT));

    polygonMode = settings["GL_POLYGON_MODE"];
    lft = (settings["GL_POLYGON_MODE"] >> 16);
    rgt = settings["GL_POLYGON_MODE"];
    
    
    glPolygonMode(lft, rgt);
}


void cullFaceOptions(map<string, unsigned int>& settings) {
    
    bool enabled = settings["GL_CULL_FACE"] != 0 ? true : false;

    if (ImGui::Checkbox("GL_CULL_FACE", &enabled)) {
        settings["GL_CULL_FACE"] = !enabled ? 0 : GL_FRONT;
    }

    if (enabled) {
        const char* items[] = { "GL_FRONT", "GL_BACK", "GL_FRONT_AND_BACK" };
        static int selectedItem = 0;  
        if (ImGui::BeginCombo("##select_GL_CULL_FACE", items[selectedItem])) {
            for (int i = 0; i < IM_ARRAYSIZE(items); ++i) {
                bool isSelected = (selectedItem == i);
                if (ImGui::Selectable(items[i], isSelected)) {
                    selectedItem = i;
                }
            }
            ImGui::EndCombo();
        }
        settings["GL_CULL_FACE"] = selectedItem == 0 ? GL_FRONT : (selectedItem == 1 ? GL_BACK : GL_FRONT_AND_BACK);
    }
    
    if (settings["GL_CULL_FACE"] != 0) {
        glEnable(GL_CULL_FACE);
        glCullFace(settings["GL_CULL_FACE"]);
    }
    else {
        glDisable(GL_CULL_FACE);
    }

}



export namespace ImGuiUtil {

   
    void addGlobalRenderOptions(map<string, unsigned int>& settings) {

        if (ImGui::TreeNodeEx("Global Render Options", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::Spacing();
            cullFaceOptions(settings);
            ImGui::Spacing();
            polygonModeOptions(settings);
            ImGui::TreePop();
        }

    }


    void shutdown() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void init(GLFWwindow* window) {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
        ImGui_ImplOpenGL3_Init();
    }



}