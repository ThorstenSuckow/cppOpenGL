#include <string>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <map>

import GLSLUtil;
import cppOpenGL.Demos;
import IOUtil;
using namespace std;

const unsigned short NUM_PROGRAMS = 9;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

static map<string, unsigned int> getSettings() {
	unsigned int color = 0x00000000;
	map<string, unsigned int> settings = {
		{"GL_CULL_FACE", 0x0000},
		/**
		 * solely relying on a 16 bit value for the shift operation is risky,
		 * but'l do for now
		 */
		{"GL_POLYGON_MODE", (GL_FRONT_AND_BACK << 16) | GL_FILL},

		{"GL_CLEAR_COLOR", (color | (51 << 24) | (76 << 16) | (76 << 8) | 255)},

		{"GL_BLEND", 0x0000},

		{"GL_POINT_SIZE", 10},
		{"GL_LINE_WIDTH", 10},
		{"GL_LINE_SMOOTH", GL_DONT_CARE}

	};

	return settings;
}

void showEnv(GLFWwindow* window) {

	const GLubyte* version = glGetString(GL_VERSION);
	
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	
	cout << endl << endl << "Env infos:" << endl;
	cout << "OpenGL Version: " << version << endl;
	cout << "Max nr of vertex attributes: " << nrAttributes;
	cout << endl << endl;

}

void run(unsigned int progId, GLFWwindow* window) {

	map<string, unsigned int> settings = getSettings();

	switch (progId) {
	case 0:
		showEnv(window);
		break;

	case 1:
		program1(window);
		break;
	case 2:
		program2(window);
		break;
	case 3:
		program3(window, settings);
		break;
	case 4:
		program4(window);
		break;
	case 5:
		program5(window);
		break;
	case 6:
		program6(window);
		break;
	case 7:
		program7(window);
		break;
	case 8:
		program8(window, settings);
		break;
	case 9:
		program9(window, settings);
		break;
	case 111:
		program111(window);
		break;

	}

}

int select_program() {


	cout << "OpenGL 4.6\n";
	cout << "==========\n\n";
	cout << "Please specify the program to run:\n\n";
	cout << "(0) env infos\n";
	cout << "(1) Lesson 1-1: Triangle drawing (glDrawArrays)\n";
	cout << "(2) Lesson 1-2: Triangle drawing indexed (glDrawElements)\n";
	cout << "(3) Lesson 1-3: Clockwise GL_TRIANGLE_STRIP (incl. settings overlay)\n";
	cout << "(4) Excercise 5.8.1: Vertices for two triangles\n";
	cout << "(5) Excercise 5.8.2: Two VAOs/VBOs for two triangles\n";
	cout << "(6) Excercise 5.8.3: Two different fragment shaders for two triangles\n";
	cout << "(7) Lesson 1-4: Color changing shader\n";
	cout << "(8) Lesson 1-5: Color changing shader w/ settings\n";
	cout << "(9) Lesson 1-6: Select object w/ click\n";
	cout << "(anything else: exit)\n\n";

	int option;

	cin >> option;

	if (option >= 0 && option <= NUM_PROGRAMS || (option == 111)) {
		string progid = to_string(option);
		cout << "running " + progid + "...\n";
	} else {
		option = -1;
	}
	
	return option;
}

int main() {

	int option = select_program();

	if (option == -1) {
		return 0;
	}

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	short width = option == 0 ? 1 : 800;
	short height= option == 0 ? 1 : 600;

	GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL Demo", NULL, NULL);

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
	string vertexShaderSource;
	string fragmentShaderSource;
	IOUtil::readInto("./resources/shader/simpleshader.vert", vertexShaderSource);
	IOUtil::readInto("./resources/shader/simpleshader.frag", fragmentShaderSource);


	shaderProgram = GLSLUtil::compileShader(
		vertexShaderSource.c_str(), fragmentShaderSource.c_str());

	glUseProgram(shaderProgram);
	
	run(option, window);
	
	glfwTerminate();

	main();

}