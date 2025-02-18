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



export void program9(GLFWwindow* window, map<string, unsigned int>& settings) {

    float vertices[] = {
        -0.25f, -0.25f, 0.0f,
        0.25f, -0.25f, 0.0f,
        0.0f, 0.25f, 0.0f
    };

    enum VAO_IDs {Triangle, NumVAOs};
    enum VBO_IDs {Buffer, NumVBOs};
    enum Attrib_IDs {vPosition = 0};


    unsigned int VAOs[NumVAOs];
    unsigned int VBOs[NumVBOs];

    glCreateBuffers(NumVBOs, VBOs);
    glNamedBufferStorage(VBOs[Buffer], sizeof(vertices), vertices, 0);

    glCreateVertexArrays(NumVAOs, VAOs);
    
    glBindVertexArray(VAOs[Triangle]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[Buffer]);
    glEnableVertexAttribArray(vPosition);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);



    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();
        GLFWUtil::processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAOs[Triangle]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

}