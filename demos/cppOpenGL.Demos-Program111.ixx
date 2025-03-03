module;

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <map>
#include <iostream>


export module cppOpenGL.Demos:Program111;

import GLFWUtil;

using namespace std;



export void program111(GLFWwindow* window) {

    float vertices[] = {
        -0.25f, -0.25f, 0.0f,
        0.25f, -0.25f, 0.0f,
        0.0f, 0.25f, 0.0f
    };

    enum VAO_IDs { Triangles, NumVAOs };
    enum VBO_IDs {Buffer, NumVBOs};
    enum AttributeIds {vPosition = 0};

    unsigned int VAOs[NumVAOs];
    unsigned int VBOs[NumVBOs];

    glCreateVertexArrays(NumVAOs, VAOs);
    glCreateBuffers(NumVBOs, VBOs);

    glNamedBufferStorage(VBOs[Buffer], sizeof(vertices), vertices, 0);

    glBindVertexArray(VAOs[Triangles]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[Buffer]);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(vPosition);



    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();
        GLFWUtil::processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAOs[Triangles]);
        glDrawArrays(GL_TRIANGLES, 0, 3);


        glfwSwapBuffers(window);
    }

}