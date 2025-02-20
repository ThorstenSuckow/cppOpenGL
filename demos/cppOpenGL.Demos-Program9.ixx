module;

#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <map>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

export module cppOpenGL.Demos:Program9;

import ImGuiUtil;
import GLFWUtil;
import GLSLUtil;
import IOUtil;

using namespace std;


void idToColor(unsigned int id, unsigned char* color) {

    if (id > 0xFFFFFF) {
        cerr << "id must be less than or equal to " << 0xFFFFFF;
    }

    color[0] = (id) & 0xFF;
    color[1] = (id >> 8) & 0xFF;
    color[2] = (id >> 16) & 0xFF;

}


export void program9(GLFWwindow* window, map<string, unsigned int>& settings) {

    unsigned char color[3] = { 0, 0, 0 };

    idToColor(256*256*256 - 1, color);

    cout  << "COLOR:" << static_cast<int>(color[0]) << " " << " " << static_cast<int>(color[1]) << " " << static_cast<int>(color[2]);



    float vertices[] = {
        -0.25f, -0.25f, 0.0f,
        0.25f, -0.25f, 0.0f,
        0.0f, 0.25f, 0.0f
    };

    enum VAO_IDs {Triangle, NumVAOs};
    enum VBO_IDs {Buffer, NumVBOs};
    enum AttributeIds {vPosition = 0};

    unsigned int VAOs[NumVAOs];
    unsigned int VBOs[NumVBOs];

    glCreateVertexArrays(NumVAOs, VAOs);
    glCreateBuffers(NumVBOs, VBOs);

    glNamedBufferStorage(VBOs[Buffer], sizeof(vertices), vertices, 0);

    glBindVertexArray(VAOs[Triangle]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[Buffer]);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(vPosition);

    ImGuiUtil::init(window);

    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();
        GLFWUtil::processInput(window);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();
        ImGuiUtil::renderSettingsAndClear("Program9", settings, GL_COLOR_BUFFER_BIT);
        
        glBindVertexArray(VAOs[Triangle]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());



        glfwSwapBuffers(window);
    }

}