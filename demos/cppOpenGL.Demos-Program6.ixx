module;

#include <glad/glad.h>
#include <glfw/glfw3.h>

export module cppOpenGL.Demos:Program6;

import GLFWUtil;
import GLSLUtil;

const char* vertexShaderSource = 
    "#version 450 core\n"
    "layout (location=0) in vec3 aPos;"
    "void main() {\n"
    " gl_Position = vec4(aPos, 1.0f);\n"
    " \n"
    "\n}\0"
;

const char* fragmentShaderSource1 =
"#version 450 core\n"
"out vec4 FragColor;"
"void main() {\n"
" FragColor = vec4(0.0f, 1.0f, 1.0f, 1.0f);\n"
" \n"
"\n}\0"
;

const char* fragmentShaderSource2 =
"#version 450 core\n"
"out vec4 FragColor;"
"void main() {\n"
" FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
" \n"
"\n}\0"
;


export void program6(GLFWwindow* window) {


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


    unsigned int shaderProgram1;
    unsigned int shaderProgram2;
    shaderProgram1 = GLSLUtil::compileShader(vertexShaderSource, fragmentShaderSource1);
    shaderProgram2 = GLSLUtil::compileShader(vertexShaderSource, fragmentShaderSource2);

    enum VAO_IDs { Triangle1, Triangle2, NumVAOs };
    enum Buffer_IDs { TriangleBuffer1, TriangleBuffer2, NumBuffers };
    enum AttributIds { vPosition = 0 };

    unsigned int VAOs[NumVAOs];
    unsigned int Buffers[NumBuffers];

    glCreateVertexArrays(NumVAOs, VAOs);
    glCreateBuffers(NumBuffers, Buffers);

    glNamedBufferStorage(Buffers[TriangleBuffer1], sizeof(vertices1), vertices1, 0);
    glNamedBufferStorage(Buffers[TriangleBuffer2], sizeof(vertices2), vertices2, 0);

    glBindVertexArray(VAOs[Triangle1]);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[Triangle1]);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(vPosition);


    glBindVertexArray(VAOs[Triangle2]);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[Triangle2]);
    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(vPosition);

    while (!glfwWindowShouldClose(window)) {

        glfwPollEvents();
        GLFWUtil::processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram1);
        glBindVertexArray(VAOs[Triangle1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(shaderProgram2);
        glBindVertexArray(VAOs[Triangle2]);
        glDrawArrays(GL_TRIANGLES, 0, 3);


        glfwSwapBuffers(window);

    }



}