module;

#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <map>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

export module cppOpenGL.Demos:Program8;

import ImGuiUtil;
import GLFWUtil;
import GLSLUtil;
import IOUtil;

using namespace std;



export void program8(GLFWwindow* window, map<string, unsigned int>& settings) {

    float vertices[] = {
        -0.25f, -0.25f, 0.0f,
        0.25f, -0.25f, 0.0f,
        0.0f, 0.25f, 0.0f
    };

    string vertexShader;
    string fragmentShader;
    IOUtil::readInto("./resources/shader/lesson-1-4.vert", vertexShader);
    IOUtil::readInto("./resources/shader/lesson-1-4.frag", fragmentShader);

    unsigned int prog = GLSLUtil::compileShader(vertexShader.c_str(), fragmentShader.c_str());

    glUseProgram(prog);

    enum VAO_IDs {Triangle, NumVAOs};
    enum VBO_IDs {Buffer, NumVBOs};

    enum Attrib_IDs {vPosition = 0};

    unsigned int VAOs[NumVAOs];
    unsigned int VBOs[NumVBOs];

    glCreateBuffers(NumVBOs, VBOs);
    glCreateVertexArrays(NumVAOs, VAOs);

    glNamedBufferStorage(VBOs[Buffer], sizeof(vertices), vertices, 0);

    glBindVertexArray(VAOs[Triangle]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[Buffer]);
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);

    unsigned int colorPos = glGetUniformLocation(prog, "sinColor");

    float timeSin, timeCos;

    ImGuiUtil::init(window);

    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();
        GLFWUtil::processInput(window);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGuiUtil::renderSettings("Program8", settings);

        glClearColor(
            (settings["GL_CLEAR_COLOR"] >> 24) / 255.0f,
            ((settings["GL_CLEAR_COLOR"] & 0x00FF0000) >> 16) / 255.0f,
            ((settings["GL_CLEAR_COLOR"] & 0x0000FF00) >> 8) / 255.0f,
            ((settings["GL_CLEAR_COLOR"] & 0x000000FF)) / 255.0f
        );
        
        glClear(GL_COLOR_BUFFER_BIT);

        timeSin = (float)sin(glfwGetTime()) / 0.2f + 0.5f;
        timeCos = (float)cos(glfwGetTime()) / 0.2f + 0.5f;

        glBindVertexArray(VAOs[Triangle]);
        glUniform3f(colorPos, timeSin, timeCos, abs(timeSin - timeCos));
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


        glfwSwapBuffers(window);
    }

    ImGuiUtil::shutdown();
}