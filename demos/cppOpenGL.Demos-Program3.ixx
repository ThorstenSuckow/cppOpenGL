module;

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <map>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>


export module cppOpenGL.Demos:Program3;

import GLFWUtil;
import ImGuiUtil;

using namespace std;



export void program3(GLFWwindow* window, map<string, unsigned int>& settings) {

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

   
    
    while (!glfwWindowShouldClose(window)) {

        GLFWUtil::processInput(window);
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        ImGuiUtil::renderSettings("Program3", settings);
        

        glClearColor(
            (settings["GL_CLEAR_COLOR"] >> 24) / 255.0f,
            ((settings["GL_CLEAR_COLOR"] & 0x00FF0000) >> 16) / 255.0f,
            ((settings["GL_CLEAR_COLOR"] & 0x0000FF00) >> 8) / 255.0f,
            ((settings["GL_CLEAR_COLOR"] & 0x000000FF)) / 255.0f
        );

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