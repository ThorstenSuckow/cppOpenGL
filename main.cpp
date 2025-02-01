#include <string>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

import GLSLUtil;
import cppOpenGL.Demos;

using namespace std;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location=0) in vec3 aPos;\n"
"void main() {\n"
" gl_Position = vec4(aPos, 1);\n"
"}\0";


const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main() {\n"
" FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void run(unsigned int progId, GLFWwindow* window) {
	switch (progId) {
	case 1:
		program1(window);
		break;
	case 2:
		program2(window);
		break;
	case 3:
		program3(window);
		break;
	}
}

int select_program() {

	cout << "Please specify the program to run:\n\n";
	cout << "(1) Lesson 1-1: Triangle drawing (glDrawArrays)\n";
	cout << "(2) Lesson 1-2: Triangle drawing indexed (glDrawElements)\n";
	cout << "(3) Lesson 1-3: Clockwise GL_TRIANGLE_STRIP\n";
	cout << "(anything else: exit)\n\n";

	int option;

	cin >> option;

	if (option > 0 && option <= 3) {
		string progid = to_string(option);
		cout << "running " + progid + "...\n";
	} else {
		option = 0;
	}
	
	return option;
}

int main() {

	int option = select_program();

	if (option == 0) {
		return 0;
	}

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Demo", NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed to creat GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);

	unsigned int shaderProgram;
	shaderProgram = GLSLUtil::compileShader(vertexShaderSource, fragmentShaderSource);

	glUseProgram(shaderProgram);
	
	run(option, window);
	
	glfwTerminate();

	main();

}