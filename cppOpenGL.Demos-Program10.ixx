module; 

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <map>

export module cppOpenGL.Demos:Program10;


import GLFWUtil;
import GLSLUtil;
import IOUtil;

using namespace std;

void loadVertexShader(unsigned int& prog) {

	string vertexShader;
	string fragmentShader;
	
	IOUtil::readInto("./resources/shader/lesson-2-1.vert", vertexShader);
	IOUtil::readInto("./resources/shader/lesson-2-1.frag", fragmentShader);

	prog = GLSLUtil::compileShader(vertexShader.c_str(), fragmentShader.c_str());
}

void processInput(GLFWwindow* window) {

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		cout << "LEFT" << endl;
		return;
	}


	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		cout << "RIGHT" << endl;
		return;
	}


	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		cout << "UP" << endl;
		return;
	}


	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		cout << "DOWN" << endl;
		return;
	}

}

export void program10(GLFWwindow* window) {


	GLfloat vertices[] = {
		0.0, 0.5, 0.0, 
		-0.5, -0.5, 0.0,
		0.5, -0.5, 0.0
	};
	unsigned int PROG_ID;

	loadVertexShader(PROG_ID);

	unsigned int VBO;
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);


	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		GLFWUtil::processInput(window);
		processInput(window);


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		glUseProgram(PROG_ID);
		glBindVertexArray(VAO);

		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
	}


};