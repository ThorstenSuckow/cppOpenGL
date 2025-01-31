module;

#include <glad/glad.h>
#include <GLFW/glfw3.h>

export module GLFWUtil;


export namespace GLFWUtil {

	
	void processInput(GLFWwindow* window) {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
	}
}