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

/**
 * copied from https://pthom.github.io/imgui_manual_online/manual/imgui_manual.html
 */
static void HelpMarker(const char* desc)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::BeginItemTooltip()) {
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

void polygonModeOptions(map<string, unsigned int>& settings) {


    unsigned int polygonMode = settings["GL_POLYGON_MODE"];
    unsigned short lft = (settings["GL_POLYGON_MODE"] >> 16);
    unsigned short rgt = settings["GL_POLYGON_MODE"];

    ImGui::SeparatorText("GL_POLYGON_MODE");
    
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
    ImGui::SameLine(); HelpMarker(
        "While older versions (2.1, see https://registry.khronos.org/OpenGL-Refpages/gl2.1/) seem \n"
        "to accept GL_FRONT / GL_BACK, the 4.6 docs only document the usage of GL_FRONT_AND_BACK\n."
        "(see https://www.khronos.org/opengl/wiki/GLAPI/glPolygonMode)");


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


void blendOptions(map<string, unsigned int>& settings) {

    bool enabled = settings["GL_BLEND"] != 0 ? true : false;

    ImGui::SeparatorText("GL_BLEND");

    if (ImGui::Checkbox("GL_BLEND", &enabled)) {
        settings["GL_BLEND"] = !enabled ? 0 : (GL_SRC_ALPHA << 16 ) | GL_ONE_MINUS_SRC_ALPHA;
    }

    if (enabled) {

        const map<unsigned short, string> items = {
            {GL_SRC_ALPHA, "GL_SRC_ALPHA"},
            {GL_ONE_MINUS_SRC_ALPHA, "GL_ONE_MINUS_SRC_ALPHA" }
        };

        static unsigned short selectedItem = (settings["GL_BLEND"] >> 16);
        ImGui::Text("SRC"); ImGui::SameLine(75); 
        if (items.contains(selectedItem)) {
            if (ImGui::BeginCombo("##select_GL_BLEND", items.at(selectedItem).c_str())) {

                ImGui::EndCombo();
            }
        }
     }

    if (settings["GL_BLEND"] != 0) {
        glEnable(GL_BLEND);
        glBlendFunc(settings["GL_BLEND_FUNC"] >> 16, (settings["GL_BLEND_FUNC"] & 0x00FF));
    }
    else {
        glDisable(GL_BLEND);
    }
}

void cullFaceOptions(map<string, unsigned int>& settings) {
    
    bool enabled = settings["GL_CULL_FACE"] != 0 ? true : false;

    ImGui::SeparatorText("GL_CULL_FACE");

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

void clearColor(map<string, unsigned int>& settings) {

    static ImVec4 color = ImVec4(
        (settings["GL_CLEAR_COLOR"] >> 24) / 255.0f,
        ((settings["GL_CLEAR_COLOR"] & 0x00FF0000) >> 16) / 255.0f,
        ((settings["GL_CLEAR_COLOR"] & 0x0000FF00) >> 8) / 255.0f,
        ((settings["GL_CLEAR_COLOR"] & 0x000000FF)) / 255.0f
    );

    ImGui::SeparatorText("GL_CLEAR_COLOR");
    ImGui::ColorEdit4("MyColor##1", (float*)&color);

    unsigned int col = 0x00000000;
    settings["GL_CLEAR_COLOR"] = col | 
        ((static_cast<unsigned int>(color.x * 255)) << 24) |
        ((static_cast<unsigned int>(color.y * 255)) << 16) |
        ((static_cast<unsigned int>(color.z * 255)) << 8) |
        (static_cast<unsigned int>(color.w * 255));

}



export namespace ImGuiUtil {

   
    void addGlobalRenderOptions(map<string, unsigned int>& settings) {

        if (ImGui::TreeNodeEx("Global Render Options", ImGuiTreeNodeFlags_DefaultOpen)) {
            ImGui::Spacing();
            blendOptions(settings);
            ImGui::Spacing();
            clearColor(settings);
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