module;

#include <glad/glad.h>
#include <glfw/glfw3.h>


export module cppOpenGL.Demos:Program5;

import GLFWUtil;


export void program5(GLFWwindow* window) {

    
    float vertices1[] = {
        -1.0f, -1.0f, 0.0f,
        -0.5f, -1.0f, 0.0f,
        -0.75f, -0.5f, 0.0f 
    };

    float vertices2[] = {
        1.0f, 1.0f, 0.0f,
        0.5f, 1.0f, 0.0f,
        0.75f, 0.5f, 0.0f

    };

    enum VAOs { Triangle1, Triangle2, NumVAOs };
    enum VBOs {TriangleBuffer1, TriangleBuffer2, NumBuffers};

    unsigned int VAOs[NumVAOs];
    unsigned int VBOs[NumBuffers];

    glCreateVertexArrays(NumVAOs, VAOs);
    glCreateBuffers(NumBuffers, VBOs);

    glNamedBufferStorage(VBOs[TriangleBuffer1], sizeof(vertices1), vertices1, 0);
    glNamedBufferStorage(VBOs[TriangleBuffer2], sizeof(vertices2), vertices2, 0);

    // VAO 1 / VBO 1
    glBindVertexArray(VAOs[Triangle1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[TriangleBuffer1]);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    
    // VAO 2 / VBO 2
    glBindVertexArray(VAOs[Triangle2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[TriangleBuffer2]);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);


    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();
        GLFWUtil::processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAOs[Triangle1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(VAOs[Triangle2]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

}