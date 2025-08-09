module; 

#define _USE_MATH_DEFINES

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <map>
#include <array>
#include <cmath>

export module cppOpenGL.Demos:Program10;


import GLFWUtil;
import GLSLUtil;
import IOUtil;

using namespace std;

struct Triangle {
public:
	float rotZ = 0;
	float rotY = 0;
};


array<float, 16> rotateZ(float degree) {
	return array<float, 16> {
		cos(degree), sin(degree), 0, 0,
			-sin(degree), cos(degree), 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
	};
}

array<float, 16> rotateY(float degree) {
	return array<float, 16> {
		cos(degree), 0, -sin(degree), 0,
		0, 1, 0, 0,
		sin(degree), 0, cos(degree), 0,
		0, 0, 0, 1
	};
}


Triangle MY_TRIANGLE;



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
		MY_TRIANGLE.rotY = fmod((MY_TRIANGLE.rotY + (5 * M_PI / 180)), 2 * M_PI);
		cout << MY_TRIANGLE.rotY << endl;
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

	unsigned int mvpMatrix = glGetUniformLocation(PROG_ID, "modelMatrix");


	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		GLFWUtil::processInput(window);
		processInput(window);

		array<float, 16> modelMatrix = rotateY(MY_TRIANGLE.rotY);


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(PROG_ID);
		glUniformMatrix4fv(mvpMatrix, 1, GL_FALSE, modelMatrix.data());
		glBindVertexArray(VAO);



		glDrawArrays(GL_TRIANGLES, 0, 3);



		glfwSwapBuffers(window);
	}


};