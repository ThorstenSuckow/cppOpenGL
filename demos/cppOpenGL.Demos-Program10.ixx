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
import Scene;
import Math;

using namespace std;

struct Triangle {
public:
	float rotZ = 0;
	float rotY = 0;
};


Triangle MY_TRIANGLE;
bool KEY_RELEASED = true;
bool KEY_PRESSED = false;
unsigned int PRESSED_KEY;

void loadVertexShader(unsigned int& prog) {

	string vertexShader;
	string fragmentShader;
	
	IOUtil::readInto("./resources/shader/lesson-2-1.vert", vertexShader);
	IOUtil::readInto("./resources/shader/lesson-2-1.frag", fragmentShader);

	prog = GLSLUtil::compileShader(vertexShader.c_str(), fragmentShader.c_str());
}

void controlNode(Scene::Node& node, GLFWwindow* window) {

	static unsigned short KEYS[4] = {
		GLFW_KEY_LEFT, GLFW_KEY_RIGHT, GLFW_KEY_UP, GLFW_KEY_DOWN
	};

	static float amount = (5 * M_PI / 180);
	static float mod = 2 * M_PI;

	for (int KEY : KEYS) {
		if (!PRESSED_KEY  && glfwGetKey(window, KEY) == GLFW_PRESS) {
			PRESSED_KEY = KEY;
			switch (KEY) {
				case GLFW_KEY_LEFT:
					node.setRotateY(fmod((node.getRotateY() + amount), mod));
					break;
				case GLFW_KEY_RIGHT:
					node.setRotateY(fmod((node.getRotateY() - amount), mod));
					break;
			}
			return;
		}
		else if (PRESSED_KEY == KEY && glfwGetKey(window, KEY) == GLFW_RELEASE) {
			PRESSED_KEY = 0;
			return;
		}
	}
	
}

export void program10(GLFWwindow* window) {


	GLfloat vertices[] = {
		0.0, 0.5, 0.0, 
		-0.5, -0.5, 0.0,
		0.5, -0.5, 0.0
	};

	Scene::Node triangle(vertices);

	unsigned int PROG_ID;

	loadVertexShader(PROG_ID);

	unsigned int VBO;
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);


	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, triangle.getVerticesSize(), triangle.getVertices(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int mvpMatrix = glGetUniformLocation(PROG_ID, "modelMatrix");


	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		GLFWUtil::processInput(window);
		controlNode(triangle, window);

	
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(PROG_ID);
		
		glUniformMatrix4fv(mvpMatrix, 1, GL_FALSE, triangle.getModelMatrix().data());
		glBindVertexArray(VAO);



		glDrawArrays(GL_LINE_LOOP, 0, 3);



		glfwSwapBuffers(window);
	}


};