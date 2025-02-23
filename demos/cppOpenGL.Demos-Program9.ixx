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


void id2Color(unsigned int id, unsigned char* color) {

    if (id > 0xFFFFFF) {
        cerr << "id must be less than or equal to " << 0xFFFFFF;
    }

    color[0] = (id) & 0xFF;
    color[1] = (id >> 8) & 0xFF;
    color[2] = (id >> 16) & 0xFF;
}


unsigned int color2Id(unsigned char r, unsigned char g, unsigned char b) {
    return (r << 16) |
        (g << 8) |
        (b);
}


void loadColorIdProgram(unsigned int &prog) {
    string vertex;
    string  fragment;
    IOUtil::readInto("./resources/shader/lesson-1-6.vert", vertex);
    IOUtil::readInto("./resources/shader/lesson-1-6.frag", fragment);

    prog = GLSLUtil::compileShader(vertex.c_str(), fragment.c_str());
}

void loadProgram(unsigned int& prog) {
    string vertex;
    string  fragment;
    IOUtil::readInto("resources/shader/simpleshader.vert", vertex);
    IOUtil::readInto("resources/shader/simpleshader.frag", fragment);

    prog = GLSLUtil::compileShader(vertex.c_str(), fragment.c_str());
}

const unsigned int OBJECT_ID = 34;

export void program9(GLFWwindow* window, map<string, unsigned int>& settings) {

    unsigned char colorCode[3] = {0, 0, 0};

    unsigned int colorIdProg;
    unsigned int prog;
    loadColorIdProgram(colorIdProg);
    loadProgram(prog);

    unsigned int colorCodeUniform = glGetUniformLocation(
        colorIdProg, "id2ColorCode");

    float vertices[] = {
        -0.25f, -0.25f, 0.0f,
        0.25f, -0.25f, 0.0f,
        0.0f, 0.25f, 0.0f
    };

    enum VAO_IDs {Triangle, ColorMapper, NumVAOs};
    enum VBO_IDs {Buffer, NumVBOs};
    enum AttributeIds {vPosition = 0};

    unsigned int VAOs[NumVAOs];
    unsigned int VBOs[NumVBOs];

    glCreateVertexArrays(NumVAOs, VAOs);
    glCreateBuffers(NumVBOs, VBOs);

    glNamedBufferStorage(VBOs[Buffer], sizeof(vertices), vertices, 0);
    
    glBindVertexArray(VAOs[ColorMapper]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[Buffer]);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(vPosition);
    
    glBindVertexArray(VAOs[Triangle]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[Buffer]);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(vPosition);

    ImGuiUtil::init(window);

    ImGuiIO& io = ImGui::GetIO();
    int width;
    int height;
    
    
    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();
        GLFWUtil::processInput(window);
        glfwGetWindowSize(window, &width, &height);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();
        ImGuiUtil::renderSettingsAndClear("Program9", settings, GL_COLOR_BUFFER_BIT);
        
        ImGui::Text("Mouse pos: (%g, %g)", io.MousePos.x, io.MousePos.y);
        ImGui::Text("Mouse down: ");

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)) {
            for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) {
                if (ImGui::IsMouseDown(i)) {
                    ImGui::Text("b%d (%.02f secs)", i, io.MouseDownDuration[i]);
                }
            }


            glUseProgram(colorIdProg);
            glBindVertexArray(VAOs[ColorMapper]);

            id2Color(OBJECT_ID, colorCode);

            glUniform3f(
                colorCodeUniform,
                (float)(colorCode[2] / 255.0f),
                (float)(colorCode[1] / 255.0f),
                (float)(colorCode[0] / 255.0f)
            );
            glDrawArrays(GL_TRIANGLES, 0, 3);
           
            glFlush();
            glFinish();

            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            unsigned char data[4];
            glReadPixels(
                io.MousePos.x, height - io.MousePos.y, 
                1, 1, GL_RGBA, GL_UNSIGNED_BYTE, data
            );
            
            unsigned int objectId = color2Id(data[0], data[1], data[2]);
            ImGui::Text(
                "(%d, %d, %d) [%d] %s", 
                data[0], data[1], data[2],
                objectId,
                objectId == OBJECT_ID ? "match" : "-"
            );
        }

        

        glUseProgram(prog);
        glBindVertexArray(VAOs[Triangle]);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());



        glfwSwapBuffers(window);
    }
    ImGuiUtil::shutdown();

}