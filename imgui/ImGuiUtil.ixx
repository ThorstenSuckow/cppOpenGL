module;

#include <imgui.h>
#include <map>
#include <string>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <glad/glad.h>
#include "imgui_internal.h"

export module ImGuiUtil;

using namespace std;


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
            cullFaceOptions(settings);
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