module;

#include <iostream>
#include <glad/glad.h>
#include <glfw/glfw3.h>

export module cppOpenGL.Demos:Program7;

import GLFWUtil;
import GLSLUtil;
import IOUtil;

using namespace std;

export void program7(GLFWwindow* window) {

    unsigned int uniformLocation;

    string vertexShaderSource;
    string fragmentShaderSource;

    IOUtil::readInto("./resources/shader/lesson-1-4.vert", vertexShaderSource);
    IOUtil::readInto("./resources/shader/lesson-1-4.frag", fragmentShaderSource);

    unsigned int prog = GLSLUtil::compileShader(
        vertexShaderSource.c_str(), fragmentShaderSource.c_str());

    glUseProgram(prog);

    uniformLocation = glGetUniformLocation(prog, "sinColor");

    float vertices[] = {
        -0.25, -0.25, 0,
        0.25, -0.25, 0,
        0.0, 0.5, 0
    };

    enum VAO_IDs { Triangle, NumVAOs };
    enum VBO_IDs { Buffer, NumVBOs };
    enum Attrib_IDs {vPosition = 0};

    unsigned int VAOs[NumVAOs];
    unsigned int VBOs[NumVBOs];


    glCreateVertexArrays(NumVAOs, VAOs);
    glCreateBuffers(NumVBOs, VBOs);

    glNamedBufferStorage(VBOs[Buffer], sizeof(vertices), vertices, 0);

    
    glBindVertexArray(VAOs[Triangle]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[Buffer]);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(vPosition);

    float timeValue;

    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();
        timeValue = (float)glfwGetTime();

        GLFWUtil::processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUniform3f(
            uniformLocation, 0.0f, (sin(timeValue) / 2.0f) + 0.5f, 0.0f);

        glDrawArrays(GL_TRIANGLES, 0, 3);


        glfwSwapBuffers(window);
    }



}