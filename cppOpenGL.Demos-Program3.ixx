module;

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

import GLFWUtil;


export module cppOpenGL.Demos:Program3;

import ImGuiUtil;

using namespace std;


void renderImGui(unsigned short &selection) {
    ImGui::Begin("Program3");

    ImGui::Text("Set GL_CULL_FACE-value:");

    if (ImGui::RadioButton("GL_FRONT", selection == GL_FRONT)) {
        selection = GL_FRONT;
    }
    if (ImGui::RadioButton("GL_BACK", selection == GL_BACK)) {
        selection = GL_BACK;
    }
    if (ImGui::RadioButton("GL_FRONT_AND_BACK", selection == GL_FRONT_AND_BACK)) {
        selection = GL_FRONT_AND_BACK;
    }

    
    ImGui::End();
}

export void program3(GLFWwindow* window) {

    ImGuiUtil::init(window);

    float vertices[] = {
        -0.25f, 0.0f, 0.0f,
        0.25f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    unsigned int index[] = {
        2, 1, 0
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    cout << "Enabling GL_CULL_FACE, setting cull face to GL_BACK.\n";
    cout << "This will cause the triangle, which is rendered \n";
    cout << "using indexed rendering (clockwise, front face is set to GL_CCW),\n";
    cout << "to be invisible.\n";
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    unsigned short selection = 0;
    while (!glfwWindowShouldClose(window)) {

        GLFWUtil::processInput(window);
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        renderImGui(selection);

        glCullFace(selection);
        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGuiUtil::shutdown();

}