module;

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

export module cppOpenGL.Demos:Program4;

import GLFWUtil;

using namespace std;

export void program4(GLFWwindow* window) {

    float vertices[] = {
        -1.0f, -1.0f, 0.0f,
        -0.5f, -1.0f, 0.0f,
        -0.75f, -0.5f, 0.0f,

        1.0f, 1.0f, 0.0f,
        0.5f, 1.0f, 0.0f,
        0.75f, 0.5f, 0.0f

    };

    enum VAO_IDs { Triangles, NumVAOs };
    enum Buffer_IDs {ArrayBuffer, NumBuffers};
    enum Attrib_IDs {vPosition = 0};
    
    GLuint VAOs[NumVAOs];
    GLuint Buffers[NumBuffers];
    
    cout << "This program uses OpenGL 4.5 functionality, e.g. \"glCreateVertexArrays\"" << endl;

    glCreateVertexArrays(NumVAOs, VAOs);
    glBindVertexArray(VAOs[Triangles]);

    
    glCreateBuffers(NumBuffers, Buffers);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
    glNamedBufferStorage(Buffers[ArrayBuffer], sizeof(vertices), vertices, 0);


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);


    while (!glfwWindowShouldClose(window)) {

        GLFWUtil::processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 6);

        glfwSwapBuffers(window);
        glfwPollEvents();


    }


}